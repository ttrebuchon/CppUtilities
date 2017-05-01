#pragma once

#include <tuple>
#include <functional>

namespace Util
{
namespace TupleArgs_Internal
{
	template <int...>
	struct seq { };
	
	template <int N, int... S>
	struct gens : gens<N-1, N-1, S...> { };
	
	template <int... S>
	struct gens<0, S...> { typedef seq<S...> type; };
	
	template <typename Ret, typename ...Args, int...S>
	Ret innerCall(std::function<Ret(Args...)> f, std::tuple<Args...> argsT, seq<S...>)
	{
		return f(std::get<S>(argsT)...);
	}
	
}
	
	template <typename Ret, typename ...Args>
	Ret call_tuple_args(std::function<Ret(Args...)> f, std::tuple<Args...> argsT)
	{
		return TupleArgs_Internal::innerCall(f, argsT, typename TupleArgs_Internal::gens<sizeof...(Args)>::type());
	}

}