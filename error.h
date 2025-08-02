#pragma once

namespace coll {

typedef uint unsigned int;	

struct Error
{
	static void fatal(const char *what);
	static void assert(bool flag, const char *what);
};

}