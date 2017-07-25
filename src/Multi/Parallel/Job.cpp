#include <QUtils/Multi/Parallel/Job.h>

namespace QUtils
{
namespace Multi
{
	void Job::readinessChanged(bool b)
	{
		if (!b)
		{
			if (this->isReady)
			{
				this->isReady = false;
				for (auto dep : this->_dependents)
				{
					dep->child()->readinessChanged(false);
				}
			}
		}
		else if (!this->isReady)
		{
			for (auto it = dependencies().begin(); it != dependencies().end() && b; ++it)
			{
				b = b && (*it)->parent()->ready();
			}
			if (b)
			{
				this->isReady = true;
				for (auto dep : _dependents)
				{
					dep->child()->readinessChanged(true);
				}
			}
		}
	}
	
	void Job::depends(std::shared_ptr<Job> job)
	{
		std::shared_ptr<Job> thisPtr;
		try
		{
			thisPtr = shared_from_this();
		}
		catch (std::bad_weak_ptr&)
		{
			thisPtr = std::shared_ptr<Job>(this);
		}
		auto dep = std::make_shared<Dependency>(thisPtr, job);
		this->_dependencies.push_back(dep);
		job->_dependents.push_back(dep);
		
		if (!job->ready())
		{
			this->readinessChanged(false);
		}
	}
		
	const std::vector<std::shared_ptr<Dependency>>& Job::dependencies() const
	{
		return this->_dependencies;
	}
	
	const std::vector<std::shared_ptr<Dependency>>& Job::dependents() const
	{
		return this->_dependents;
	}
	
	std::vector<std::shared_ptr<Job>> Job::previousJobs()
	{
		std::vector<std::shared_ptr<Job>> prev;
		for (auto dep : _dependencies)
		{
			prev.push_back(dep->parent());
			for (auto subdep : dep->parent()->previousJobs())
			{
				prev.push_back(subdep);
			}
		}
		return prev;
	}
	
	std::vector<std::shared_ptr<const Job>> Job::previousJobs() const
	{
		std::vector<std::shared_ptr<const Job>> prev;
		for (auto dep : _dependencies)
		{
			prev.push_back(dep->parent());
			for (auto subdep : dep->parent()->previousJobs())
			{
				prev.push_back(subdep);
			}
		}
		return prev;
	}
	
	void Job::addCallback(std::function<void()> callback)
	{
		callbacks.push_back(callback);
	}
	
	void Job::wait()
	{
		if (!launched)
		{
		std::unique_lock<std::mutex> lk(condMut);
		cond.wait(lk);
		}
		this->launchFuture.wait();
	}
	
	std::shared_ptr<const std::exception> Job::exception() const
	{
		return ex;
	}
}
}