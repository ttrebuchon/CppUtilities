#pragma once
#include <chrono>
#include <thread>

namespace Util
{
	
	enum Sleep
	{
		Seconds = 1000000,
		Milliseconds = 1000,
		Microseconds = 1,
	};
	
	void sleep(long double duration, Util::Sleep units = Util::Sleep::Milliseconds);
	
}