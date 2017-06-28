#pragma once
#include <memory>


namespace QUtils
{
namespace Genetic
{
	namespace Internal
	{
		template <class Ret, class ...In>
		class AlgoWrapper
		{
			public:
			
			virtual Ret operator()(In...) const = 0;
		};
		
		
		template <class F, class Ret, class ...In>
		class AlgoWrapperImp : public AlgoWrapper<Ret, In...>
		{
			
			protected:
			const F func;
			public:
			AlgoWrapperImp(const F f) : func(f) {}
			
			virtual Ret operator()(In... in) const override
			{
				static_assert(std::is_same<Ret, decltype(func(in...))>::value, "Incompatible type for 'F' in AlgoWrapperImp");
				return func(in...);
			}
		};
	}
	
	template <typename T>
	class Population;
	
	template <typename T, class H>
	class Solution;
	
	
	template <typename T>
	class Algorithm
	{
		protected:
		unsigned long long _generation;
		std::shared_ptr<Population<T>> population;
		
		public:
		const unsigned long long& generation;
		
		Algorithm(const std::shared_ptr<Population<T>>);
		
		virtual void go(const unsigned int generations) = 0;
		
		virtual std::shared_ptr<const T> best() const = 0;
	};
}
}