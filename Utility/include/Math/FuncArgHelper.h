#pragma once

namespace Util
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
	
}