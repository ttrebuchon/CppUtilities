#pragma once
#include <chrono>
#include <limits>

namespace QUtils { namespace World {
	
	template <class Clock>
	struct Clock_Timespan
	{
		typedef typename Clock::time_point Time;
		typedef typename Clock::duration Duration;
		Time start;
		Time end;
		
		Clock_Timespan(Time start, Time end) : start(start), end(end)
		{}
		
		Clock_Timespan(Time start, Duration dur) : Clock_Timespan(start, start+dur)
		{}
		
		Clock_Timespan() : start(), end()
		{}
		
		Duration duration() const
		{
			return end - start;
		}
		
		std::chrono::milliseconds to_ms() const
		{
			return std::chrono::milliseconds(end - start);
		}
		
		std::chrono::milliseconds toMilliseconds() const
		{
			return std::chrono::milliseconds(end - start);
		}
		
		std::chrono::seconds to_s() const
		{
			return std::chrono::seconds(end - start);
		}
		
		std::chrono::seconds toSeconds() const
		{
			return std::chrono::seconds(end - start);
		}
	};
	
	
	
	using namespace std::literals::chrono_literals;
	
	
	
	template <int Ratio>
	struct WorldClock_R
	{
		public:
		typedef long long int rep;
		typedef std::ratio<1, Ratio> period;
		typedef std::chrono::duration<rep, period> duration;
		typedef std::chrono::time_point<WorldClock_R<Ratio>> time_point;
		constexpr static bool is_steady = true;
		
		static time_point min()
		{
			return time_point(duration(0));
		}
		
		static time_point max()
		{
			return time_point(duration(std::numeric_limits<rep>::max()));
		}
		
		
		
		WorldClock_R() : ticks(0)
		{
			
		}
		
		inline time_point now() const
		{
			return time_point(duration(ticks));
		}
		
		void advance()
		{
			++ticks;
		}
		
		private:
		rep ticks;
		
	};
	
	
	
	
	typedef std::chrono::steady_clock Clock;
	static_assert(Clock::is_steady, "Clock must be a steady type");
	typedef typename Clock::time_point Time;
	typedef typename Clock::duration Duration;
	typedef Clock_Timespan<Clock> Timespan;
	
	
	typedef WorldClock_R<1000> WorldClock;
}
}