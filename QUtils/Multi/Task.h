#pragma once

#include <tuple>

#include <thread>
#include <future>


namespace QUtils
{
namespace Multi
{
	namespace Helpers
	{
		template <int... N>
		struct seq { };
		
		template <int n, int ...N>
		struct SeqGen : public SeqGen<n-1, n, N...>
		{ };
		
		template <int ...N>
		struct SeqGen<0, N...>
		{
			typedef seq<0, N...> type;
		};
		
		template <int ...N>
		struct SeqGen<-1, N...>
		{
			typedef seq<N...> type;
		};
		
		template <>
		struct SeqGen<-1>
		{
			typedef seq<> type;
		};
		
		
		template <class, int Start, int Count, class ...Types>
		struct SplitTypes {};
		
		
		template <int Start, int Count, class Type1, class ...Types>
		struct SplitTypes<void, Start, Count, Type1, Types...> : public SplitTypes<void, Start-1, Count, Types...>
		{
			static_assert(Start >= 1, "Cannot use negative index!");
		};
		
		template <int Count, class Type1, class ...Types>
		struct SplitTypes<void, 0, Count, Type1, Types...>
		{
			static_assert(Count > 0, "");
			typedef decltype(std::tuple_cat(std::declval<std::tuple<Type1>>(), std::declval<typename SplitTypes<void, 0, Count-1, Types...>::type>())) type;
		};
		
		template <class Type1, class ...Types>
		struct SplitTypes<void, 0, 1, Type1, Types...>
		{
			typedef std::tuple<Type1> type;
		};
		
		template <class ...Types>
		struct SplitTypes<void, 0, 0, Types...>
		{
			typedef std::tuple<> type;
		};
		
		
		
		
		template <int N, class Type, class ...Types>
		struct __PromiseIndex : public __PromiseIndex<N+1, Types...>
		{ };
		
		template <int N, class Type, class ...Types>
		struct __PromiseIndex<N, std::promise<Type>, Types...>
		{
			const int index = N;
		};
		
		
		template <class, template <class> class Pattern, bool bVal, int N, class ...Types>
		struct __TypeMatchIndex {};
		
		template <template <class> class Pattern, int N, class Type, class ...Types>
		struct __TypeMatchIndex<void, Pattern, false, N, Type, Types...> : public __TypeMatchIndex<void, Pattern, Pattern<Type>::value, N+1, Types...>
		{};
		
		template <template <class> class Pattern, int N, class ...Types>
		struct __TypeMatchIndex<void, Pattern, true, N, Types...>
		{
			static const int value = N;
		};
		
		template <template <class> class Pattern, int N>
		struct __TypeMatchIndex<void, Pattern, false, N>
		{
			static const int value = N+1;
		};
		
		
		
		template <template <class> class Pattern, class Type, class ...Types>
		struct TypeMatchIndex : public __TypeMatchIndex<void, Pattern, Pattern<Type>::value, 0, Types...>
		{};
		
		
		
		
		
		
	}
	
	
	
	
	
	
	namespace Internal
	{
		template <class MainReturn, class ...Returns>
		struct FuncObject
		{
			
			virtual void call(std::promise<MainReturn>&, std::promise<Returns>&... args) const = 0;
		};
		
		
		
		template <class Func, class MainReturn, class ...Returns>
		struct FuncObject_Imp : public FuncObject<MainReturn, Returns...>
		{
			template <class ...Args>
			FuncObject_Imp(const Func f, Args... args) : FuncObject<MainReturn, Returns...>(), func([=](std::promise<Returns>&... a) -> MainReturn {
				
				return f(args..., a...);
			})
			{
				
			}
			
			
			virtual void call(std::promise<MainReturn>& mainRet, std::promise<Returns>&... returns) const override
			{
				mainRet.set_value(func(returns...));
			}
			
			private:
			//const Func func;
			const std::function<MainReturn(std::promise<Returns>&...)> func;
		};
		
		
		
		
		
		template <class ...Types>
		struct FuncObj
		{
			virtual void run(Types...) = 0;
			void run(std::tuple<Types...> args)
			{
				auto s = typename Helpers::SeqGen<sizeof...(Types)-1>::type();
				run_tup_helper(args, s);
			}
			
			
			
			protected:
			static const int PIndex = Helpers::__PromiseIndex<0, Types...>::index;
			
			private:
			
			template <int ...N>
			void run_tup_helper(std::tuple<Types...> tup, Helpers::seq<N...>)
			{
				this->run(std::get<N>(tup)...);
			}
		};
		
		
		
		template <class F, class ...Types>
		struct FuncObj_Imp : public FuncObj<Types...>
		{
			virtual void run(Types... types) override
			{
				func(types...);
			}
			
			FuncObj_Imp(const F f) : FuncObj<Types...>(), func(f) {}
			
			
			
			private:
			const F func;
			using FuncObj<Types...>::PIndex;
		};
		
		
		
		template <class ...Types>
		struct FuncObj_EmptyImp : public FuncObj<Types...>
		{
			virtual void run(Types... types) override { }
			
			FuncObj_EmptyImp() : FuncObj<Types...>() {}
			
			
			
		};
		
		template <class T>
		struct VoidPattern : public std::false_type {};
		
		template <>
		struct VoidPattern<void> : public std::true_type {};
		
		template <class T>
		struct PromisePattern : public std::false_type {};
		
		template <class T>
		struct PromisePattern<std::promise<T>> : public std::true_type {};
		
		template <class ...Types>
		struct PromiseTypes : public Helpers::SplitTypes<
		void,
		Helpers::TypeMatchIndex<PromisePattern, Types...>::value, 
		sizeof...(Types) - Helpers::TypeMatchIndex<PromisePattern, Types...>::value,
		Types...>
		{};
		
		template <class ...Types>
		struct NonPromiseTypes : public Helpers::SplitTypes<
		void,
		0,
		Helpers::TypeMatchIndex<PromisePattern, Types...>::value, 
		Types...>
		{};
		
		
		template <class Type>
		struct ExtractPromises
		{};
		
		template <class ...Types>
		struct ExtractPromises<std::tuple<std::promise<Types>...>>
		{
			typedef std::tuple<Types...> type;
		};
		
		
		
		template <class, template <class> class Temp, class Type>
		struct EncapsulateTupleTypes
		{ };
		
		template <template <class> class Temp, class ...Types>
		struct EncapsulateTupleTypes<void, Temp, std::tuple<Types...>>
		{
			typedef std::tuple<Temp<Types>...> type;
		};
		
		
	}
	
	
	
	
	template <class ...Types>
	class Task
	{
		public:
		typedef typename Internal::PromiseTypes<Types...>::type Promises;
		typedef typename Internal::EncapsulateTupleTypes<void, std::shared_future, typename Internal::ExtractPromises<Promises>::type>::type Values;
		private:
		Promises prom;
		Values vals;
		
		//std::shared_ptr<Internal::FuncObj<std::promise<Return>&...>> func;
		
		
		protected:
		
		
		
		public:
		template <class F>
		Task(const F);
		Task();
		const Values& values;
		
		void operator()();
		
		
		
		
		
		
	};
}
}

#include "Task.hpp"