#include <QUtils/Reddit/Comment.h>
#include <QUtils/Reddit/RedditSys.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	Comment::Comment(RedditSystem* sys, json_ptr&& j) : Thing(sys, (json_ptr&&)j), Votable(), Created()
	{
		
	}
	
	void Comment::refresh()
	{
		throw NotImp();
	}
	
	#define PROPERTY(TYPE, NAME) CLASS_PROPERTY(Comment, TYPE, NAME)
	
	PROPERTY(std::string, approved_by)
	std::string Comment::author_name() const
	{
		return json->at("author");
	}
	Account* Comment::author() const
	{
		throw NotImp();
	}
	PROPERTY(std::string, author_flair_css_class)
	PROPERTY(std::string, author_flair_text)
	PROPERTY(std::string, banned_by)
	PROPERTY(std::string, body)
	PROPERTY(std::string, body_html)
	PROPERTY(unsigned long, edited)
	PROPERTY(int, gilded)
	std::string Comment::link_author_name() const
	{
		return json->at("link_author");
	}
	Account* Comment::link_author() const
	{
		throw NotImp();
	}
	Link* Comment::link() const
	{
		throw NotImp();
	}
	PROPERTY(std::string, link_id)
	PROPERTY(std::string, link_title)
	PROPERTY(std::string, link_url)
	PROPERTY(int, num_reports)
	PROPERTY(std::string, parent_id)
	Comment* Comment::parent() const
	{
		throw NotImp();
	}
	Listing<Thing>* Comment::replies() const
	{
		throw NotImp();
	}
	PROPERTY(bool, saved)
	PROPERTY(bool, score_hidden)
	PROPERTY(std::string, subreddit_name)
	Subreddit* Comment::subreddit() const
	{
		throw NotImp();
	}
	PROPERTY(std::string, subreddit_id)
	PROPERTY(std::string, distinguished)
	
	
	
	
	
	
}
}