#pragma once

#include <functional>
#include <memory>
#include <shared_mutex>
#include <list>

#include <QUtils/Graphs/DependencyGraph.h>
#include "Job.h"
#include "Handle.h"

namespace QUtils { namespace Multi {
namespace Pool
{
	class _Pool final
	{
		private:
		
		enum struct State
		{
			Created,
			Running,
			Closing,
		};
		
		State state;
		std::shared_timed_mutex control_m;
		std::promise<void> closePromise;
		std::shared_future<void> closeFuture;
		std::condition_variable cond;
		std::atomic<int> runningCount;
		QUtils::Graphs::DependencyGraph<std::shared_ptr<Job>> jobs;
		std::list<std::thread> threads;
		std::atomic<unsigned int> threadCount;
		
		
		std::mutex job_m;
		void threadDriver();
		
		public:
		_Pool(const unsigned int threadCount);
		~_Pool();
		
		void init();
		
		JobHandle addJob(const std::function<void()> func);
		
		void setThreads(const unsigned int);
		unsigned int getThreads() const;
		
		std::shared_future<void> pause();
		std::shared_future<void> close();
		
		
		
	};
	
}
}
}