#include <QUtils/Network/Service/Channel.h>

namespace QUtils { namespace Network {
	Channel::Channel(bool hasMessages, bool isValid) : messages(new std::deque<std::shared_ptr<Message>>()), hasMessages(hasMessages), stillValid(isValid)
	{
	}
	
	Channel::Channel() : Channel(false, true)
	{
	}
	
	void Channel::addMessage(std::shared_ptr<Message> msg)
	{
		
		 lock_guard_t lock(messages);
			(*messages)->push_back(msg);
			hasMessages = true;
	}
	
	
	std::shared_ptr<Message> Channel::getNext()
	{
		lock_guard_t lock(messages);
		auto front = (*messages)->front();
		(*messages)->pop_front();
		if ((*messages)->size() == 0)
		{
			hasMessages = false;
		}
		return front;
	}
	
	std::deque<std::shared_ptr<Message>>* Channel::getAll()
	{
		std::deque<std::shared_ptr<Message>>* ptr;
		{
			lock_guard_t lock(messages);
			ptr = (*messages);
			messages = new std::deque<std::shared_ptr<Message>>();
			hasMessages = false;
		}
		return ptr;
	}
}
}