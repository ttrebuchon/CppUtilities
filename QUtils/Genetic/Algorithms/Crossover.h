#pragma once
#include "../Algorithm.h"

#include <functional>


namespace QUtils
{
namespace Genetic
{
	template <typename Solution_t>
	class CrossoverAlgorithm : public Algorithm<Solution_t>
	{
		protected:
		typedef double Metric;
		
		
		
		public:
		bool mutations;
		int sequenceLength;
		double mutateProbability;
		std::function<void(Solution_t&)> mutateOverride = NULL;
		
		CrossoverAlgorithm(const std::shared_ptr<Population<Solution_t>>);
		
		virtual void go(const unsigned int generations) override;
		
		virtual std::shared_ptr<const Solution_t> best() const override;
		
	};
}
}