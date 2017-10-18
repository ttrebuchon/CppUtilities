#pragma once
#include <atomic>
#include <memory>

namespace QUtils { namespace Multi {
namespace Pool
{
	
	class Job
	{
		private:
		std::future<void> future;
		std::atomic<bool> cancelled;
		std::atomic<bool> started;
		
		public:
		Job(const std::function<void()> func) : future(std::async(std::launch::deferred, func))
		{
			
		}
		
		void run()
		{
			future.get();
		}
		
		void cancel()
		{
			cancelled = true;
			if (started)
			{
				cancelled = false;
			}
		}
		
		bool completed() const
		{
			return (future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready);
		}
		
		/*JobHandle getHandle() const
		{
			
		}*/
		
		friend class JobHandle;
	};
	
}
}
}