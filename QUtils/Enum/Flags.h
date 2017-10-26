#pragma once



#define QUTILS_FLAG_ENUM_OPS(Type) \
\
\
\
\
constexpr inline Type operator|(const Type a, const Type b) \
{ \
	return static_cast<Type>(static_cast<int>(a) | static_cast<int>(b)); \
} \
\
\
constexpr inline Type operator&(const Type a, const Type b) \
{ \
	return static_cast<Type>(static_cast<int>(a) & static_cast<int>(b)); \
} \
\
constexpr inline bool operator&&(const Type a, const Type b) \
{ \
	return (static_cast<int>(a) & static_cast<int>(b)) > 0; \
} \
\
\
\
\
constexpr inline Type& operator|=(Type& a, const Type b) \
{ \
	a = a | b; \
	return a; \
} \
\
constexpr inline Type& operator&=(Type& a, const Type b) \
{ \
	a = a & b; \
	return a; \
}

