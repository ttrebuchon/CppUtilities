#pragma once
#include <type_traits>
#include "Void_t.h"

namespace QUtils
{
namespace Types
{
	//Indexer/Subscript Forwarding
	namespace Internal
	{
		
		template <class T, class G, typename = void>
		struct has_subscript_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_subscript_op<T, G, void_t<decltype(std::declval<T>()[std::declval<G>()])>> : std::true_type
		{};
		
		
		
		
		template <class T, class G, typename = void>
		struct has_greater_than_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_greater_than_op<T, G, void_t<decltype(std::declval<T>() > std::declval<G>())>> : std::true_type
		{};
		
		
		
		template <class T, class G, typename = void>
		struct has_less_than_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_less_than_op<T, G, void_t<decltype(std::declval<T>() < std::declval<G>())>> : std::true_type
		{};
		
		
		template <class T, class G, typename = void>
		struct has_greater_than_equal_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_greater_than_equal_op<T, G, void_t<decltype(std::declval<T>() >= std::declval<G>())>> : std::true_type
		{};
		
		
		
		template <class T, class G, typename = void>
		struct has_less_than_equal_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_less_than_equal_op<T, G, void_t<decltype(std::declval<T>() <= std::declval<G>())>> : std::true_type
		{};
		
		
		
		
		
		
		
		template <class T, class G, typename = void>
		struct has_addition_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_addition_op<T, G, void_t<decltype(std::declval<T>() + std::declval<G>())>> : std::true_type
		{};
		
	
		template <class T, class G, typename = void>
		struct has_subtraction_op : std::false_type
		{};
		
		template <class T, class G>
		struct has_subtraction_op<T, G, void_t<decltype(std::declval<T>() - std::declval<G>())>> : std::true_type
		{};
		
		
		
		
		
		
		
		template <class T, typename = void, class... G>
		struct has_invoke_op : std::false_type
		{};
		
		template <class T, class... G>
		struct has_invoke_op<T, void_t<decltype(std::declval<T>()( (std::declval<G>())...))>, G...> : std::true_type
		{};
		
		
		
		
		
		/*template <class T, typename = void>
		struct has_iterator_begin_op : std::false_type
		{};
		
		template <class T>
		struct has_iterator_begin_op<T, void_t<decltype(std::declval<T>().begin())>> : std::true_type
		{};
		
		template <class T, typename = void>
		struct has_iterator_end_op : std::false_type
		{};
		
		template <class T>
		struct has_iterator_end_op<T, void_t<decltype(std::declval<T>().end())>> : std::true_type
		{};*/
		
		
		
		
		template <class T, typename = void>
		struct has_iterator_begin_op : std::false_type
		{};
		
		template <class T>
		struct has_iterator_begin_op<T, void_t<decltype(std::declval<T>().begin())>> : std::true_type
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
	
	
	
	template <class T>
	class GreaterLessThanForward
	{
		protected:
		T* ptr;
		
