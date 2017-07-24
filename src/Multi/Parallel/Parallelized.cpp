#include <QUtils/Multi/Parallel/Parallelized.h>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace Multi
{
	Parallelized::Parallelized(const unsigned int threads) : threads(), futures(), allowedFutures(0), toRemove(0), jobs(), jobMut(), jobCond()
	{
		toRemove = threads;
		threadpool(threads);
	}
	
	
	void Parallelized::getJob()
	{
		toRemove.lock();
		auto i = *toRemove;
		if (i > 0)
		{
			--(*toRemove);
			toRemove.unlock();
			return;
		}
		throw NotImp();
	}
	
	size_t Parallelized::threadpool() const
	{
		return threads.size();
	}
	
	size_t Parallelized::threadpool(const size_t nSize)
	{
		allowedFutures = nSize;
		/*if (threads.size() > nSize)
		{
			
			toRemove = threads.size() - nSize;
			return nSize;
		}*/
		if (allowedFutures > nSize)
		{
			toRemove = allowedFutures - nSize;
		}
		
		while (threads.size() < nSize)
		{
			threads.emplace_back([&]() { this->getJob(); });
			futures.push_back(std::async(std::launch::async, [&]() { this->getJob(); }));
		}
		
		throw NotImp();
	}
	
	size_t Parallelized::activeThreads() const
	{
		throw NotImp();
	}
	
	Parallelized::~Parallelized()
	{
		
	}
}
}