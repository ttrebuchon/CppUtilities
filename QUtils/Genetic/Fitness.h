#pragma once


namespace QUtils
{
namespace Genetic
{
	template <class Ret, class ...In>
	class FitnessMetric
	{
		public:
		
		virtual Ret eval(In...) const = 0;
		Ret operator()(In... in) const { return eval(in...); }
	};
	
	template <class F, class Ret, class ...In>
	class FitnessMetricImp : public FitnessMetric<Ret, In...>
	{
		protected:
		const F func;
		public:
		
		FitnessMetricImp(const F f) : func(f) {}
		
		virtual Ret eval(In... in) const override { return func(in...); }
	};
	
	
}
}