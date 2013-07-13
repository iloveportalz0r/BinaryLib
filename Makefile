#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = 
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -std=c++11 -Wall -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/libbinary.a

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -fomit-frame-pointer -Os -std=c++11 -Wall
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/libbinary.a

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/BinaryLibUtil.o $(OBJDIR_DEBUG)/src/BinaryReader.o $(OBJDIR_DEBUG)/src/BinaryWriter.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/BinaryLibUtil.o $(OBJDIR_RELEASE)/src/BinaryReader.o $(OBJDIR_RELEASE)/src/BinaryWriter.o

all: debug release debug_w32 release_w32

clean: clean_debug clean_release clean_debug_w32 clean_release_w32

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(AR) rcs $(OUT_DEBUG) $(OBJ_DEBUG)

$(OBJDIR_DEBUG)/src/BinaryLibUtil.o: src/BinaryLibUtil.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/BinaryLibUtil.cpp -o $(OBJDIR_DEBUG)/src/BinaryLibUtil.o

$(OBJDIR_DEBUG)/src/BinaryReader.o: src/BinaryReader.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/BinaryReader.cpp -o $(OBJDIR_DEBUG)/src/BinaryReader.o

$(OBJDIR_DEBUG)/src/BinaryWriter.o: src/BinaryWriter.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/BinaryWriter.cpp -o $(OBJDIR_DEBUG)/src/BinaryWriter.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(AR) rcs $(OUT_RELEASE) $(OBJ_RELEASE)

$(OBJDIR_RELEASE)/src/BinaryLibUtil.o: src/BinaryLibUtil.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/BinaryLibUtil.cpp -o $(OBJDIR_RELEASE)/src/BinaryLibUtil.o

$(OBJDIR_RELEASE)/src/BinaryReader.o: src/BinaryReader.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/BinaryReader.cpp -o $(OBJDIR_RELEASE)/src/BinaryReader.o

$(OBJDIR_RELEASE)/src/BinaryWriter.o: src/BinaryWriter.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/BinaryWriter.cpp -o $(OBJDIR_RELEASE)/src/BinaryWriter.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

