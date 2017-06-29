#pragma once
#include <mutex>


namespace QUtils
{
namespace Multi
{
	template <class T>
	class Mutexed
	{
		private:
		
		protected:
		std::mutex mut;
		T t;
		
		
		
		public:
		template <class ...Args>
		Mutexed(Args... args);
		
		
		T& operator*();
		T* operator->();
		
		bool try_lock();
		void lock();
		void unlock();
		
	};
	
}
}

#include "Mutexed.hpp"