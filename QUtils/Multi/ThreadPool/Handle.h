#pragma once

#include <memory>
#include "Handle.h"

namespace QUtils { namespace Multi {
	
	namespace Pool
	{
		class Job;
	}
	
	class JobHandle
	{
		private:
		std::shared_ptr<Pool::Job> job;
		
		
		public:
		JobHandle(std::shared_ptr<Pool::Job> ptr) : job(ptr)
		{
		}
		
		bool started() const;
		bool cancelled() const;
		bool completed() const;
		
		void cancel();
	};
}
}