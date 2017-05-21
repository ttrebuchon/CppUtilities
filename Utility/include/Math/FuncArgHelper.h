#pragma once

#include <functional>
#include <vector>

namespace Util
{
namespace Math
{
namespace _Helpers
{
	template <int N, typename T, typename Ret, typename ...Args>
	class FuncArgHelper
	{
		void func(Args... args)
		{
			T i;
			FuncArgHelper<N-1, T, Ret, T, Args...>::func(i, args...);
		}
		
		public:
		
		typedef typename FuncArgHelper<N-1, T, Ret, T, Args...>::type type;
		
	};
	
	template <typename T, typename Ret, typename ...Args>
	class FuncArgHelper<0, T, Ret, Args...>
	{
		private:
		
		void func(Args... args)
		{
			
		}
		
		public:
		
		typedef std::function<Ret(Args...)> type;
	};
	
	
	
	
	template <typename ...Args>
	struct ConcatArgs
	{
		template <typename ...TArgs>
		static std::tuple<Args..., TArgs...> Get(Args... args, std::tuple<TArgs...> t)
		{
			return std::tuple_cat(std::make_tuple(args...), t);
		}
	};
	
	template <typename T>
	struct ArgsToVec
	{
		template <typename...Args>
		static std::vector<T> call(Args... args)
		{
			std::vector<T> vec;
			_call(vec, args...);
			return vec;
		}
		
		private:
		
		template <typename Arg1, typename...Args>
		static std::vector<T>& _call(std::vector<T>& vec, Arg1 arg1, Args... args)
		{
			vec.push_back(arg1);
			_call(vec, args...);
			return vec;
		}
		
		template <typename Arg1>
		static std::vector<T>& _call(std::vector<T>& vec, Arg1 arg1)
		{
			vec.push_back(arg1);
			return vec;
		}
	};
	
}
}
}