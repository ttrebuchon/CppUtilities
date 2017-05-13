#pragma once

#include <tuple>

namespace Util
{
	template <typename ...T>
	class Tuple;
	
	namespace _Helpers
	{
		
	}
	
	
	template <typename ...T>
	class Tuple
	{
		private:
		
		protected:
		std::tuple<T...> inner;
		
		public:
		Tuple(std::tuple<T...> tup) : inner(tup)
		{ }
		Tuple(T... args) : inner(std::make_tuple(args...))
		{ }
		Tuple() : inner()
		{ }
		
		template <int index>
		auto& get();
		
		template <typename ...U>
		Tuple<T..., U...> append(const U... u);
		
		template <typename ...U>
		Tuple<U..., T...> prepend(const U... u);
		
		template <typename ...U>
		Tuple<T..., U...> concat(const Tuple<U...> u);
		
		template <typename ...U>
		Tuple<T..., U...> cat(const Tuple<U...> u) { return concat(u); }
		
		template <typename Y>
		auto useAsArgs(Y y);
		
		constexpr std::size_t count() const
		{ return sizeof...(T); }
		
		template <int Count>
		auto takeFront();
		
		template <typename ...U>
		bool operator==(Tuple<U...> u);
		
		
	};
	
	
	
	
}


#include "Tuple.hpp"