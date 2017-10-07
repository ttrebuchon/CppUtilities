#include <QUtils/Network/Service/Router.h>
#include <QUtils/Network/Service/Channel.h>

namespace QUtils { namespace Network {
	
	std::shared_ptr<Message> Router::next()
	{
		/*if (messageTmpQueue.try_lock())
		{
			while (!messageTmpQueue->empty())
			{
				messages.push(messageTmpQueue->front());
				messageTmpQueue->pop();
				}
			messageTmpQueue.unlock();
		}*/
		std::lock_guard<Multi::Mutexed<std::vector<std::shared_ptr<Channel>>>> lock(channels);
		for (auto it = channels->begin(); it != channels->end(); )
		{
			if ((*it)->hasMessages)
			{
				auto deq = (*it)->getAll();
				for (auto msg : *deq)
				{
					if (msg != NULL)
					{
						messages.push(msg);
					}
				}
				delete deq;
			}
			if (!(*it)->stillValid)
			{
				it = channels->erase(it);
			}
			else
			{
				++it;
			}
		}
		
		
		if (!messages.empty())
		{
			auto t = messages.top();
			messages.pop();
			return t;
		}
		else
		{
			return NULL;
		}
	}
	
	std::shared_ptr<Message> Router::fast_next()
	{
		if (messages.empty())
		{
			return next();
		}
		
		auto t = messages.top();
		messages.pop();
		return t;
	}
	
	bool Router::job()
	{
		auto msg = next();
		if (msg != NULL)
		{
			handleMsg(msg);
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool Router::fast_job()
	{
		auto msg = fast_next();
		if (msg != NULL)
		{
			handleMsg(msg);
			return true;
		}
		else
		{
			return false;
		}
	}
	
	void Router::addChannel(const std::shared_ptr<Channel> channel)
	{
		if (channel == NULL)
		{
			return;
		}
		channels.lock();
		channels->push_back(channel);
		channels.unlock();
	}
	
}
}