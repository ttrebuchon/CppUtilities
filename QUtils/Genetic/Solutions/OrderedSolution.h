#pragma once

#include "../Solution.h"
#include <vector>

namespace QUtils
{
namespace Genetic
{
	template <class T>
	class OrderedSolution : public Solution<std::vector<T>, T>
	{
		protected:
		
		std::vector<T> order;
		
		public:
		OrderedSolution(const unsigned int size, const T lowerBound, const T upperBound);
		OrderedSolution(const unsigned int size, const T lowerBound);
		OrderedSolution(const unsigned int size);
		
		T& operator[](const unsigned int i) { return at(i); }
		const T& operator[](const unsigned  int i) const { return at(i); }
		virtual T& at(const size_t) override;
		virtual const T& at(const size_t) const;
		
		virtual unsigned int size() const;
		
		virtual void randomize() override;
		
		virtual void mutate(const int magnitude = -1) override;
		
		virtual std::vector<T> get() const override;
		
		virtual std::shared_ptr<Solution<std::vector<T>, T>> clone() const override;
		
		virtual void modified() override;
		virtual T& set(const int index, const T) override;
		
	};
}
}