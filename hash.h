#ifndef COLL_HASH_H
#define COLL_HASH_H

#include <stdint.h>
#include <stddef.h>
#include "chars.h"

namespace coll {

size_t hash(size_t key);
size_t hash(int key);
size_t hash(float key);
size_t hash(double key);
size_t hash(const CharArray &charArray);

}

#endif