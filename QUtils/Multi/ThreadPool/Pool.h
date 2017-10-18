#pragma once

#include <functional>
#include <memory>
#include <QUtils/Graph/DependencyGraph.h>

namespace QUtils { namespace Multi {
namespace Pool
{
	class _Pool final
	{
		private:
		QUtils::Graph::DependencyGraph<std::shared_ptr<Job>> jobs;
		
		std::atomic<unsigned int> threadCount;
		
		public:
		_Pool()
		{
			
		}
		
		JobHandle addJob(const std::function<void()> func)
		{
			std::shared_ptr<Job> ptr;
			jobs.push_back(ptr = std::make_shared<Job>(func));
			JobHandle handle(ptr);
			return handle;
		}
		
		void setThreads(const unsigned int);
		unsigned int getThreads() const;
		
		std::future<void> pause();
		std::future<void> close();
		
		
		
	};
	
}
}
}