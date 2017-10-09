#pragma once
#include <atomic>
#include <memory>
#include <deque>
#include <QUtils/Multi/Mutexed.h>
//#include <shared

namespace QUtils { namespace Network {
	
	class Message;
	
	class Channel : public std::enable_shared_from_this<Channel>
	{
		private:
		
		typedef std::lock_guard<Multi::Mutexed<std::deque<std::shared_ptr<Message>>*>> lock_guard_t;
		
		protected:
		QUtils::Multi::Mutexed<std::deque<std::shared_ptr<Message>>*> messages;
		
		void addMessage(std::shared_ptr<Message>);
		
		template <class Begin, class End>
		void addMessages(Begin begin, End end)
		{
			if (begin == end)
			{
				return;
			}
			lock_guard_t lock(messages);
			(*messages)->insert((*messages)->end(), begin, end);
			hasMessages = true;
		}
		
		
		
		Channel(bool hasMessages, bool isValid);
		Channel();
		
		public:
		std::atomic<bool> hasMessages;
		std::atomic<bool> stillValid;
		
		
		
		std::shared_ptr<Message> getNext();
		std::deque<std::shared_ptr<Message>>* getAll();
		virtual bool gatherMessages() = 0;
		
		
		
	};
	
}
}