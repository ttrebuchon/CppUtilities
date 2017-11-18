#pragma once

#include "../Solution.h"

namespace QUtils
{
namespace Genetic
{
	template <class T>
	class NumericVectorSolution : public Solution<std::vector<T>, T>
	{
		private:
		protected:
		std::vector<T> values;
		
		public:
		NumericVectorSolution(const unsigned int size);
		NumericVectorSolution(const std::vector<T> values);
		
		template <class RandomGen>
		NumericVectorSolution(const unsigned int size, RandomGen generator); 
		
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