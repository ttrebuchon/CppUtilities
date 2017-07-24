#pragma once
#include "Job.h"
#include "JobQueue.h"
#include "../Mutexed.h"
#include <thread>
#include <condition_variable>
#include <future>

namespace QUtils
{
namespace Multi
{
	namespace Internal
	{
		struct JobCompare
		{
			bool operator()(const std::shared_ptr<Job> a, const std::shared_ptr<Job> b) const
			{
				return a->priority() <= b->priority();
			}
		};
	}
	
	class Parallelized
	{
		private:
		std::vector<std::thread> threads;
		std::vector<std::future<void>> futures;
		Mutexed<unsigned int> allowedFutures;
		Mutexed<unsigned int> toRemove;
		
		void getJob();
		void finishJob();
		
		
		protected:
		JobQueue<std::shared_ptr<Job>, Internal::JobCompare> jobs;
		
		std::mutex jobMut;
		std::condition_variable jobCond;
		
		size_t threadpool() const;
		size_t threadpool(const size_t);
		size_t activeThreads() const;
		
		public:
		
		Parallelized(const unsigned int threads);
		virtual ~Parallelized();
		
		template <class F, class... Args>
		std::shared_ptr<Job> addJob(F func, Args... args);
		
	};
}
}
