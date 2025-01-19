#include <iostream>
#include "queue.h"
#include "stack.h"
#include "array.h"
#include "chars.h"
#include "heap.h"
#include "list.h"
#include "set.h"
#include "map.h"

bool palindrome(CharArray &ca, size_t l, size_t r)
{
	if (l >= r) return true;
	if (ca[l] != ca[r]) return false;
	return palindrome(ca, l + 1, r - 1);
}

int main(const int argc, const char **argv)
{
	std::cout << "hello.world" << std::endl;
	return EXIT_SUCCESS;
}