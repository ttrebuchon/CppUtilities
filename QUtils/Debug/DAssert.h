#pragma once

#ifdef DEBUG
#include <cassert>
#define dassert(x) assert(x)
#else
#define dassert(x)
#endif