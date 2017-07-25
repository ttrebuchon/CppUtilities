#pragma once
#include <functional>

#include "Job.h"

namespace QUtils
{
namespace Multi
{
	
	
	template <class Result_t>
	class AJob : public Job
	{
		private:
		
		protected:
		std::function<void(std::promise<Result_t>&)> func;
		std::promise<Result_t> promise;
		std::future<Result_t> future;
		
		public:
		AJob(std::function<void(std::promise<Result_t>&)>, unsigned long priority = 1);
		
		template <class F>
		AJob(F f, unsigned long priority = 1);
		
		template <class Arg>
		AJob(std::function<Result_t(Arg)>, std::shared_ptr<AJob<Arg>> parentJob, unsigned long priority = 1);
		
		template <class F, class Arg>
		AJob(F f, std::shared_ptr<AJob<Arg>> parentJob, unsigned long priority = 1) : AJob(std::function<Result_t(Arg)>([f](Arg arg) -> Result_t { return f(arg); }), parentJob, priority) {}
		
		virtual ~AJob() {}
		
		
		
		virtual bool running() const override;
		virtual unsigned long priority() const override;
		
		virtual Result_t result();
		
		virtual std::shared_future<void> launch() override;
		
	};
	
	
}
}

#include "AJob.hpp"