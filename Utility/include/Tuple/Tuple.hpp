#pragma once


#include "Tuple.h"

namespace Util
{
	namespace Tuple_Helpers
	{
		template <int ...Nums>
		struct seq {};
		
		template <int N, int ...Nums>
		struct seqgen
		{
			static_assert(N > 0, "Invalid argument to seqgen");
			typedef typename seqgen<N-1, N, Nums...>::type type;
		};
		
		template <int ...Nums>
		struct seqgen<0, Nums...>
		{
			typedef seq<0, Nums...> type;
		};
		
		template <typename Y, typename ...T, int ...N>
		auto useAsArgs_Helper(Y y, const std::tuple<T...>& tup, seq<N...>)
		{
			
			return y(std::get<N>(tup)...);
		}
		
		template <typename ...T>
		Tuple<T...> con_Helper(T... t)
		{
			return Tuple<T...>(t...);
		}
		
		template <typename ...T, int ...N>
		auto takeFront_Helper(const std::tuple<T...>& tup, seq<N...>)
		{
			return con_Helper(std::get<N>(tup)...);
		}
		
		template <typename ...T, int ...N>
		auto takeBack_Helper(const std::tuple<T...>& tup, seq<N...>)
		{
			return con_Helper(std::get<sizeof...(T) - sizeof...(N) + N>(tup)...);
		}
		
		template <int N, int Size>
		struct equals_Helper
		{
			template <typename ...T, typename ...U>
			static bool call(Tuple<T...>& t, Tuple<U...>& u)
			{
				if (t.template get<N>() != u.template get<N>())
				{
					return false;
				}
				
				return equals_Helper<N+1, Size>::call(t, u);
			}
		};
		
		template <int Size>
		struct equals_Helper<Size, Size>
		{
			template <typename ...T, typename ...U>
			static bool call(Tuple<T...>& t, Tuple<U...>& u)
			{
				return true;
			}
		};
		
	}
	
	
	
	template <typename ...T>
	template <int index>
	auto& Tuple<T...>::get()
	{
		return std::get<index>(inner);
	}
	
	template <typename ...T>
	template <typename ...U>
	Tuple<T..., U...> Tuple<T...>::append(const U... u)
	{
		return Tuple<T..., U...>(std::tuple_cat(inner, std::make_tuple(u...)));
	}
	
	template <typename ...T>
	template <typename ...U>
	Tuple<U..., T...> Tuple<T...>::prepend(const U... u)
	{
		return Tuple<U..., T...>(std::tuple_cat(std::make_tuple(u...), inner));
	}
	
	template <typename ...T>
	template <typename ...U>
	Tuple<T..., U...> Tuple<T...>::concat(const Tuple<U...> u)
	{
		return Tuple<T..., U...>(std::tuple_cat(inner, u.inner));
	}
	
	template <typename ...T>
	template <typename Y>
	auto Tuple<T...>::useAsArgs(Y y)
	{
		return Tuple_Helpers::useAsArgs_Helper(y, inner, typename Tuple_Helpers::seqgen<sizeof...(T)-1>::type());
	}
	
	template <typename ...T>
	template <int Count>
	auto Tuple<T...>::takeFront()
	{
		typename Tuple_Helpers::seqgen<Count-1>::type seq;
		return Tuple_Helpers::takeFront_Helper(inner, seq);
	}
	
	template <typename ...T>
	template <int Count>
	auto Tuple<T...>::takeBack()
	{
		typename Tuple_Helpers::seqgen<Count-1>::type seq;
		
		return Tuple_Helpers::takeBack_Helper(inner, seq);
	}
	
	template <typename ...T>
	template <typename ...U>
	bool Tuple<T...>::operator==(Tuple<U...> u)
	{
		if (sizeof...(T) != sizeof...(U))
		{
			return false;
		}
		
		return Tuple_Helpers::equals_Helper<0, sizeof...(T)>::call(*this, u);
		
	}
	
	template <typename... T>
	Tuple<T...> Tuple<T...>::make(T... args)
	{
		return Tuple<T...>(args...);
	}
	
	template <typename... T>
	Tuple<T...> Tuple<T...>::make(std::tuple<T...> tup)
	{
		return Tuple<T...>(tup);
	}
	
	template <typename... T>
	Tuple<T...> Make_Tuple(std::tuple<T...> tup)
	{
		return Tuple<T...>(tup);
	}
	
	
	
}
