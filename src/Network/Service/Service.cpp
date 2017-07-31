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
			router->job();
			//QUtils::sleep(100);
			_started.lock();
			go = *_started;
			_started.unlock();
		}
		}
		catch (...)
		{}
		std::cout << "Service stopped...\n";
	}
	
	void Service::wait()
	{
		this->stop();
		this->serviceFuture.get();
		while (router->job())
		{}
	}
}
}