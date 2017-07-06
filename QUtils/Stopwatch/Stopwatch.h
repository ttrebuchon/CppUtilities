#ifndef INCLUDED_UTIL_STOPWATCH_H
#define INCLUDED_UTIL_STOPWATCH_H

#include <vector>
#include <chrono>

namespace QUtils
{
namespace Stopwatch
{
	class Stopwatch
	{
		private:
		
		typedef std::chrono::high_resolution_clock Clock;
		
		typedef typename Clock::time_point time_p;
		
		std::vector<time_p> times;
		
		protected:
		
		public:
		
		Stopwatch();
		
		
		void reset();
		
		void start();
		void stop();
		
		long double value();
		
		
	};
	
}
}



#endif