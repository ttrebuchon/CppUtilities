#include <QUtils/GUI/AppWindow.h>
#include <QUtils/GUI/ViewComponent.h>

#include <iostream>

namespace QUtils::GUI
{
	AppWindow::AppWindow(bool touch) : RenderTarget(), Clickable(touch), mainView(NULL), eventExceptions(), eventExceptions_m(), updateHolds(0), update_m(), UIThread(), exiting(false), exiting_m(), onQuit(), onKeyDown(!touch)
	{
		relayEvents([](auto _this) {
			return ((AppWindow*)_this)->mainView;
		});
	}
	
	AppWindow::~AppWindow()
	{
		{
			std::lock_guard<std::mutex> lock(exiting_m);
			exiting = true;
		}
		
		UIThread.join();
	}
	
	void AppWindow::init()
	{
		auto func = [&]()
		{
			try
			{
			this->initializeUIThread();
			}
			catch (...)
			{
				addEventException(std::current_exception());
				return;
			}
			
			bool done = false;
			bool holds = false;
			while (!done)
			{
				//Do any UI calls
				{
				try
				{
					std::unique_lock<std::timed_mutex> lock(UIcalls_m, std::defer_lock);
					if (lock.try_lock_for(std::chrono::milliseconds(50)))
					{
						while (UIcalls.size() > 0)
						{
							auto call = UIcalls.front();
							UIcalls.pop_front();
							call();
							
						}
					}
				}
				catch (...)
				{
					addEventException(std::current_exception());
				}
				}
				
				
				//Check for holds
				{
					std::unique_lock<std::mutex> lock(update_m);
					/*if (updateHolds > 0)
					{
						holds = true;
					}*/
					
					if (update_c.wait_for(lock, std::chrono::milliseconds(100), [&]{return updateHolds == 0;}))
					{
						holds = false;
					}
					else
					{
						holds = true;
					}
					
					if (!holds)
					{
						try
						{
						this->update();
						}
						catch (...)
						{
						addEventException(std::current_exception());
						}
					}
				}
				
				//Check for quit
				{
					std::lock_guard<std::mutex> lock(exiting_m);
					done = exiting;
				}
			}
		};
		
		UIThread = std::thread(func);
	}
	
	
	
	void AppWindow::blockUpdate()
	{
		std::lock_guard<std::mutex> lock(update_m);
		++updateHolds;
		update_c.notify_all();
	}
	
	void AppWindow::unblockUpdate()
	{
		std::lock_guard<std::mutex> lock(update_m);
		if (updateHolds > 0)
		{
			--updateHolds;
		}
		update_c.notify_all();
	}
	
	ViewComponent* AppWindow::replaceView(ViewComponent* v)
	{
		auto vOld = mainView;
		if (v != NULL)
		{
			std::unique_lock<std::mutex> this_lock(update_m, std::defer_lock);
			
			std::unique_lock<std::recursive_mutex> comp_lock(v->getMutex(), std::defer_lock);
			
			std::lock(this_lock, comp_lock);
			vOld = mainView;
			mainView = v;
			if (vOld != NULL)
			{
				vOld->setWindow(NULL);
			}
			v->setWindow(this);
		}
		else
		{
			std::lock_guard<std::mutex> this_lock(update_m);
			
			vOld = mainView;
			mainView = v;
			if (vOld != NULL)
			{
				vOld->setWindow(NULL);
			}
		}
		return vOld;
	}
	
	void AppWindow::addEventException(std::exception_ptr ptr)
	{
		std::lock_guard<std::mutex> lock(eventExceptions_m);
		eventExceptions.push_back(ptr);
	}
	
	bool AppWindow::updateBlocked() const
	{
		std::lock_guard<std::mutex> lock(update_m);
		return updateHolds > 0;
	}
	
	std::future<void> AppWindow::invokeUpdate()
	{
		auto prom = new std::promise<void>();
		std::lock_guard<std::timed_mutex> lock(UIcalls_m);
		UIcalls.push_back([&, prom]()
		{
			try
			{
				this->update();
				prom->set_value();
			}
			catch (...)
			{
				prom->set_exception(std::current_exception());
			}
			delete prom;
		});
		return prom->get_future();
	}
}