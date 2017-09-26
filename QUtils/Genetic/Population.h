#pragma once
#include <memory>

#include "Fitness.h"


namespace QUtils
{
namespace Genetic
{
	template <class T, class H>
	class Solution;
	
	template <class Solution_t>
	class Population
	{
		protected:
		
		std::shared_ptr<FitnessMetric<double, const Solution_t&>> _fitness;
		
		public:
		Population(const std::shared_ptr<FitnessMetric<double, const Solution_t&>> f) : _fitness(f) {}
		
		template <typename F>
		Population(const F f) : _fitness(std::make_shared<FitnessMetricImp<F, double, const Solution_t&>>(f))
		{}
		
		std::shared_ptr<Solution_t>& operator[](const unsigned int index) const { return this->at(index); }
		virtual std::shared_ptr<Solution_t>& at(const unsigned int index) const = 0;
		
		virtual unsigned int size() const = 0;
		
		virtual void sort() = 0;
		
		virtual void newGeneration() = 0;
		virtual std::shared_ptr<const FitnessMetric<double, const Solution_t&>> fitness() const
		{
			return _fitness;
		}
		
		virtual void addOrReplace(std::shared_ptr<Solution_t> sol) = 0;
	};
}
}