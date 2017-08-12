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
	class JobQueue : public std::priority_queue<T, std::vector<T>, ValueFunc>, public Lockable
	{
		private:
		typedef std::priority_queue<T, std::vector<T>, ValueFunc> Base;
		
		protected:
		
		public:
		JobQueue(const size_t size) : Base(size), Lockable()
		{ }
		JobQueue() : Base(), Lockable() {}
		
		
		void reorder();
	};
}
}