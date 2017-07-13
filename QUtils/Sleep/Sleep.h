#pragma once
#include <chrono>
#include <thread>

namespace QUtils
{
	
	enum Sleep
	{
		Seconds = 1000000,
		Milliseconds = 1000,
		Microseconds = 1,
	};
	
	void sleep(long double duration, QUtils::Sleep units = QUtils::Sleep::Milliseconds);
	
}