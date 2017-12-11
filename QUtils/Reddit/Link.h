#pragma once
#include <string>

#include "ForwardDecs.h"
#include "Votable.h"
#include "Created.h"

namespace QUtils { namespace Reddit {
	
	
	class Link : public Votable, public Created
	{
		private:
		
		protected:
		Link(RedditSystem* sys, json_ptr&&);
		
		mutable MoreListing<Comment>* _comments;
		
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::t3;
		
		std::string author_name() const;
		Account* author() const;
		std::string author_flair_css_class() const;
		std::string author_flair_text() const;
		bool clicked() const;
		std::string domain() const;
		bool hidden() const;
		bool is_self() const;
		std::string link_flair_css_class() const;
		std::string link_flair_text() const;
		bool locked() const;
		//Object media() const;
		//Object media_embed() const;
		int num_comments() const;
		bool over_18() const;
		std::string permalink() const;
		bool saved() const;
		std::string selftext() const;
		std::string selftext_html() const;
		std::string subreddit_name() const;
		Subreddit* subreddit() const;
		std::string subreddit_id() const;
		std::string thumbnail() const;
		std::string title() const;
		std::string url() const;
		unsigned long edited() const;
		std::string distinguished() const;
		bool stickied() const;
		
		
		virtual typename Reddit::Kind kind() const override
		{
			return Kind;
		}
		
		
		const MoreListing<Comment>* comments() const;
		MoreListing<Comment>* comments();
		
		friend class RedditSystem;
	};
	
	
	
}
}