#pragma once
#include <mutex>


namespace QUtils
{
namespace Multi
{
	class Lockable
	{
		protected:
		std::mutex mut;
		public:
		Lockable();
		
		bool try_lock();
		void lock();
		void unlock();
	};
}
}