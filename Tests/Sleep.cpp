#include "../Tests_Helpers.h"
#include <QUtils/Sleep/Sleep.h>
#include <chrono>

#define TEST_DURATION ((long double)(0.1))

#define ACCEPTABLE_ERROR 0.025

#define ACCEPTABLE_REL_ERROR 5

long double TestSleep(long double time)
{
	
	auto start = std::chrono::high_resolution_clock::now(); //Get start time
	QUtils::sleep(time, QUtils::Sleep::Seconds);
	auto stop = std::chrono::high_resolution_clock::now(); //Get stop time
	auto diff = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count(); //Get delta in microseconds
	
	
	long double err = ((long double)(diff - time*1000000))/1000000; //Get error in seconds
	err*= (err < 0) ? -1 : 1; //Take abs value
	
	long double rel_err = (100*err)/time;
	if (!((err < ACCEPTABLE_ERROR && rel_err < 100) || (rel_err < ACCEPTABLE_REL_ERROR && err < ACCEPTABLE_ERROR*10)))
	{
		throw StringException(std::string("(") + std::to_string(err) + " < ACCEPTABLE_ERROR(" + std::to_string(ACCEPTABLE_ERROR) + ") && " + std::to_string(rel_err) + " < 100) || (" + std::to_string(rel_err) + " < ACCEPTABLE_REL_ERROR && " + std::to_string(err) + " < ACCEPTABLE_ERROR(" + std::to_string(ACCEPTABLE_ERROR) + ") *10)");
	}
	//assert_ex((err < ACCEPTABLE_ERROR && rel_err < 100) || (rel_err < ACCEPTABLE_REL_ERROR && err < ACCEPTABLE_ERROR*10));
	return rel_err;
}


bool Test_Sleep()
{
	for (int i = 0; i < 10; i++)
	{
	long double avg = 0;
	avg += TestSleep(TEST_DURATION);
	avg += TestSleep(TEST_DURATION/10);
	avg += TestSleep(TEST_DURATION*1.9);
	dout << avg/3 << "%" << std::endl;
	}
	
	
	
	
	return true;
}