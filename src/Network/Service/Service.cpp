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
		_started = true;
		
		try
		{
		while (_started)
		{
			router->job();
			//_started.lock();
			//go = _started;
			//_started.unlock();
		}
		}
		catch (...)
		{}
		
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