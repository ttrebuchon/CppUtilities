#include "../Tests_Helpers.h"
#include <QUtils/Multi/ThreadPool.h>

#include <QUtils/Sleep/Sleep.h>

DEF_TEST(Multi_ThreadPool)
{
	using namespace QUtils::Multi;
	
	dout << "Default Thread Count: " << ThreadPool::GetThreads() << "\n";
	assert_ex(ThreadPool::GetThreads() == std::thread::hardware_concurrency());
	
	/*ThreadPool::Start().get();
	dout << "Started.\n";*/
	
	/*try
	{
		ThreadPool::SetThreads(100);
	}
	catch (...) {}*/
	
	auto x = ThreadPool::AddJob([]() {
		dout << "Mark!\n";
	});
	dout << "Job Added.\n";
	
	QUtils::sleep(3000);
	dout << "Slept.\n";
	
	ThreadPool::Close().get();
	dout << "Closed.\n";
	
	return true;
}