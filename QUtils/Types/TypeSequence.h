#pragma once

#include <tuple>

namespace QUtils
{
namespace Types
{
	template <class... T>
	using TypeSequence = std::tuple<T...>;
	
	
	template <template <class...> class, class>
	struct TemplateFromTupleTypes
	{ };
	
	template <template <class...> class T, class ...G>
	struct TemplateFromTupleTypes<T, std::tuple<G...>>
	{
		typedef T<G...> type;
	};
	
	template <template <class...> class T, class G>
	using ApplyTemplateSequence = TemplateFromTupleTypes<T, G>;
	
	template <template <class...> class T, class G>
	using TemplateFromSequence = TemplateFromTupleTypes<T, G>;
	
	
	
	template <class A, class... B>
	struct ReverseSequence
	{
		typedef decltype(std::tuple_cat(std::declval<typename ReverseSequence<B...>::type>(), std::declval<std::tuple<A>>())) type;
	};
	
	template <class A>
	struct ReverseSequence<A>
	{
		typedef std::tuple<A> type;
	};
	
	
	
	template <int N, class A, class... B>
	struct ExcludeFirstN
	{
		static_assert(N > 0, "");
		typedef typename ExcludeFirstN<N-1, B...>::type type;
	};
	
	template <class A, class... B>
	struct ExcludeFirstN<0, A, B...>
	{
		typedef std::tuple<A, B...> type;
	};
	
	template <class A>
	struct ExcludeFirstN<0, A>
	{
		typedef std::tuple<A> type;
	};
	
	template <class A>
	struct ExcludeFirstN<1, A>
	{
		typedef std::tuple<> type;
	};
	
	template <int N, class A, class... B>
	struct TakeFirstN
	{
		static_assert(N > 1, "");
		typedef decltype(std::tuple_cat(std::declval<A>(), std::declval<typename TakeFirstN<N-1, B...>::type>())) type;
		
	};
	
	template <class A, class... B>
	struct TakeFirstN<1, A, B...>
	{
		typedef std::tuple<A> type;
	};
	
	template <class A>
	struct TakeFirstN<1, A>
	{
		typedef std::tuple<A> type;
	};
	
	
	
	
	
	template <int N, class A, class... B>
	struct ExcludeLastN
	{
		static_assert(N <= sizeof...(B)+1, "");
		static_assert(sizeof...(B)+1-N >= 1, "");
		
		typedef typename TakeFirstN<sizeof...(B)+1-N, A, B...>::type type;
	};
	
	
	
	
	
	
	template <class A, class... B>
	struct LastType : public LastType<B...>
	{
	};
	
	template <class A>
	struct LastType<A>
	{
		typedef A type;
	};
	
	template <class A, class... B>
	struct FirstType
	{
		typedef A type;
	};
	
	template <class... A>
	struct FirstTypeOrVoid;
	
	template <>
	struct FirstTypeOrVoid<>
	{
		typedef void type;
	};
	
	template <class... A>
	struct FirstTypeOrVoid : public FirstType<A...> { };
	
	
	template <class T>
	struct ExtractArgs
	{
		
	};
	
	template <template <class...> class T, class ...A>
	struct ExtractArgs<T<A...>>
	{
		typedef std::tuple<A...> type;
	};
	
	
	
	template <class A, class ...B>
	struct Concat
	{
		typedef std::tuple<A, B...> type;
	};
	
	template <class ...TupTypes, class T>
	struct Concat<std::tuple<TupTypes...>, T>
	{
		typedef decltype(
		std::tuple_cat(
		std::declval<
			std::tuple<TupTypes...>
		>(), 
		std::declval<T>()
		)) 
		type;
	};
	
	template <class ...TupTypes, class T>
	struct Concat<T, std::tuple<TupTypes...>>
	{
		typedef decltype(
		std::tuple_cat(
		std::declval<
			std::tuple<T>
		>(),
		std::declval<
			std::tuple<TupTypes...>
		>()
		)) 
		type;
	};
	
	
	
	template <class T>
	struct IsTuple : public std::false_type
	{ };
	
	template <class... T>
	struct IsTuple<std::tuple<T...>> : public std::true_type
	{ };
	
	
	
	
	
	namespace Helpers
	{
		template <class Tuple_t, int Index, class A, class ...B>
		struct RemoveType_Helper : public RemoveType_Helper<Concat<Tuple_t, A>, Index-1, B...>
		{
			static_assert(Index >= 0, "");
		};
		
		template <class Tuple_t, class A, class ...B>
		struct RemoveType_Helper<Tuple_t, 0, A, B...>
		{
			typedef typename Concat<Tuple_t, std::tuple<B...>>::type type;
		};
	}
	
	template <int Index, class A, class... B>
	struct RemoveType : public Helpers::RemoveType_Helper<std::tuple<A>, Index-1, B...>
	{ };
	
	template <class A, class... B>
	struct RemoveType<0, A, B...>
	{
		typedef std::tuple<B...> type;
	};
	
	
	
	
	
	namespace Helpers
	{
		template <class Tup, template <class> class X, class... Y>
		struct ForEachType;
		
		
		template <class Tup, template <class> class X, class T, class... Y>
		struct ForEachType<Tup, X, T, Y...>
		{
			typedef typename ForEachType<typename Types::Concat<Tup, X<T>>::type, X, Y...>::type type;
		};
		
		template <class Tup, template <class> class X>
		struct ForEachType<Tup, X>
		{
			typedef Tup type;
		};
	}
	
	
	template <template <class> class X, class T, class... Y>
	struct ForEachType
	{
		typedef typename Helpers::ForEachType<std::tuple<X<T>>, X, Y...>::type type;
	};
}
}