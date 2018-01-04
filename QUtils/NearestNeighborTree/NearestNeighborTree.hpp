#ifndef INCLUDED_NEAREST_NEIGHBOR_TREE_HPP
#define INCLUDED_NEAREST_NEIGHBOR_TREE_HPP


#include "NearestNeighborTree.h"
#include <QUtils/Types/Void_t.h>
#include <QUtils/Types/IntegerSequence.h>
#include <cmath>

namespace QUtils
{
	
	namespace NNST_Helpers
	{
		template <class Dim, class ...Dims>
		struct EuclideanDist
		{
			typedef decltype(std::declval<Dim>() - std::declval<Dim>()) Diff;
			typedef decltype(std::declval<Diff>()*std::declval<Diff>() + std::declval<typename EuclideanDist<Dims...>::Sum>()) Sum;
			typedef decltype(sqrt(std::declval<Sum>())) type;
		};
		
		template <class Dim>
		struct EuclideanDist<Dim>
		{
			typedef decltype(std::declval<Dim>() - std::declval<Dim>()) Diff;
			typedef decltype(std::declval<Diff>()*std::declval<Diff>()) Sum;
			typedef decltype(sqrt(std::declval<Sum>())) type;
		};
		
		template <class Dim, class ...Dims>
		struct DiffTypes
		{
			private:
			typedef decltype(std::declval<Dim>() - std::declval<Dim>()) This_Diff;
			typedef std::tuple<This_Diff> This_Tuple;
			typedef typename DiffTypes<Dims...>::type Next_Type;
			
			public:
			typedef decltype(std::tuple_cat(std::declval<This_Tuple>(), std::declval<Next_Type>())) type;
		};
		
		template <class Dim>
		struct DiffTypes<Dim>
		{
			private:
			typedef decltype(std::declval<Dim>() - std::declval<Dim>()) This_Diff;
			typedef std::tuple<This_Diff> This_Tuple;
			
			public:
			typedef This_Tuple type;
		};
		
		template <class>
		struct GetDiffs;
		
		template <int I, int... Is>
		struct GetDiffs<QUtils::Types::Sequence<I, Is...>>
		{
		template <class Elem, class ...Dims>
		struct Inner
		{
			static_assert(I < sizeof...(Dims), "");
			private:
			typedef typename DiffTypes<Dims...>::type diff_type;
			
			public:
			
			static auto go(Elem* e, Elem* e2, const std::tuple<std::function<Dims(Elem*)>...>& funcs, diff_type& diff)
			{
				auto& func = std::get<I>(funcs);
				std::get<I>(diff) = func(e) - func(e2);
				
				typedef GetDiffs<QUtils::Types::Sequence<Is...>> NextOuter;
				typedef typename NextOuter::template Inner<Elem, Dims...> NextInner;
				NextInner::go(e, e2, funcs, diff);
			}
		};
		};
		
		template <int I>
		struct GetDiffs<QUtils::Types::Sequence<I>>
		{
		template <class Elem, class ...Dims>
		struct Inner
		{
			static_assert(I == sizeof...(Dims)-1, "");
			private:
			typedef typename DiffTypes<Dims...>::type diff_type;
			
			public:
			
			static auto go(Elem* e, Elem* e2, const std::tuple<std::function<Dims(Elem*)>...>& funcs, diff_type& diff)
			{
				auto& func = std::get<I>(funcs);
				std::get<I>(diff) = func(e) - func(e2);
			}
		};
		};
		
		template <class Elem, class ...Dims>
		struct GetDiffs_t
		{
			private:
			typedef typename DiffTypes<Dims...>::type diff_type;
			static_assert(std::tuple_size<diff_type>::value == sizeof...(Dims), "");
			
			public:
			
			static diff_type go(Elem* e, Elem* e2, const std::tuple<std::function<Dims(Elem*)>...>& funcs)
			{
				typedef typename QUtils::Types::SequenceGen<sizeof...(Dims)-1>::type Ints;
				typedef GetDiffs<Ints> Outer;
				typedef typename Outer::template Inner<Elem, Dims...> Type;
				diff_type diffs;
				Type::go(e, e2, funcs, diffs);
				return diffs;
			}
		};
		
		template <class, class>
		struct Tuple_Square;
		
		template <class T, int I>
		struct Tuple_Square<T, QUtils::Types::Sequence<I>>
		{
			static_assert(std::tuple_size<T>::value-1 == I, "");
			static void go(T& t)
			{
				std::get<I>(t) = std::get<I>(t)*std::get<I>(t);
			}
		};
		
