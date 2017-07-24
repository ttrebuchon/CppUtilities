#pragma once

#include "AJob.h"


namespace QUtils
{
namespace Multi
{
	
	template <class Result_t>
	AJob<Result_t>::AJob(std::function<void(std::promise<Result_t>&)> f, unsigned long priority) : Job(priority), func(f), promise(), future(promise.get_future())
	{
		
	}
	
	
	template <class Result_t>
	template <class F>
	AJob<Result_t>::AJob(F f, unsigned long priority)  : AJob(std::function<void(std::promise<Result_t>&)>([f](auto& p)->void {p.set_value_at_thread_exit(f());}), priority) {}
	
	template <>
	template <class F>
	AJob<void>::AJob(F f, unsigned long priority)  : AJob(std::function<void(std::promise<void>&)>([f](auto& p)->void { f(); p.set_value_at_thread_exit();}), priority) {}
	
	template <class Result_t>
	template <class Arg>
	AJob<Result_t>::AJob(std::function<Result_t(Arg)> f, std::shared_ptr<AJob<Arg>> parentJob, unsigned long priority) : AJob([=]() -> Result_t { return f(parentJob->result()); }, priority)
	{
		this->depends(parentJob);
	}
	
	template <class Result_t>
	bool AJob<Result_t>::running() const
	{
		throw 4;
	}
	
	template <class Result_t>
	unsigned long AJob<Result_t>::priority() const
	{
		unsigned long l = this->rawPriority;
		for (auto dep : this->dependents())
		{
			l += dep->child()->priority();
		}
		return l;
	}
	
	
	template <class Result_t>
	Result_t AJob<Result_t>::result()
	{
		return future.get();
	}
	
}
}