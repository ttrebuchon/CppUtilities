#pragma once
#include <type_traits>


#define QUTILS_HASMETHOD(x) \
	template <typename, typename T> \
	struct has_##x##_method \
	{ \
	static_assert(std::integral_constant<T, false>::value, "Second type parameter needs to be a function type."); \
	}; \
	 \
	template <typename C, typename Ret, typename ...Args> \
	struct has_##x##_method<C, Ret(Args...)> \
	{ \
		private: \
		template <class T> \
		static constexpr auto check(T*) -> typename std::is_same<decltype( std::declval<T>(). x ( std::declval<Args>()...)), Ret>::type; \
		\
		template <class> \
		static constexpr std::false_type check(...); \
		\
		typedef decltype(check<C>(0)) type; \
		\
		public: \
		static constexpr bool value = type::value; \
	}
	