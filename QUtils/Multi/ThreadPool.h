#pragma once

#include <thread>
#include <future>
#include <vector>
#include <queue>
#include <functional>
#include <shared_mutex>

#include "Lockable.h"
#include "Task.h"

#include "ThreadPool/Handle.h"
#include "ThreadPool/Job.h"
#include "ThreadPool/Pool.h"

namespace QUtils
{
namespace Multi
{
	namespace Internal
	{
		
	}
	
	
	
	class ThreadPool final
	{
		private:
		
		static std::shared_timed_mutex Current_m;
		static Pool::_Pool* Current;
		static std::atomic<unsigned int> ThreadCount;
		
		
		static void Init();
		
		public:
		
		static Pool::_Pool* Create(const int threads);
		
		static void SetThreads(const unsigned int);
		static unsigned int GetThreads();
		static JobHandle AddJob(const std::function<void()> func);
		static std::future<void> Pause();
		static std::future<void> Close();
	};
}
}