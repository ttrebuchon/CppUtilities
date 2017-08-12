#pragma once
#include "Job.h"

namespace QUtils
{
namespace Multi
{
	template <class Result, class... Args>
	class JobFactory
	{
		private:
		std::function<Result(Args...)> func;
		unsigned long priority;
		
		public:
		//Constructors
		JobFactory(std::function<Result(Args...)> f) : func(f) {}
		template <class F>
		JobFactory(F f) : JobFactory(std::function<Result(Args...)>([f](Args... args) -> Result { return f(args...); })) {}
		
		
		
		
		
		std::shared_ptr<AJob<Result>> build(Args... args) const
		{
			auto f = func;
			return std::make_shared<AJob<Result>>([f, args...]() -> Result {
				return f(args...);
			});
		}
		
		std::shared_ptr<AJob<Result>> build(std::shared_ptr<AJob<Args...>> parent) const
		{
			auto f = func;
			return std::make_shared<AJob<Result>>(f, parent);
		}
		
		
		void setPriority(const unsigned long priority)
		{
			this->priority = priority;
		}
	};
}
}