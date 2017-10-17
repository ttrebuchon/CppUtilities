#pragma once



#define QUTILS_FLAG_ENUM_OPS(Type) \
\
\
\
\
inline Type& operator|=(Type& a, const Type b) \
{ \
	reinterpret_cast<int&>(a) |= static_cast<int>(b); \
	return a; \
} \
\
inline Type& operator&=(Type& a, const Type b) \
{ \
	reinterpret_cast<int&>(a) &= static_cast<int>(b); \
	return a; \
} \
\
\
\
inline Type operator|(Type a, const Type b) \
{ \
	a |= b; \
	return a; \
} \
\
\
\
inline Type operator&(Type a, const Type b) \
{ \
	a &= b; \
	return a; \
}


