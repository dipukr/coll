#include <stdarg.h>
#include <stdio.h>
#include "error.h"
#include "chars.h"

namespace coll {

CharArray::CharArray(char c)
{
	count = 1;
	total = count + 1;
	chars = new char[total];
	chars[0] = c;
	chars[1] = 0;
}

CharArray::CharArray(size_t sz)
{
	count = 0;
	total = sz;
	chars = new char[total];
	chars[0] = 0;
}

CharArray::CharArray(size_t size, char c)
{
	count = size;
	total = size + 1;
	chars = new char[total];
	memset(chars, c, count);
	chars[count] = 0;
}

CharArray::CharArray(const char* str)
{
	count = strlen(str);
	total = count + 1;
	chars = new char[total];
	strcpy(chars, str);
}

CharArray::CharArray(const CharArray &arg)
{
	count = arg.size();
	total = count + 1;
	chars = new char[total];
	strcpy(chars, arg.chars);
}

CharArray::~CharArray()
{
	if (chars != nullptr)
		delete[] chars;
}

void CharArray::operator=(const CharArray &rhs)
{
	if (this != &rhs) {
		delete[] chars;
		count = rhs.count;
		total = rhs.total;
		chars = new char[total];
		strcpy(chars, rhs.chars);
	}
}

void CharArray::operator+=(const CharArray &rhs)
{
	size_t ncount = count + rhs.count;
	if (ncount >= total) {
		total = ncount * 2;
		char *ptr = chars;
		chars  = new char[total];
		strcpy(chars, ptr);
		delete[] ptr;
	}
	strcpy(chars + count, rhs.chars);
	count = ncount;
}

CharArray CharArray::operator+(const CharArray &rhs)
{
	CharArray result(*this);
	result += rhs;
	return result;
}

char& CharArray::operator[](size_t index)
{
	if (index >= count) Error::fatal("Array index out of bound.");
	return chars[index];
}

char CharArray::operator[](size_t index) const
{
	if (index >= count) Error::fatal("Array index out of bound.");
	return chars[index];
}

void CharArray::clear()
{
	count = 0;
	total = 0;
	chars[0] = 0;
}

void CharArray::resize(size_t sz)
{
	total = sz;
	if (sz < count) count = sz;
	char *pt = chars;
	chars = new char[sz];
	memset(chars, 0, sz);
	memcpy(chars, pt, count);
}

size_t CharArray::findFirstOf(char c) const
{
	if (c == 0) return CharArray::NO_POS;
	char *ptr = strchr(chars, c);
	return ptr != nullptr ? ptr - chars : CharArray::NO_POS;
}

size_t CharArray::findLastOf(char c) const
{
	if (c == 0) return CharArray::NO_POS;
	char *ptr = strrchr(chars, c);
	return ptr != nullptr ? ptr - chars: CharArray::NO_POS;
}

CharArray CharArray::substr(size_t start, size_t end) const
{
	if (start >= count or end >= count) Error::fatal("CharArray index out of bound.");
	size_t len = end - start;
	CharArray charArray(len, 0);
	memcpy(charArray.chars, chars + start, len);
	return charArray;
}

CharArray CharArray::sub(size_t start, size_t sz) const
{
	if (start + sz > count) Error::fatal("CharArray index out of bound.");
	CharArray charArray(sz, 0);
	memcpy(charArray.chars, chars + start, sz);
	return charArray;
}

CharArray CharArray::leftPart(size_t end) const 
{
	if (end >= count) Error::fatal("CharArray index out of bound.");
	return substr(0, end);
}

CharArray CharArray::rightPart(size_t start) const
{
	if (start >= count) Error::fatal("CharArray index out of bound.");
	return substr(start, count - 1);
}

CharArray CharArray::format(const char *fmt, ...)
{
	char buf[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 256, fmt, args);
	va_end(args);
	return buf;
}

CharArray CharArray::of(int8_t i)
{
	char buf[20];
	sprintf(buf, "%d", i);
	return buf;
}

CharArray CharArray::of(int16_t i)
{
	char buf[20];
	sprintf(buf, "%d", i);
	return buf;
}

CharArray CharArray::of(int32_t i)
{
	char buf[20];
	sprintf(buf, "%d", i);
	return buf;
}

CharArray CharArray::of(int64_t i)
{
	char buf[20];
	sprintf(buf, "%l", i);
	return buf;
}

CharArray CharArray::of(uint8_t i)
{
	char buf[20];
	sprintf(buf, "%u", i);
	return buf;
}

CharArray CharArray::of(uint16_t i)
{
	char buf[20];
	sprintf(buf, "%u", i);
	return buf;
}

CharArray CharArray::of(uint32_t i)
{
	char buf[20];
	sprintf(buf, "%u", i);
	return buf;
}

CharArray CharArray::of(uint64_t i)
{
	char buf[20];
	sprintf(buf, "%ul", i);
	return buf;
}

CharArray CharArray::of(float f)
{
	char buf[20];
	sprintf(buf, "%f", f);
	return buf;
}

CharArray CharArray::of(double f)
{
	char buf[20];
	sprintf(buf, "%f", f);
	return buf;
}

}
