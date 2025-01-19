#ifndef NEEM_READER_H
#define NEEM_READER_H

#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include "struct.h"

namespace neem {

class file_reader
{
	FILE *stream = nullptr;
	U64 size = 0;

public:
	file_reader(const char *file);
	~file_reader();

	void seek(U64 loc);
	U64 file_size();
	void close();
	
	void read(S8  &val);
	void read(U8  &val);
	void read(S16 &val);
	void read(U16 &val);
	void read(S32 &val);
	void read(U32 &val);
	void read(S64 &val);
	void read(U64 &val);
	void read(F32 &val);
	void read(F64 &val);
	void read(text* &v);
	void read(value &v);
	void read(code* &v);
	void read(clas_s* &v);
	void read(char *dest, U64 sz);	
};


class mem_reader
{
	U8 *mem = nullptr;
	U8 *loc = nullptr;
	U64 mem_total = 0;

public:
	mem_reader(U8 *src, U64 sz);
	void reset();

	void read(S8  &val);
	void read(U8  &val);
	void read(S16 &val);
	void read(U16 &val);
	void read(S32 &val);
	void read(U32 &val);
	void read(S64 &val);
	void read(U64 &val);
	void read(F32 &val);
	void read(F64 &val);
	void read(char* &s);
};

}

#endif