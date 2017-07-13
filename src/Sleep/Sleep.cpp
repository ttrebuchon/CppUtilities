#include <QUtils/Sleep/Sleep.h>
#include <chrono>
#include <thread>


namespace QUtils
{
	void sleep(long double duration, QUtils::Sleep units)
	{
		std::this_thread::sleep_for(std::chrono::microseconds((int)(duration*units)));
	}
	
}