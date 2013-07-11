#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <stdint.h>
#include <sstream> // for std::stringstream
#include "Util.hpp" // for Util functions and the file functions in stdio.h (included in fstream)

// if you change this, don't forget to recompile the library!
#define FLOAT16 long double
//#define FLOAT16 __float128

class BinaryWriter
{
	public:
		BinaryWriter(std::string s, bool bak = true);
		void addBytes(int i);
		void Close();

		// 8-bit (1 byte)
		bool WriteBool(bool b);

		// 8-bit (1 byte)
		bool WriteInt8(int8_t c);
		bool WriteUInt8(uint8_t value);

		// 16-bit (2 bytes)
		bool WriteInt16(int16_t i);
		bool WriteUInt16(uint16_t i);

		// 32-bit (4 bytes)
		bool WriteInt32(int32_t i);
		bool WriteUInt32(uint32_t i);

		// 64-bit (8 bytes)
		bool WriteInt64(int64_t i);
		bool WriteUInt64(uint64_t i);

		// 128-bit (16 bytes)
		bool WriteInt128(__int128 i);
		bool WriteUInt128(unsigned __int128 i);

		// 32-bit (4 bytes)
		bool WriteFloat32(float value);

		// 64-bit (8 bytes)
		bool WriteFloat64(double value);

		// 128-bit (16 bytes)
		bool WriteFloat128(FLOAT16 value);

		bool WriteChars(int8_t* c, int len);
		bool WriteBytes(uint8_t* c, int len);

		bool WriteString(std::string s);

		void Write7BitEncodedInt(uint32_t value);
		bool WriteStringMS(std::string s);

		bool isLoaded;
		std::string fname;
		FILE *file;
		uint_fast32_t totalBytes;
};

#endif // BINARYWRITER_H