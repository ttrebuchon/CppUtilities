#pragma once


namespace QUtils
{
namespace Types
{
	template <int...>
	struct Sequence {};
	
	
	template <int N, int... M>
	struct SequenceGen : public SequenceGen<N-1, N, M...> 
	{};
	
	template <int ...M>
	struct SequenceGen<0, M...> : public Sequence<0, M...>
	{
		typedef Sequence<0, M...> type;
	};
	
	template <int ...M>
	struct SequenceGen<-1, M...> : public Sequence<M...>
	{
		typedef Sequence<M...> type;
	};
	
	
	
}
}