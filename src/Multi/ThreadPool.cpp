#include <QUtils/Multi/ThreadPool.h>
#include <thread>

namespace QUtils { namespace Multi {
	
	std::shared_timed_mutex ThreadPool::Current_m;
	Pool::_Pool* ThreadPool::Current = NULL;
	
	std::atomic<unsigned int> ThreadPool::ThreadCount(std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 2);
	
	void ThreadPool::Init()
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		
		if (Current == NULL)
		{
			std::lock_guard<std::shared_timed_mutex> lock(Current_m);
			Current = Create(ThreadCount);
		}
	}
	
	void ThreadPool::SetThreads(const unsigned int count)
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		if (!Current)
		{
			Init();
		}
		
		Current->setThreads(count);
		ThreadCount = count;
	}
	
	
	
}
}