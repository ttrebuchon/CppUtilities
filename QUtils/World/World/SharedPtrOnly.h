#pragma once
#include <memory>

#define SHARED_PTR_ONLY(X) \
typedef std::shared_ptr<X> Ptr; \
typedef std::shared_ptr<const X> CPtr; \
template <class... Args> \
static Ptr Create(Args... args) \
{ \
	return Ptr(new X(args...)); \
}

