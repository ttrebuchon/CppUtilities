#pragma once
#include "Job.h"
#include "JobQueue.h"
#include "../Mutexed.h"
#include <thread>
#include <condition_variable>
#include <future>
#include <iostream>

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
				bool aReady = a->ready();
				bool bReady = b->ready();
				if (aReady)
				{
					if (!bReady)
					{
						return false;
					}
				}
				else if (bReady)
				{
					return true;
				}
				
				return a->priority() <= b->priority();
			}
		};
	}
	
	class Parallelized
	{
		private:
		std::mutex threadsMut;
		std::vector<std::thread> threads;
		std::vector<std::shared_future<void>> futures;
		
		std::future<void> jobMnger;
		unsigned int allowedFutures;
		unsigned int running;
		unsigned int toRemove;
		bool destroy;
		
		void manageJobs();
		
		void getJob();
		void finishJob();
		
		void startNext();
		void startNextNoLock();
		
		void removeThread(std::thread::id);
		
		
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
		
		bool isRunning() const
		{
			Parallelized* ptr = (Parallelized*)this;
			ptr->threadsMut.lock();
			bool b = ptr->running > 0;
			ptr->threadsMut.unlock();
			return b;
		}
		
	};
}
}