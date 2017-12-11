#pragma once
#include <string>

#include "ForwardDecs.h"
#include "Created.h"

namespace QUtils { namespace Reddit {
	
	
	class Message : public Created
	{
		private:
		
		protected:
		Message(RedditSystem* sys, json_ptr&&);
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::t4;
		
		std::string author_name() const;
		Account* author() const;
		std::string body() const;
		std::string body_html() const;
		std::string context() const;
		std::string first_message_id() const;
		Message* first_message() const;
		bool likes() const;
		std::string link_title() const;
		Link* link() const;
		bool unread() const;
		std::string parent_id() const;
		Listing<Thing*>* replies() const;
		std::string subject() const;
		std::string subreddit_name() const;
		Subreddit* subreddit() const;
		bool was_comment() const;
		
		
		virtual typename Reddit::Kind kind() const override
		{
			return Kind;
		}
		
		friend class RedditSystem;
	};
	
	
	
}
}