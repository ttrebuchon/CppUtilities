#pragma once
#include <string>

#include "ForwardDecs.h"
#include "Votable.h"
#include "Created.h"

namespace QUtils { namespace Reddit {
	
	
	class Comment : public Votable, public Created
	{
		private:
		
		protected:
		mutable MoreListing<Comment>* _replies = NULL;
		Comment(RedditSystem* sys, json_ptr&&);
		
		
		public:
		constexpr static Reddit::Kind Kind = Reddit::Kind::t1;
		
		virtual void refresh() override;
		
		std::string approved_by() const;
		std::string author_name() const;
		Account* author() const;
		std::string author_flair_css_class() const;
		std::string author_flair_text() const;
		std::string banned_by() const;
		std::string body() const;
		std::string body_html() const;
		unsigned long edited() const;
		int gilded() const;
		std::string link_author_name() const;
		Account* link_author() const;
		Link* link() const;
		std::string link_id() const;
		std::string link_title() const;
		std::string link_url() const;
		int num_reports() const;
		std::string parent_id() const;
		Comment* parent() const;
		MoreListing<Comment>* replies() const;
		bool saved() const;
		bool score_hidden() const;
		std::string subreddit_name() const;
		Subreddit* subreddit() const;
		std::string subreddit_id() const;
		std::string distinguished() const;
		
		
		virtual typename Reddit::Kind kind() const override
		{
			return Kind;
		}
		
		
		friend class RedditSystem;
		
		template <class>
		friend class MoreListing;
	};
	
	
	
}
}