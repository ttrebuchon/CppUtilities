#include <QUtils/Multi/ThreadPool/Pool.h>
#include <QUtils/Exception/Exception.h>

#include <iostream>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Multi {
namespace Pool
{
	
	QUTILS_CUSTOM_EXCEPTION(ThreadPoolException,);
	
	_Pool::_Pool(const unsigned int threads) : state(State::Created), control_m(), closePromise(), closeFuture(), cond(), runningCount(0), jobs(), threads(), threadCount(threads)
	{
		
	}
	
	_Pool::~_Pool()
	{
		try
		{
			bool needClose;
			
			{
				std::shared_lock<std::shared_timed_mutex> shared_lock(control_m);
			needClose = (state != State::Closing);
			}
			
			if (needClose)
			{
				this->close();
			}
			
			closeFuture.get();
		}
		catch (...)
		{
			
		}
		
		
		
		
		
		std::cout << "Deleting _Pool...\n";
		
		for (auto& thread : threads)
		{
			thread.join();
		}
		
		std::cout << "Threads joined.\n";
		//Wait for any other threads to finish and GTFO
		std::lock_guard<std::shared_timed_mutex> lock(control_m);
	}
	
	void _Pool::init()
	{
		//TODO
		std::lock_guard<std::shared_timed_mutex> lock(control_m);
		if (state == State::Closing)
		{
			throw ThreadPoolException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Tried to initialize 'Closing' pool");
		}
		state = State::Running;
		auto ptr = this;
		auto driver = [](auto obj)
		{
			obj->threadDriver();
		};
		while (threads.size() < threadCount)
		{
			threads.emplace_back(driver, ptr);
			++runningCount;
		}
	}
	
	JobHandle _Pool::addJob(const std::function<void()> func)
	{
		std::shared_ptr<Job> ptr;
		jobs.push_back(ptr = std::make_shared<Job>(func));
		JobHandle handle(ptr);
		cond.notify_one();
		return handle;
	}
	
	void _Pool::setThreads(const unsigned int count)
	{
		throw NotImp();
	}
	
	unsigned int _Pool::getThreads() const
	{
		return threadCount;
	}
	
	std::shared_future<void> _Pool::pause()
	{
		throw NotImp();
	}
	
	std::shared_future<void> _Pool::close()
	{
		{
		std::shared_lock<std::shared_timed_mutex> shared_lock(control_m);
		if (state == State::Closing)
		{
			return closeFuture;
		}
		
		}
		
		std::lock_guard<std::shared_timed_mutex> lock(control_m);
		
		auto oldState = state;
		
		if (state == State::Closing)
		{
			return closeFuture;
		}
		
		state = State::Closing;
		closeFuture = closePromise.get_future().share();
		cond.notify_all();
		
		if (oldState == State::Created || runningCount == 0)
		{
			closePromise.set_value();
		}
		
		
		return closeFuture;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	void _Pool::threadDriver()
	{
		try
		{
		//Sync with the other threads to
		//prevent a runningCount race cond
		control_m.lock_shared();
		control_m.unlock_shared();
		try
		{
			bool emergencyExit = false;
			const auto& stateRef = this->state;
			const auto& jobsRef = this->jobs;
			while (true)
			{
				std::unique_lock<std::mutex> lock(job_m);
				//Main code here
				cond.wait(lock, 
				[&stateRef, &jobsRef, &emergencyExit] ()
				{
					try
					{
					return
					(stateRef == State::Closing) ||
					(jobsRef.ready() > 0);
					}
					catch (...)
					{
						emergencyExit = true;
						return true;
					}
				});
				
				if (emergencyExit || state == State::Closing)
				{
					break;
				}
				
				//TODO
				std::cerr << "Breaking...\n" << std::flush;
				
				
				
				
			}
		}
		catch (...)
		{
			
		}
		
		int running = --runningCount;
		if (running == 0)
		{
			bool last_out;
			{
				std::shared_lock<std::shared_timed_mutex> shared_lock(control_m);
				last_out = (state == State::Closing);
			}
			
			if (last_out)
			{
				std::lock_guard<std::shared_timed_mutex> lock(control_m);
				closePromise.set_value();
			}
		}
		}
		catch (std::exception& ex)
		{
			std::cerr << "Exception caught!\n" << ex.what() << "\n";
		}
		catch (...)
		{}
	}
	
}
}
}