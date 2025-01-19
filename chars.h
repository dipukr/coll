#ifndef COLL_CHARS_H
#define COLL_CHARS_H

#include <string.h>
#include <stdint.h>

namespace coll {

class CharArray
{
	char *chars = nullptr;
	size_t total = 0;
	size_t count = 0;	
public:
	CharArray(char c);
	CharArray(size_t size);
	CharArray(size_t size, char c);
	CharArray(const char *str = "");
	CharArray(const CharArray &arg);
	
	virtual ~CharArray();

	void operator=(const CharArray &rhs);
	void operator+=(const CharArray &rhs);

	CharArray operator+(const CharArray &rhs);

	char& operator[](size_t index);
	char operator[](size_t index) const;
	
	CharArray substr(size_t start, size_t end) const;
	CharArray sub(size_t start, size_t sz) const;
	CharArray rightPart(size_t start) const;
	CharArray leftPart(size_t end) const;

	size_t findFirstOf(char c) const;
	size_t findLastOf(char c) const;
	
	void resize(size_t sz);
	void clear();

	size_t size() const {return count;}
	bool empty() const {return size() == 0;}
	bool notEmpty() const {return !empty();}
	const char* cstr() const {return chars;}

	static const size_t NO_POS = -1;
	static CharArray format(const char *fmt, ...);
	
	static CharArray of(int8_t i);
	static CharArray of(int16_t i);
	static CharArray of(int32_t i);
	static CharArray of(int64_t i);
	static CharArray of(uint8_t i);
	static CharArray of(uint16_t i);
	static CharArray of(uint32_t i);
	static CharArray of(uint64_t i);
	static CharArray of(float f);
	static CharArray of(double f);

	bool operator==(const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) == 0;}
	bool operator!=(const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) != 0;}
	bool operator< (const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) <  0;}
	bool operator<=(const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) <= 0;}
	bool operator> (const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) >  0;}
	bool operator>=(const CharArray &rhs) const {return strcmp(this->chars, rhs.chars) >= 0;}
};

}

#endif