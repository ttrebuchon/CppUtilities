#include <QUtils/Multi/ThreadPool.h>
#include <thread>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Multi {
	
	std::shared_timed_mutex ThreadPool::Current_m;
	std::shared_ptr<Pool::_Pool> ThreadPool::Current = NULL;
	
	std::atomic<unsigned int> ThreadPool::ThreadCount(std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 2);
	
	void ThreadPool::Init()
	{
		std::lock_guard<std::shared_timed_mutex> lock(Current_m);
		
		if (Current == NULL)
		{
			Current = Create(ThreadCount);
		}
	}
	
	std::shared_ptr<Pool::_Pool> ThreadPool::Create(const int threads)
	{
		auto ptr = std::make_shared<Pool::_Pool>(threads);
		ptr->init();
		return ptr;
	}
	
	void ThreadPool::SetThreads(const unsigned int count)
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		ThreadCount = count;
		if (!Current)
		{
			shared_lock.unlock();
			Init();
			shared_lock.lock();
		}
		Current->setThreads(count);
		
	}
	
	unsigned int ThreadPool::GetThreads()
	{
		return ThreadCount;
	}
	
	JobHandle ThreadPool::AddJob(const std::function<void()> func)
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		if (!Current)
		{
			shared_lock.unlock();
			Init();
			shared_lock.lock();
		}
		
		return Current->addJob(func);
	}
	
	/*std::shared_future<void> ThreadPool::Start()
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		if (Current)
		{
			return std::async(std::launch::deferred, [](){}).share();
		}
		else
		{
			return std::async(std::launch::async, []()
			{
				Init();
			}).share();
		}
	}*/
	
	std::shared_future<void> ThreadPool::Pause()
	{
		std::shared_lock<std::shared_timed_mutex> shared_lock(Current_m);
		if (!Current)
		{
			shared_lock.unlock();
			Init();
			shared_lock.lock();
		}
		
		return Current->pause();
	}
	
	std::shared_future<void> ThreadPool::Close()
	{
		std::lock_guard<std::shared_timed_mutex> lock(Current_m);
		if (!Current)
		{
			return std::async(std::launch::deferred, [](){}).share();
		}
		else
		{
			auto fut = Current->close();
			Current = NULL;
			return fut;
		}
		
		
	}
	
	
	
}
}