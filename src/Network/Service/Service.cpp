#include <QUtils/Network/Service/Service.h>
#include <QUtils/Network/Service/Router.h>
#include <iostream>
#include <QUtils/Sleep/Sleep.h>

namespace QUtils
{
namespace Network
{
	
	Service::Service(std::shared_ptr<Router> router) : _started(false), registered(false), router(router), started(_started)
	{
		
	}
	
	void Service::goRegister()
	{
		if (!registered)
		{
			registerProcs();
		}
	}
	
	
	Service::~Service()
	{
		router = NULL;
		this->stop();
	}
	
	std::shared_ptr<Router> Service::getRouter()
	{
		return router;
	}
	
	
	void Service::start()
	{
		//bool go = true;
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
	
	void Service::startAsync()
	{
		if (this->serviceFuture.valid())
		{
			if (serviceFuture.wait_for(std::chrono::seconds(1)) != std::future_status::ready)
			{
				//TODO
				throw std::exception();
			}
		}
		this->serviceFuture = std::async(std::launch::async, [&] () {
			this->start();
		});
	
	}
	
	void Service::stop()
	{
		_started = false;
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