#pragma once
#include <memory>


namespace QUtils
{
namespace Genetic
{
	template <class T>
	class Solution
	{
		protected:
		
		public:
		
		virtual void randomize() = 0;
		
		virtual void mutate(const int magnitude = -1) = 0;
		
		virtual T get() const = 0;
		
		virtual std::shared_ptr<Solution<T>> clone() const = 0;
		
		virtual void modified() = 0;
	};
}
}