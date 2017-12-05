#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/Link.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	Link::Link(RedditSystem* sys, json_ptr&& j) : Thing(sys, (json_ptr&&)j), Votable(), Created()
	{
		
	}
	
	#define PROPERTY(TYPE, NAME) CLASS_PROPERTY(Link, TYPE, NAME)
	
	std::string Link::author_name() const
	{
		return json->at("author");
	}
	
	Account* Link::author() const
	{
		throw NotImp();
	}
	
	
	PROPERTY(std::string, author_flair_css_class)
	PROPERTY(std::string, author_flair_text)
	PROPERTY(bool, clicked)
	PROPERTY(std::string, domain)
	PROPERTY(bool, hidden)
	PROPERTY(bool, is_self)
	PROPERTY(std::string, link_flair_css_class)
	PROPERTY(std::string, link_flair_text)
	PROPERTY(bool, locked)
	PROPERTY(int, num_comments)
	PROPERTY(bool, over_18)
	PROPERTY(std::string, permalink)
	PROPERTY(bool, saved)
	PROPERTY(std::string, selftext)
	PROPERTY(std::string, selftext_html)
	std::string Link::subreddit_name() const
	{
		return json->at("subreddit");
	}
	Subreddit* Link::subreddit() const
	{
		return sys->subreddit(subreddit_name());
	}
	std::string Link::subreddit_id() const
	{
		std::string str = json->at("subreddit_id");
		return (str.length() > 3 ? str.substr(3) : str);
	}
	PROPERTY(std::string, thumbnail)
	PROPERTY(std::string, title)
	PROPERTY(std::string, url)
	PROPERTY(unsigned long, edited)
	PROPERTY(std::string, distinguished)
	PROPERTY(bool, stickied)
	
	
	
	
	
	
}
}