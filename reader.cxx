#include <assert.h>
#include "reader.h"
#include "error.h"

namespace neem {

file_reader::file_reader(const char *file)
{
	stream = fopen(file, "rb");
	assert(stream !=  nullptr);
	fseek(stream, 0, SEEK_END);
	size = (U64) ftell(stream);
	fseek(stream, 0, SEEK_SET);
}

file_reader::~file_reader()
{
	fclose(stream);
}

void file_reader::read(S8  &v) {read((char*) &v, sizeof(v));}
void file_reader::read(U8  &v) {read((char*) &v, sizeof(v));}
void file_reader::read(S16 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(U16 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(S32 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(U32 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(S64 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(U64 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(F32 &v) {read((char*) &v, sizeof(v));}
void file_reader::read(F64 &v) {read((char*) &v, sizeof(v));}

void file_reader::read(value &v)
{
	read(v.type);
	switch (v.type) {
	case Data::I64: read(v.i64); break;
	case Data::F64: read(v.f64); break;
	case Data::STR: read(v.str);  break;
	case Data::FUN: read(v.fun); break;
	case Data::CLS: read(v.cls); break;
	default: assert(false);
	}
}

void file_reader::read(text* &v)
{
	char str[1024];
	U32 len(0);
	read(len);
	assert(len < 1024);
	read(str, len);
	str[len] = 0;
	v = new text(str);
}

void file_reader::read(code* &v)
{
	v = (code*) malloc(sizeof(code));
	v->is_native = 0;
	read(v->id);
	read(v->argc);
	read(v->varc);
	read(v->addr);
}

void file_reader::read(clas_s* &v)
{
	v = (clas_s*) malloc(sizeof(clas_s));
	read(v->id);
	read(v->data_count);
}

void file_reader::read(char *dest, U64 sz) 
{
	U64 rd = fread(dest, sz, 1, stream);
	assert(rd == 1);
}

void file_reader::seek(U64 pos)
{
	assert(pos < size);
	fseek(stream, pos, SEEK_SET);
}

size_t file_reader::file_size()
{
	return size;
}

void file_reader::close()
{
	fclose(stream);
}

mem_reader::mem_reader(U8 *src, U64 sz)
{
	mem = src;
	loc = mem;
	mem_total = sz;
	assert(mem != nullptr);
}

void mem_reader::read(S8 &val)
{
	val = *(S8*) loc;
	loc += sizeof(S8);
}

void mem_reader::read(U8 &val)
{
	val = *(U8*) loc;
	loc += sizeof(U8);
}

void mem_reader::read(S16 &val)
{
	val = *(S16*) loc;
	loc += sizeof(S16);
}

void mem_reader::read(U16 &val)
{
	val = *(U16*) loc;
	loc += sizeof(U16);
}

void mem_reader::read(S32 &val)
{
	val = *(S32*) loc;
	loc += sizeof(S32);
}

void mem_reader::read(U32 &val)
{
	val = *(U32*) loc;
	loc += sizeof(U32);
}

void mem_reader::read(S64 &val)
{
	val = *(S64*) loc;
	loc += sizeof(S64);
}

void mem_reader::read(U64 &val)
{
	val = *(U64*) loc;
	loc += sizeof(U64);
}

void mem_reader::read(F32 &val)
{
	val = *(F32*) loc;
	loc += sizeof(F32);
}

void mem_reader::read(F64 &val)
{
	val = *(F64*) loc;
	loc += sizeof(F64);
}

void mem_reader::read(char* &s)
{
	U32 sz = 0;
	read(sz);
	s = (char*) malloc(sz + 1);
	for (U32 a = 0; a < sz; a++)
		*(s + a) = loc[a];
	s[sz] = 0;
	loc += sz;
}

}
