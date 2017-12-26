#pragma once
#include <chrono>

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
	typedef std::chrono::steady_clock Clock;
	static_assert(Clock::is_steady, "Clock must be a steady type");
	typedef typename Clock::time_point Time;
	typedef typename Clock::duration Duration;
	typedef Clock_Timespan<Clock> Timespan;
	
	
}
}