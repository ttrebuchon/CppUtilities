#pragma once

#include <thread>
#include <future>
#include <vector>
#include <queue>

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
		ThreadPool* current;
		
		static void Init();
		
		public:
		
	};
}
}