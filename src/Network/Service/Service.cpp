#include <QUtils/Network/Service/Service.h>
#include <QUtils/Network/Service/Router.h>
#include <iostream>
#include <QUtils/Sleep/Sleep.h>

namespace QUtils
{
namespace Network
{
	void Service::start()
	{
		bool go = true;
		goRegister();
		_started.lock();
		_started = true;
		_started.unlock();
		std::cout << "Starting service...\n";
		try
		{
		while (go)
		{
			//sleep(2000);
			router->job();
			
			_started.lock();
			go = *_started;
			_started.unlock();
		}
		}
		catch (...)
		{}
		std::cout << "Service stopped...\n";
	}
}
}