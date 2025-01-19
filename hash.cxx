#include "hash.h"

namespace coll {

size_t hash(size_t key) {return size_t(key);}
size_t hash(int key) {return size_t(key);}
size_t hash(float key)    {return size_t(key);}
size_t hash(double key)   {return size_t(key);}
size_t hash(const CharArray &charArray) {
	size_t h = 0;
	for (size_t it = 0; it < charArray.size(); it++)
		h = 31 * h + charArray[it];
	return (h & 0x7fffffff);
}

}