		public:
		GreaterLessThanForward(T* t) : ptr(t)
		{}
		
		
		template <class G>
		typename std::enable_if<Internal::has_greater_than_op<T, G>::value, decltype(std::declval<T>() > std::declval<G>())>::type operator>(const G g)
		{
			return (*ptr) > g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_greater_than_op<const T, G>::value, decltype(std::declval<const T>() > std::declval<G>())>::type operator>(const G g) const
		{
			return (*ptr) > g;
		}
		
		
		template <class G>
		typename std::enable_if<Internal::has_less_than_op<T, G>::value, decltype(std::declval<T>() < std::declval<G>())>::type operator<(const G g)
		{
			return (*ptr) < g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_less_than_op<const T, G>::value, decltype(std::declval<const T>() < std::declval<G>())>::type operator<(const G g) const
		{
			return (*ptr) < g;
		}
		
		
		
		
		
		
		
		
		template <class G>
		typename std::enable_if<Internal::has_greater_than_equal_op<T, const G>::value, decltype(std::declval<T>() >= std::declval<const G>())>::type operator>=(const G g)
		{
			return (*ptr) >= g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_greater_than_equal_op<const T, const G>::value, decltype(std::declval<const T>() >= std::declval<const G>())>::type operator>=(const G g) const
		{
			return (*ptr) >= g;
		}
		
		
		template <class G>
		typename std::enable_if<Internal::has_less_than_equal_op<T, const G>::value, decltype(std::declval<T>() <= std::declval<const G>())>::type operator<=(const G g)
		{
			return (*ptr) <= g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_less_than_equal_op<const T, const G>::value, decltype(std::declval<const T>() <= std::declval<const G>())>::type operator<=(const G g) const
		{
			return (*ptr) <= g;
		}
		
		
	};
	
	
	
	
	
	
	
	template <class T>
	class ArithmeticForward
	{
		protected:
		T* ptr;
		
		public:
		ArithmeticForward(T* t) : ptr(t)
		{}
		
		
		template <class G>
		typename std::enable_if<Internal::has_addition_op<T, const G>::value, decltype(std::declval<T>() + std::declval<const G>())>::type operator+(const G g)
		{
			return (*ptr) + g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_addition_op<const T, const G>::value, decltype(std::declval<const T>() + std::declval<const G>())>::type operator+(const G g) const
		{
			return (*ptr) + g;
		}
		
		
		
		
		
		
		template <class G>
		typename std::enable_if<Internal::has_subtraction_op<T, const G>::value, decltype(std::declval<T>() - std::declval<const G>())>::type operator-(const G g)
		{
			return (*ptr) - g;
		}
		
		template <class G>
		typename std::enable_if<Internal::has_subtraction_op<const T, const G>::value, decltype(std::declval<const T>() - std::declval<const G>())>::type operator-(const G g) const
		{
			return (*ptr) - g;
		}
		
		
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <class T>
	class InvokeForward
	{
		protected:
		T* ptr;
		
		public:
		InvokeForward(T* t) : ptr(t)
		{}
		
		
		template <class... G>
		typename std::enable_if<Internal::has_invoke_op<T, G...>::value, decltype(std::declval<T>()((std::declval<G>())...))>::type operator()(G... g)
		{
			return (*ptr)(g...);
		}
		
		template <class... G>
		typename std::enable_if<Internal::has_invoke_op<const T, G...>::value, decltype(std::declval<const T>()((std::declval<G>())...))>::type operator()(G... g) const
		{
			return (*ptr)(g...);
		}
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <class T>
	class IteratorForward
	{
		protected:
		T* ptr;
		
		public:
		IteratorForward(T* t) : ptr(t)
		{}
		
		typename std::enable_if<Internal::has_iterator_begin_op<T>::value, decltype(std::declval<T>().begin())>::type begin()
		{
			return ptr->begin();
		}
		
		/*typename std::enable_if<Internal::has_iterator_end_op<T>::value, decltype(std::declval<T>().end())>::type end()
		{
			return ptr->end();
		}*/
		
		
		
		/*typename std::enable_if<Internal::has_iterator_begin_op<const T>::value, decltype(std::declval<const T>().begin())>::type begin() const
		{
			return ptr->begin();
		}*/
		
		/*typename std::enable_if<Internal::has_iterator_end_op<const T>::value, decltype(std::declval<const T>().end())>::type end() const
		{
			return ptr->end();
		}*/
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//#define ITERATOR_FORWARD
	
	template <class T>
	class AllOperatorForward : public IndexerForward<T>, public GreaterLessThanForward<T>, public ArithmeticForward<T>, public InvokeForward<T>
	#ifdef ITERATOR_FORWARD
	, public IteratorForward<T>
	#endif
	{
		public:
		
		AllOperatorForward(T* t) : IndexerForward<T>(t), GreaterLessThanForward<T>(t), ArithmeticForward<T>(t), InvokeForward<T>(t)
		#ifdef ITERATOR_FORWARD
		, IteratorForward<T>(t)
		#endif
		{
			
		}
		
		
		void set(T* t)
		{
			IndexerForward<T>::ptr = t;
			GreaterLessThanForward<T>::ptr = t;
			ArithmeticForward<T>::ptr = t;
			#ifdef ITERATOR_FORWARD
			IteratorForward<T>::ptr = t;
			#endif
		}
		
		
	};
	
	
	
	
	
	
	
	
	
}
}