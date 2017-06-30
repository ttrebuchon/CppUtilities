#pragma once
#include <type_traits>

namespace QUtils
{
namespace Types
{
	//Indexer/Subscript Forwarding
	namespace Internal
	{
		template <class...>
		using void_t = void;
		
		template <class T, class G, typename = void>
		struct has_subscript_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_subscript_op<T, G, void_t<decltype(std::declval<T>()[std::declval<G>()])>> : std::true_type
		{};
	}
	
	template <class T>
	class IndexerForward
	{
		protected:
		T* ptr;
		
		public:
		IndexerForward(T* t) : ptr(t)
		{}
		
		
		template <class G>
		typename std::enable_if<Internal::has_subscript_op<T, G>::value, decltype(std::declval<T>()[std::declval<G>()])>::type operator[](G g)
		{
			return (*ptr)[g];
		}
		
		template <class G>
		typename std::enable_if<Internal::has_subscript_op<const T, G>::value, decltype(std::declval<const T>()[std::declval<G>()])>::type operator[](G g) const
		{
			return (*ptr)[g];
		}
		
		
	};
	
	template <class T>
	using SubscriptForward = IndexerForward<T>;
	
	
	
	
	
	
	
	
	
}
}