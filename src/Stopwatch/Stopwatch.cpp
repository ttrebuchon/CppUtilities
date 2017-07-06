#include <QUtils/Stopwatch/Stopwatch.h>


namespace QUtils
{
namespace Stopwatch
{
	Stopwatch::Stopwatch() : times()
	{
		
	}
	
	void Stopwatch::reset()
	{
		times = std::vector<time_p>();
	}
	
	void Stopwatch::start()
	{
		auto t = Clock::now();
		if (times.size() % 2 == 0)
		{
			times.push_back(t);
		}
	}
	
	void Stopwatch::stop()
	{
		auto t = Clock::now();
		if (times.size() % 2 == 1)
		{
			times.push_back(t);
		}
	}
	
	long double Stopwatch::value()
	{
		auto t = Clock::now();
		register int count = times.size();
		register Clock::duration duration = Clock::duration::zero();
		if (count == 0)
		{
			return std::chrono::duration_cast<std::chrono::microseconds>(duration).count()/1000000;
		}
		
		
		for (auto i = 1; i < count; i += 2)
		{
			duration += (times[i] - times[i-1]);
		}
		if (count % 2 > 0)
		{
			duration += (t - times[count-1]);
		}
		
		
		
		return ((long double)std::chrono::duration_cast<std::chrono::microseconds>(duration).count())/1000000;
	}
	
	
	
}
}