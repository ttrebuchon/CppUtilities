#pragma once

#include "Task.h"

namespace QUtils
{
namespace Multi
{
	namespace Helpers
	{
		
		
		struct FutureHelper
		{
			
			
			template <class ...T>
			static std::tuple<std::shared_future<T>...> call(std::tuple<std::promise<T>...>& tup)
			{
				return innercall(tup, typename SeqGen<sizeof...(T)-1>::type());
			}
			
			
			private:
			template <int ...N, class ...T>
			static std::tuple<std::shared_future<T>...> innercall(std::tuple<std::promise<T>...>& tup, seq<N...>)
			{
				return std::make_tuple((std::get<N>(tup).get_future().share())...);
			}
			
			static std::tuple<> innercall(std::tuple<>& tup, seq<>)
			{
				return std::make_tuple();
			}
		};
		
		
		
	}
	
	
	
	
	
	
	
	
	template <class ...Types>
	template <class F>
	Task<Types...>::Task(const F f) : prom(), vals(Helpers::FutureHelper::call(prom)), /*func(std::make_shared<Internal::FuncObj_Imp<F, std::promise<Return>&...>>(f)), */values(vals)
	{
		
	}
	
	
	template <class ...Types>
	Task<Types...>::Task() : prom(), vals(Helpers::FutureHelper::call(prom)), /*func(std::make_shared<Internal::FuncObj_EmptyImp<std::promise<Return>&...>>()), */values(vals)
	{
		
	}
	
	template <class ...Types>
	void Task<Types...>::operator()()
	{
		//func->run(prom);
	}
}
}