#include <Sleep/Sleep.h>
#include <chrono>
#include <thread>


namespace Util
{
	void sleep(long double duration, Util::Sleep units)
	{
		std::this_thread::sleep_for(std::chrono::microseconds((int)(duration*units)));
	}
	
}