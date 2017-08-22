#pragma once


namespace QUtils
{
namespace Types
{
	namespace MinMax_Helper
	{
		
		template <int N1, int... N>
		struct Max : public Max<N1, Max<N...>::value>
		{
			
		};
		
		template <int N1, int N2>
		struct Max<N1, N2>
		{
			static constexpr int value = std::max(N1, N2);
		};
		
		template <int N1>
		struct Max<N1>
		{
			static constexpr int value = N1;
		};
		
		
		
		
		
		
		
		template <int N1, int... N>
		struct Min : public Min<N1, Min<N...>::value>
		{
			
		};
		
		template <int N1, int N2>
		struct Min<N1, N2>
		{
			static constexpr int value = std::min(N1, N2);
		};
		
		template <int N1>
		struct Min<N1>
		{
			static constexpr int value = N1;
		};
		
		
	}
	
	
	template <int... N>
	struct Sequence
	{
		constexpr static int Max()
		{
			return MinMax_Helper::Max<N...>::value;
		}
		
		constexpr static int Min()
		{
			return MinMax_Helper::Min<N...>::value;
		}
	};
	
	
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