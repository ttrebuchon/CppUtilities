#pragma once
#include <set>
#include <string>
#include <map>
#include <json/json.hpp>

#include "ForwardDecs.h"

namespace QUtils { namespace Reddit {
	
	class RedditSystem
	{
		protected:
		mutable std::set<Thing*> items;
		const std::string api = "utility.ttrebuchon.com/RedditForward.php?"; //"http://www.reddit.com";
		
		virtual std::string getPage(const std::string URL, const std::string queryStr) const = 0;
		
		void getJSON(nlohmann::json&, const std::string path, const std::string queryStr) const;
		
		void addThing(Thing*);
		
		mutable std::map<std::string, Thing*> thingsByName;
		
		Thing* parseURL(const std::string url, const std::string queryStr);
		Thing* parse(const std::string json);
		Thing* parseJSON(nlohmann::json&);
		
		template <class T>
		Listing<T>* parseListingURL(const std::string url, const std::string query)
		{
			return new Listing<T>(this, getListingURL_JSON(url, query));
		}
		std::shared_ptr<nlohmann::json> getListingURL_JSON(const std::string, const std::string);
		std::shared_ptr<nlohmann::json> getListingJSON(nlohmann::json&);
		
		void getCommentJSON(nlohmann::json&, const std::string link_id, const std::string comment_id, bool includeReplies = false) const;
		
		Comment* parseComment(nlohmann::json&);
		Account* parseAccount(nlohmann::json&);
		Link* parseLink(nlohmann::json&);
		
		public:
		RedditSystem() : items()
		{}
		
		virtual ~RedditSystem();
		
		Subreddit* subreddit(const std::string);
		Link* link(const std::string);
		Account* account(const std::string);
		MoreListing<Comment>* comments(const std::string linkID);
		
		
		Thing* parseJSON(const std::string);
		
		friend class Thing;
		friend class Comment;
		friend class Link;
		friend class Account;
		friend class Message;
		friend class Subreddit;
		
		template <class>
		friend class Listing;
		
		template <class>
		friend class MoreListing;
	};
	
	
	
}
}