#pragma once
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "struct.h"

namespace coll {

class FileWriter
{
	FILE *stream = nullptr;

public:
	FileWriter(const char *file);
	~FileWriter();
	void close();
	
	void write(S8  val);
	void write(U8  val);
	void write(S16 val);
	void write(U16 val);
	void write(S32 val);
	void write(U32 val);
	void write(S64 val);
	void write(U64 val);
	void write(F32 val);
	void write(F64 val);
	void write(String &v);
	void write(const char *src, U64 sz);
};

class MemoryWriter
{
	U8 *mem = nullptr;
	U8 *loc = nullptr;
	U64 mem_total = 0;

public:
	mem_writer(U64 sz);
	~mem_writer();

	U8* get_mem();
	U64 size();
	void reset();

	void write(S8  val);
	void write(U8  val);
	void write(S16 val);
	void write(U16 val);
	void write(S32 val);
	void write(U32 val);
	void write(S64 val);
	void write(U64 val);
	void write(F32 val);
	void write(F64 val);
	void write(char* s);

}

#endif