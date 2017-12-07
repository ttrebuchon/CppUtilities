#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/Subreddit.h>
#include <QUtils/Reddit/Link.h>
#include <QUtils/Reddit/Listing.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	Subreddit::Subreddit(RedditSystem* sys, json_ptr&& j) : Thing(sys, (json_ptr&&)j)
	{
		
	}
	
	#define PROPERTY(TYPE, NAME) CLASS_PROPERTY(Subreddit, TYPE, NAME)
	
	
	PROPERTY(int, accounts_active)
	PROPERTY(int, comment_score_hide_mins)
	PROPERTY(std::string, description)
	PROPERTY(std::string, description_html)
	PROPERTY(std::string, display_name)
	PROPERTY(std::string, header_img)
	PROPERTY(std::string, header_title)
	bool Subreddit::over_18() const
	{
		return json->at("over18");
	}
	PROPERTY(std::string, public_description)
	PROPERTY(bool, public_traffic)
	PROPERTY(long, subscribers)
	PROPERTY(std::string, submission_type)
	PROPERTY(std::string, submit_link_label)
	PROPERTY(std::string, submit_text_label)
	PROPERTY(std::string, subreddit_type)
	PROPERTY(std::string, title)
	PROPERTY(std::string, url)
	PROPERTY(bool, user_is_banned)
	PROPERTY(bool, user_is_contributor)
	PROPERTY(bool, user_is_moderator)
	PROPERTY(bool, user_is_subscriber)
	
	
	//Methods
	Listing<Link>* Subreddit::getListing(int limit) const
	{
		
		return Thing::parseListingURL<Link>("/r/" + display_name() + ".json", "limit=" + std::to_string(limit));
	}
	
	
}
}