#pragma once

#include <queue>

#include "../Lockable.h"

namespace QUtils
{
namespace Multi
{
	namespace Internal
	{
		template <class T>
		struct IdentityCompare
		{
			bool operator()(const T a, const T b)
			{
				return a <= b;
			}
		};
		
	}
	
	template <class T, class ValueFunc = Internal::IdentityCompare<T>>
	class JobQueue : Lockable
	{
		private:
		typedef std::priority_queue<T, std::vector<T>, ValueFunc> Base;
		
		struct InvValueFunc
		{
			ValueFunc v;
			
			bool operator()(const T a, const T b)
			{
				return !(v(a, b));
			}
		};
		
		Base q;
		std::vector<T> v;
		
		void sort()
		{
			std::sort(v.begin(), v.end(), InvValueFunc());
		}
		
		protected:
		
		public:
		std::mutex finishMut;
		std::condition_variable finishCond;
		JobQueue() : Lockable(), q(), v(), finishMut(), finishCond() {}
		
		T get()
		{
			std::unique_lock<Lockable> lk(*this);
			sort();
			if (v.size() <= 0)
			{
				//this->unlock();
				return NULL;
			}
			auto back = v.back();
			if (back->ready())
			{
				v.pop_back();
				//this->unlock();
				return back;
			}
			else
			{
				//this->unlock();
				return NULL;
			}
		}
		
		void push(T t)
		{
			this->lock();
			t->addCallback([&]() {
				finishCond.notify_all();
			});
			v.push_back(t);
			this->unlock();
		}
		
		bool ready()
		{
			sort();
			if (v.size() <= 0)
			{
				return false;
			}
			
			return v.back()->ready();
		}
		
	};
}
}