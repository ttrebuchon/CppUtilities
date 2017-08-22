#pragma once

#include "IntegerSequence.h"

namespace QUtils::Types
{
	template <class... Types>
	struct TypeSizes
	{
		typedef Sequence<(sizeof(Types))...> type;
	};
	
	template <class... Types>
	struct TypeSizes<std::tuple<Types...>> : public TypeSizes<Types...>
	{
		
	};
	
	template <class... Types>
	struct MaxTypeSize
	{
		constexpr static int Max = TypeSizes<Types...>::type::Max();
		
		constexpr static int value = TypeSizes<Types...>::type::Max();
	};
	
	template <class... Types>
	struct MaxTypeSize<std::tuple<Types...>> : public MaxTypeSize<Types...>
	{
	};
	
	
	
	template <class... Types>
	struct MinTypeSize
	{
		constexpr static int Min = TypeSizes<Types...>::type::Min();
		
		constexpr static int value = TypeSizes<Types...>::type::Min();
	};
	
	template <class... Types>
	struct MinTypeSize<std::tuple<Types...>> : public MinTypeSize<Types...>
	{
	};
	
	
	
	template <int Size>
	struct TypeWithSize
	{
		static_assert(Size >= 1, "Cannot create type with a negative size");
		private:
		char data[Size];
	};
	
	
}