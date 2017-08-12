#pragma once

#include "AJob.h"


namespace QUtils
{
namespace Multi
{
	template <class F, class... Args>
	std::shared_ptr<Job> Parallelized::addJob(F func, Args... args)
	{
		typedef decltype(func(args...)) Ret;
		auto j = std::make_shared<AJob<Ret>>([func, args...]() -> Ret {
			return func(args...);
		});
		j->addCallback([&]() {
			this->jobCond.notify_one();
		});
		
		this->jobs.lock();
		this->jobs.push(j);
		this->jobs.unlock();
		
		return j;
	}
}
}