#include <QUtils/Multi/Parallel/Parallelized.h>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace Multi
{
	Parallelized::Parallelized(const unsigned int threads) : threadsMut(), threads(), futures(), jobMnger(), allowedFutures(0), running(0), toRemove(0), destroy(false), jobs(), jobMut(), jobCond()
	{
		threadpool(threads);
		jobMnger = std::async([&]() {
			this->manageJobs();
		});
	}
	
	void Parallelized::manageJobs()
	{
		while (!destroy)
		{
			threadsMut.lock();
			while (jobs.ready() && running < allowedFutures)
			{
				auto j = jobs.get();
				std::cout << "Launching job\n";
				futures.push_back(j->launch());
				++running;
			}
			threadsMut.unlock();
			//std::cout << "Waiting for jobs to be added...\n";
			std::unique_lock<std::mutex> lk(jobs.finishMut);
			jobs.finishCond.wait(lk);
		}
	}
	
	
	void Parallelized::getJob()
	{
		auto job = jobs.get();
		if (job != NULL)
		{
			std::cout << "Got job.\n";
			throw NotImp();
		}
		else
		{
			std::cout << "Waiting for job...\n";
			std::unique_lock<std::mutex> lk(jobMut);
			jobCond.wait(lk);
			return getJob();
		}
	}
	
	void Parallelized::finishJob()
	{
		/*if (toRemove > 0)
		{
			threadsMut.lock();
			if (toRemove > 0)
			{
				removeThread(std::this_thread::get_id());
				threadsMut.unlock();
				return;
			}
			threadsMut.unlock();
		}
		
		throw NotImp();*/
		std::cout << "Job finished" << std::endl;
		threadsMut.lock();
		--running;
		threadsMut.unlock();
	}
	
	void Parallelized::startNext()
	{
		threadsMut.lock();
		this->startNextNoLock();
		threadsMut.unlock();
	}
	
	void Parallelized::startNextNoLock()
	{
		while (running < allowedFutures)
		{
			futures.push_back(std::async(std::launch::async, [&]() { this->getJob(); }));
			++running;
		}
	}
	
	void Parallelized::removeThread(std::thread::id id)
	{
		for (auto it = threads.begin(); it != threads.end(); ++it)
		{
			if (it->get_id() == id)
			{
				threads.erase(it);
				return;
			}
		}
		throw std::exception();
	}
	
	size_t Parallelized::threadpool() const
	{
		return allowedFutures;
		//return threads.size();
	}
	
	size_t Parallelized::threadpool(const size_t nSize)
	{
		/*if (threads.size() > nSize)
		{
			
			toRemove = threads.size() - nSize;
			return nSize;
		}*/
		threadsMut.lock();
		/*if (threads.size() > nSize)
		{
			toRemove = threads.size() - nSize;
		}*/
		allowedFutures = nSize;
		jobs.finishCond.notify_all();
		/*if (running < nSize)
		{
			this->startNextNoLock();
		}*/
		
		
		
		/*while (threads.size() < nSize)
		{
			threads.emplace_back([&]() { this->getJob(); });
		}*/
		threadsMut.unlock();
		
		//throw NotImp();
		return nSize;
	}
	
	size_t Parallelized::activeThreads() const
	{
		throw NotImp();
	}
	
	Parallelized::~Parallelized()
	{
		destroy = true;
		this->jobs.finishCond.notify_all();
		jobMnger.wait();
		for (auto fut : futures)
		{
			fut.wait();
		}
	}
}
}