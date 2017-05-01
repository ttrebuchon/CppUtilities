#include "../Tests.h"
#include <Sleep/Sleep.h>
#include <Stopwatch/Stopwatch.h>

#define TEST_DURATION ((long double)(0.1))

#define ACCEPTABLE_ERROR 0.025

#define ACCEPTABLE_REL_ERROR 5

long double TestSleep(long double time)
{
	Util::Stopwatch sw;
	
	//dout << "Testing at duration=" << time << std::endl;
	sw.start();
	Util::sleep(time, Util::Sleep::Seconds);
	sw.stop();
	//dout << sw.value() << std::endl;
	long double err = sw.value() - time;
	err*= (err < 0) ? -1 : 1;
	//dout << "Error: " << err << std::endl;
	
	long double rel_err = (100*err)/time;
	assert_ex((err < ACCEPTABLE_ERROR && rel_err < 100) || (rel_err < ACCEPTABLE_REL_ERROR && err < ACCEPTABLE_ERROR*10));
	return rel_err;
}


bool Testing::Sleep()
{
	for (int i = 0; i < 10; i++)
	{
	long double avg = 0;
	avg += TestSleep(TEST_DURATION);
	avg += TestSleep(TEST_DURATION/10);
	avg += TestSleep(TEST_DURATION/100);
	dout << avg/3 << "%" << std::endl;
	}
	
	
	
	
	return true;
}