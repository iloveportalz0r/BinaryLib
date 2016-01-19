#include "../include/BinaryReader.hpp"
#include <fstream>
#include <algorithm> // std::copy_n

struct BinaryReader_private
{
	std::ifstream file;
	std::unique_ptr<uint8_t[]> data;
	uint_fast64_t file_size;
	uint_fast64_t pos;
};

template <class type> type bytes_to_type(BinaryReader* self)
{
	std::unique_ptr<uint8_t[]> buf = self->ReadBytes(sizeof(type));
	type ret = *(reinterpret_cast<type*>(buf.get()));
	return ret;
}

/**
	BinaryReader.cpp
	This class is my implementation of Microsoft's C# BinaryReader
	It reads bytes from a file and returns the following:
	 - signed and unsigned integer values (8-bit, 16-bit, 32-bit, 64-bit, or 128-bit)
	 - single characters (8-bit int) or strings of characters (in std::string)
	It can read strings that have their length specified by a 7-bit encoded int

	Thanks to Matt Davis for the reinterpret_cast usage
		http://stackoverflow.com/a/545020/1578318

	@todo		Check return values of fread
	@todo		Make an exception class to throw when errors occur instead of using std::string
*/

/**
	@arg		s The file to read
*/
BinaryReader::BinaryReader(const std::string& s)
{
	this->privates = new BinaryReader_private();
	this->ChangeFile(s);
}

/**
	@arg		data The byte array to read
	@arg		size The size (in bytes) of the byte array
*/
BinaryReader::BinaryReader(std::unique_ptr<uint8_t[]> data, const uint_fast64_t size)
{
	this->privates = new BinaryReader_private();
	this->ChangeFile(std::move(data), size);
}

BinaryReader::~BinaryReader()
{
	this->Close();
	delete this->privates;
}

/**
	Close the current file, if one is loaded, and open a file
	@arg		s The file to read
*/
void BinaryReader::ChangeFile(const std::string& filename)
{
	this->Close();

	this->privates->pos = 0;
	this->privates->data = nullptr;
	this->privates->file.open(filename.c_str(), std::ios::binary | std::ios::ate);
	if(!this->privates->file.is_open())
	{
		throw ("BinaryReader: error opening \"" + filename + "\"");
	}
	this->privates->file_size = this->privates->file.tellg();
	this->privates->file.seekg(0, this->privates->file.beg);
}

/**
	Close the current file, if one is loaded, and use a byte array
	@arg		data The byte array to read
*/
void BinaryReader::ChangeFile(std::unique_ptr<uint8_t[]> data, const uint_fast64_t size)
{
	this->Close();

	this->privates->pos = 0;
	this->privates->file.close();
	this->privates->data = std::move(data);
	this->privates->file_size = size;
}

void BinaryReader::Close()
{
	if(this->privates->data != nullptr)
	{
		this->privates->data = nullptr;
	}
	else if(this->privates->file.is_open())
	{
		this->privates->file.close();
	}
}

uint_fast64_t BinaryReader::GetFileSize() const
{
	return this->privates->file_size;
}

uint_fast64_t BinaryReader::GetPosition() const
{
	return this->privates->pos;
}

void BinaryReader::Seek(uint_fast64_t pos)
{
	this->privates->pos = pos;
}

bool BinaryReader::ReadBool()
{
	return (this->ReadUInt8() != 0);
}

#define X(name, type)\
type BinaryReader::Read##name()\
{\
	return bytes_to_type<type>(this);\
}

BINARYREADER_TYPES

#if __SIZEOF_INT128__ == 16
X(Int128, __int128)
X(UInt128, unsigned __int128)
#else
#warning "BinaryReader::Read(U)Int128 not included"
#endif

#ifdef FLOAT16
X(Float128, FLOAT16)
#else
#warning "BinaryReader::ReadFloat128 not included"
#endif

#undef X

std::unique_ptr<char[]> BinaryReader::ReadChars(uint_fast64_t bytes)
{
	std::unique_ptr<uint8_t[]> uptr = this->ReadBytes(bytes);
	char* ptr = reinterpret_cast<char*>(uptr.release());
	return std::unique_ptr<char[]>(ptr);
}

std::unique_ptr<uint8_t[]> BinaryReader::ReadBytes(uint_fast64_t bytes)
{
	std::unique_ptr<uint8_t[]> buf(new uint8_t[bytes]);

	if(this->privates->data != nullptr)
	{
		std::copy_n(this->privates->data.get() + this->privates->pos, bytes, buf.get());
	}
	else if(this->privates->file.is_open())
	{
		this->privates->file.seekg(this->privates->pos, this->privates->file.beg);
		this->privates->file.read(reinterpret_cast<char*>(buf.get()), bytes);
	}
	else
	{
		throw std::string("BinaryReader: tried to read, but no file is loaded");
	}

	this->privates->pos += bytes;

	return buf;
}

std::string BinaryReader::ReadString(uint_fast64_t length)
{
	std::unique_ptr<char[]> buf = this->ReadChars(length);
	std::string ret(buf.get(), length);
	return ret;
}

// derived from http://www.terrariaonline.com/threads/86509/
uint64_t BinaryReader::Read7BitEncodedInt()
{
	uint_fast64_t ret = 0;
	uint_fast8_t shift = 0;

	while(shift != 70) // maximum shifting is 7 * 9
	{
		uint_fast64_t b = this->ReadUInt8();
		ret |= (b & 127) << shift;
		shift += 7;
		if((b & 128) == 0)
		{
			return ret;
		}
	}
	throw std::string("Failed to read a 7-bit encoded integer");
}

std::string BinaryReader::ReadStringMS()
{
	auto len = this->Read7BitEncodedInt();
	return this->ReadString(len);
}