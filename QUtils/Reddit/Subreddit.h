#pragma once
#include <string>

#include "ForwardDecs.h"
#include "Votable.h"
#include "Created.h"

namespace QUtils { namespace Reddit {
	
	
	class Subreddit : public Thing
	{
		private:
		
		protected:
		Subreddit(RedditSystem* sys, json_ptr&&);
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::t5;
		
		//Attributes
		int accounts_active() const;
		int comment_score_hide_mins() const;
		std::string description() const;
		std::string description_html() const;
		std::string display_name() const;
		std::string header_img() const;
		//Array header_size() const;
		std::string header_title() const;
		bool over_18() const;
		std::string public_description() const;
		bool public_traffic() const;
		long subscribers() const;
		std::string submission_type() const;
		std::string submit_link_label() const;
		std::string submit_text_label() const;
		std::string subreddit_type() const;
		std::string title() const;
		std::string url() const;
		bool user_is_banned() const;
		bool user_is_contributor() const;
		bool user_is_moderator() const;
		bool user_is_subscriber() const;
		
		
		//Methods
		Listing<Link>* getListing(int count = 10) const;
		
		
		friend class RedditSystem;
	};
	
	
	
}
}