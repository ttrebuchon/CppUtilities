#pragma once

#include "OrderedSolution.h"

namespace QUtils
{
namespace Genetic
{
	template <class T>
	class CircularOrderedSolution : public OrderedSolution<T>
	{
		protected:
		std::shared_ptr<T> lowest;
		void shift(int n);
		
		public:
		CircularOrderedSolution(const unsigned int size, const T lowerBound, const T upperBound);
		CircularOrderedSolution(const unsigned int size, const T lowerBound);
		CircularOrderedSolution(const unsigned int size);
		
		
		virtual std::shared_ptr<Solution<std::vector<T>, T>> clone() const override;
		
		virtual void modified() override;
		
	};
}
}