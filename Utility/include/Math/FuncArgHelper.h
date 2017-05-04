#pragma once

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
	
}
}
}