		template <class T, int I, int... Is>
		struct Tuple_Square<T, QUtils::Types::Sequence<I, Is...>>
		{
			static void go(T& t)
			{
				std::get<I>(t) = std::get<I>(t)*std::get<I>(t);
				Tuple_Square<T, QUtils::Types::Sequence<Is...>>::go(t);
			}
		};
		
		template <class T, class R, class>
		struct Tuple_Sum_Imp;
		
		template <class T, class R, int I, int... Is>
		struct Tuple_Sum_Imp<T, R, QUtils::Types::Sequence<I, Is...>>
		{
			static void go(T& t, R& r)
			{
				r += std::get<I>(t);
				Tuple_Sum_Imp<T, R, QUtils::Types::Sequence<Is...>>::go(t, r);
			}
		};
		
		template <class T, class R, int I>
		struct Tuple_Sum_Imp<T, R, QUtils::Types::Sequence<I>>
		{
			static void go(T& t, R& r)
			{
				r += std::get<I>(t);
			}
		};
		
		
		template <class, class>
		struct Tuple_Sum;
		
		template <class T, int... Is>
		struct Tuple_Sum<T, QUtils::Types::Sequence<Is...>>
		{
			static auto go(T& t)
			{
				static_assert(sizeof...(Is) == std::tuple_size<T>::value, "");
				double sum = 0;
				Tuple_Sum_Imp<T, double, QUtils::Types::Sequence<Is...>>::go(t, sum);
				return sum;
				//return (std::get<Is>(t) + ...);
			}
		};
		
		
		
		template <class Elem, class, class ...Dims>
		struct Default_Dist
		{
			static std::function<double(Elem*, Elem*)> dist(const std::tuple<std::function<Dims(Elem*)>...>&)
			{
				return std::function<double(Elem*, Elem*)>();
			}
			
		};
		
		template <class Elem, class ...Dims>
		struct Default_Dist<Elem, QUtils::Types::void_t<typename EuclideanDist<Dims...>::type>, Dims...>
		{
			static std::function<double(Elem*, Elem*)> dist(const std::tuple<std::function<Dims(Elem*)>...>& funcs)
			{
				return [funcs](Elem* e1, Elem* e2) -> double
				{
					auto diffs = GetDiffs_t<Elem, Dims...>::go(e1, e2, funcs);
					Tuple_Square<decltype(diffs), typename QUtils::Types::SequenceGen<sizeof...(Dims)-1>::type>::go(diffs);
					return sqrt(Tuple_Sum<decltype(diffs), typename QUtils::Types::SequenceGen<sizeof...(Dims)-1>::type>::go(diffs));
				};
			}
		};
		
		template <class Elem, class ...Dims>
		using DefaultDist = Default_Dist<Elem, QUtils::Types::void_t<typename EuclideanDist<Dims...>::type>, Dims...>;
	}
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	NearestNeighbor<Elem, Dim1, Dims...>::NearestNeighbor(std::function<Dim1(Elem*)> f1, std::function<Dims(Elem*)>... fs) : root(NULL)
	{
		ProcFuncs(f1, fs...);
		dist = NNST_Helpers::DefaultDist<Elem, Dim1, Dims...>::dist(funcs);
	}
	
	
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	template <typename D, typename ...Ds>
	void NearestNeighbor<Elem, Dim1, Dims...>::ProcFuncs(std::function<D(Elem*)> f, std::function<Ds(Elem*)>... fs)
	{
		funcs = std::make_tuple(f, fs...);
	}
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	void NearestNeighbor<Elem, Dim1, Dims...>::insert(Elem* e)
	{
		Node* n = new Node(e, &funcs);
		if (root == NULL)
		{
			root = n;
		}
		else
		{
			root = root->template insert<0>(n);
		}
	}
	
	template <typename Elem, typename Dim1, typename ...Dims>
	int NearestNeighbor<Elem, Dim1, Dims...>::size()
	{
		if (root == NULL)
		{
			return 0;
		}
		return root->size();
	}
	
	template <typename Elem, typename Dim1, typename ...Dims>
	std::vector<Elem*> NearestNeighbor<Elem, Dim1, Dims...>::traverse(Elem* e, int n)
	{
		std::vector<Elem*> results;
		
		root->template traverse<0>(e, n, &results, &dist);
		
		return results;
	}
}

#endif