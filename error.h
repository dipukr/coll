#ifndef COLL_ERROR_H
#define COLL_ERROR_H

namespace coll {

struct Error
{
	static void fatal(const char *what);
	static void assert(bool flag, const char *what);
};

}

#endif