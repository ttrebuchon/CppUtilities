#include <QUtils/Reddit/Comment.h>
#include <QUtils/Reddit/RedditSys.h>
#include <QUtils/Reddit/MoreListing.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/Exception/NotImplemented.h>

#include "Macro.h"

namespace QUtils { namespace Reddit {
	
	Comment::Comment(RedditSystem* sys, json_ptr&& j) : Thing(sys, std::forward<json_ptr>(j)), Votable(), Created()
	{
		dassert(json->count("author") > 0);
		dassert(json->count("replies") > 0);
		dassert(json->count("body") > 0);
		dassert(json->count("body_html") > 0);
		
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
	MoreListing<Comment>* Comment::replies() const
	{
		if (_replies == NULL)
		{
			if (!json->at("replies").is_object())
			{
			json->at("replies") = {
				{"kind",  "Listing"},
				{"data", {
					
					{"children",  "[]"_json },
					{"after", "null"_json},
					{"before", "null"_json},
					{"modhash", "null"_json}
					
				}
				}
			};
			}
			_replies = new MoreListing<Comment>(sys, std::make_shared<nlohmann::json>(json->at("replies").at("data")));
		}
		return _replies;
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