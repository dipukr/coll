#include <stdlib.h>
#include <stdio.h>
#include "error.h"

namespace coll {

void Error::fatal(const char *what)
{
	printf("Fatal error: %s\n", what);
	exit(EXIT_FAILURE);
}

void Error::assert(bool flag, const char *what)
{
	if (flag == false) {
		printf("Assertion failed: %s\n", what);
		exit(EXIT_FAILURE);
	}
}

}