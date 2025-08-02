#include "writer.h"
#include "error.h"

namespace neem {

FileWriter::FileWriter(const char *filename)
{
	stream = fopen(filename, "wb");
	if (stream == nullptr)
		fatal("file open error");
}

FileWriter::~FileWriter()
{
	fclose(stream);
}



void FileWriter::write(S8  v) {write((char*) &v, sizeof(v));}
void FileWriter::write(U8  v) {write((char*) &v, sizeof(v));}
void FileWriter::write(S16 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(U16 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(S32 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(U32 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(S64 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(U64 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(F32 v) {write((char*) &v, sizeof(v));}
void FileWriter::write(F64 v) {write((char*) &v, sizeof(v));}

void FileWriter::write(text &v)
{
	U32 sz = v.size();
	write(sz);
	write((char*) v.cstr(), sz);
}

void FileWriter::write(value &v)
{

}

void FileWriter::write(code *v)
{

}

void FileWriter::write(clas_s *v)
{

}

void FileWriter::write(const char *src, U64 sz)
{
	U64 wr = fwrite(src, sz, 1, stream);
	assert(wr == 1);
}

void FileWriter::close()
{
	fclose(stream); 
}

MemWriter::MemWriter(U64 sz)
{
	mem = (U8*) malloc(sz);
	assert(mem != nullptr);
	loc = mem;
	mem_total = sz;
}

MemWriter::~MemWriter()
{
	free(mem);
	loc = nullptr;
	mem = nullptr;
}

U8* MemWriter::get_mem()
{
	return mem;
}

U64 MemWriter::size()
{
	return mem_total;
}

void MemWriter::write(S8 val)
{
	*(S8*) loc = val;
	loc += sizeof(S8);
}

void MemWriter::write(U8 val)
{
	*(U8*) loc = val;
	loc += sizeof(U8);
}

void MemWriter::write(S16 val)
{
	*(S16*) loc = val;
	loc += sizeof(S16);
}

void MemWriter::write(U16 val)
{
	*(U16*) loc = val;
	loc += sizeof(U16);
}

void MemWriter::write(S32 val)
{
	*(S32*) loc = val;
	loc += sizeof(S32);
}

void MemWriter::write(U32 val)
{
	*(U32*) loc = val;
	loc += sizeof(U32);
}

void MemWriter::write(S64 val)
{
	*(S64*) loc = val;
	loc += sizeof(S64);
}

void MemWriter::write(U64 val)
{
	*(U64*) loc = val;
	loc += sizeof(U64);
}

void MemWriter::write(F32 val)
{
	*(F32*) loc = val;
	loc += sizeof(F32);
}

void MemWriter::write(F64 val)
{
	*(F64*) loc = val;
	loc += sizeof(F64);
}

void MemWriter::write(char* s)
{
	if (s == nullptr) return;
	U32 sz = strlen(s);
	write(sz);
	for (U32 a = 0; a < sz; a++)
		*(loc + a) = s[a];
	loc += sz;
}

}