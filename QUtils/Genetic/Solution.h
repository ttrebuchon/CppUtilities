#pragma once
#include <memory>


namespace QUtils
{
namespace Genetic
{
	//T can be a container of Hs, if the solution is a set of values
	template <class T, class H = T>
	class Solution
	{
		protected:
		
		public:
		
		virtual void randomize() = 0;
		
		virtual void mutate(const int magnitude = -1) = 0;
		
		virtual T get() const = 0;
		
		virtual std::shared_ptr<Solution<T, H>> clone() const = 0;
		
		virtual void modified() = 0;
		virtual H& set(const int index, const H) = 0;
	};
}
}