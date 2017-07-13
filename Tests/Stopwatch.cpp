#include "../Tests_Helpers.h"
#include <QUtils/Stopwatch/Stopwatch.h>
#include <ctime>

#include <chrono>

#define WAIT_PERIOD 1

bool Test_Stopwatch()
{
	QUtils::Stopwatch::Stopwatch sw;
	sw.start();
	auto cur = std::chrono::steady_clock::now();
	while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - cur).count() < WAIT_PERIOD*1000)
	{
		
	}
	sw.stop();
	dout << "Time Diff: " << (sw.value() - WAIT_PERIOD) << std::endl;
	assert_ex(abs(sw.value() - WAIT_PERIOD) < 0.01);
	long double val = sw.value();
	assert_ex(sw.value() == val);
	cur = std::chrono::steady_clock::now();
	while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - cur).count() < 1000)
	{
		
	}
	assert_ex(sw.value() == val);
	
	return true;
}