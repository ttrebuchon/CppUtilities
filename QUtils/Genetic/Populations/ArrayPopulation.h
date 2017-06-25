#pragma once

#include "../Population.h"

namespace QUtils
{
namespace Genetic
{
	template <class Solution_t>
	class ArrayPopulation : public Population<Solution_t>
	{
		protected:
		std::shared_ptr<Solution_t>* const array;
		const int count;
		
		public:
		template <class F>
		ArrayPopulation(const F, const unsigned int size);
		virtual ~ArrayPopulation();
		
		
		virtual std::shared_ptr<Solution_t>& at(const unsigned int index) const override;
		
		virtual unsigned int size() const override;
		
		virtual void sort() override;
	};
}
}