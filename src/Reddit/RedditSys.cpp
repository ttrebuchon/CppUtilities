#include <QUtils/Reddit/Thing.h>
#include <QUtils/Reddit/RedditSys.h>
#include <QUtils/Reddit/Subreddit.h>
#include <QUtils/Reddit/Link.h>
#include <QUtils/Reddit/Listing.h>
#include <QUtils/Reddit/MoreListing.h>
#include <QUtils/Reddit/Account.h>
#include <QUtils/Reddit/Comment.h>

#include <QUtils/Debug/DAssert.h>
#include <QUtils/String.h>
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Exception/Exception.h>
#include <memory>

#ifdef DEBUG
#include <iostream>
#include <fstream>
#endif

namespace QUtils { namespace Reddit {
	
	
	#define PRINT_KEYS(x) \
	for (auto it = x.begin(); it != x.end(); ++it) \
	{ \
		std::cerr << it.key() << std::endl; \
	}
	
	QUTILS_CUSTOM_EXCEPTION(ParseException,);
	QUTILS_CUSTOM_EXCEPTION(InvalidURLException,); 
	
	Subreddit* RedditSystem::subreddit(const std::string name)
	{
		String lower = String(name).toLower();
		
		if (thingsByName.count(lower) > 0)
		{
			return (Subreddit*)thingsByName.at(lower);
		}
		auto j = nlohmann::json::parse(this->getPage(api + "/r/" + name + "/about.json", ""));
		dassert(j.count("kind") == 1);
		if (j.at("kind") == "Listing")
		{
			dassert(j.count("data") == 1);
			j = j.at("data");
			dassert(j.count("children") == 1);
			j = j.at("children");
			dassert(j.is_array());
			dassert(j.size() == 0);
			return NULL;
		}
		
		dassert(j.at("kind") == "t5");
		j = j.at("data");
		
		auto jptr = std::make_unique<nlohmann::json>();
		std::swap(*jptr, j);
		
		auto sub = new Subreddit(this, (Thing::json_ptr&&)std::move(jptr));
		
		thingsByName[lower] = sub;
		String lowerFullName = sub->name();
		lowerFullName = lowerFullName.toLower();
		
		if (thingsByName.count(lowerFullName) <= 0)
		{
			thingsByName[lowerFullName] = sub;
			
		}
		
		return sub;
	}
	
	Link* RedditSystem::link(const std::string id)
	{
		String low = String(id).toLower();
		if (thingsByName.count("t3_" + low) > 0)
		{
			auto link = dynamic_cast<Link*>(thingsByName.at("t3_" + low));
			if (link == NULL)
			{
				thingsByName.erase("t3_" + low);
			}
			else
			{
				return link;
			}
		}
		auto j = nlohmann::json::parse(this->getPage(api + "/" + id + ".json", ""));
		dassert(j.is_array());
		j = j[0];
		dassert(j.is_object());
		dassert(j.at("kind") == "Listing");
		dassert(j.at("data").is_object());
		j = j.at("data").at("children");
		dassert(j.is_array());
		j = j[0];
		dassert(j.at("kind") == "t3");
		
		j = j.at("data");
		
		auto jptr = std::make_unique<nlohmann::json>();
		std::swap(*jptr, j);
		
		auto link = new Link(this, (Thing::json_ptr&&)std::move(jptr));
		
		String name = String(link->name()).toLower();
		if (thingsByName.count(name) <= 0)
		{
			thingsByName[name] = link;
		}
		
		return link;
	}
	
	Account* RedditSystem::account(const std::string name)
	{
		String low = String(name).toLower();
		if (thingsByName.count(low) > 0)
		{
			Account* account = dynamic_cast<Account*>(thingsByName.at(low));
			if (account == NULL)
			{
				thingsByName.erase(low);
			}
			else
			{
				return account;
			}
		}
		
		
		auto j = nlohmann::json::parse(this->getPage(api + "/u/" + name + "/about.json", ""));
		dassert(j.is_object());
		dassert(j.at("kind") == "t2");
		dassert(j.at("data").is_object());
		j = j.at("data");
		
		auto jptr = std::make_unique<nlohmann::json>();
		std::swap(*jptr, j);
		
		auto account = new Account(this, (Thing::json_ptr&&)std::move(jptr));
		
		thingsByName[low] = account;
		
		low = String(account->name()).toLower();
		if (thingsByName.count(low) <= 0)
		{
			thingsByName[low] = account;
		}
		
		
		return account;
	}
	
	MoreListing<Comment>* RedditSystem::comments(const std::string id)
	{
		auto j = nlohmann::json::parse(this->getPage(api + "/" + id + ".json", ""));
		
		dassert(j.is_array());
		j = j[1];
		dassert(j.is_object());
		dassert(j.at("kind") == "Listing");
		j = j.at("data");
		
		return new MoreListing<Comment>(this, std::make_shared<nlohmann::json>(j));
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	void RedditSystem::getJSON(nlohmann::json& j, const std::string path, const std::string query) const
	{
		std::cerr << (api + path) << "?" << query << std::endl;
		std::ofstream file("URL.txt");
		file << (api + path) << "?" << query << std::endl;
		file.close();
		{
			const std::string res = this->getPage(api + path, query);
			j = nlohmann::json::parse(res);
		}
	}
	
	void RedditSystem::addThing(Thing* thing)
	{
		dassert(thing->name() != "");
		dassert(thingsByName.count(thing->name()) <= 0);
		items.insert(thing);
		thingsByName[thing->name()] = thing;
	}
	
	
	
	Thing* RedditSystem::parseURL(const std::string url, const std::string queryStr)
	{
		const std::string str = this->getPage(api + url + ".json", queryStr);
		if (str[0] == '<')
		{
			throw InvalidURLException().File(__FILE__).Function(__func__).Line(__LINE__).Msg("Invalid URL \"" + api + url + "\"");
		}
		return parse(str);
	}
	
	
	Thing* RedditSystem::parse(const std::string json)
	{
		nlohmann::json j;
		try
		{
			j = nlohmann::json::parse(json);
		}
		catch (std::exception& ex)
		{
			throw ParseException(std::current_exception(), "JSON Exception").Line(__LINE__).File(__FILE__).Function(__func__).Msg("Could not parse '" + json + "'");
		}
		return this->parseJSON((nlohmann::json&)j);
	}
	
	Thing* RedditSystem::parseJSON(nlohmann::json& j)
	{
		if (j.is_object())
		{
			if (j.count("kind") > 0)
			{
				switch (StringToKind(j.at("kind")))
				{
					case Kind::t1:
					return parseComment(j);
					
					case Kind::t2:
					return parseAccount(j);
					
					case Kind::t3:
					return parseLink(j);
					
					default:
					throw NotImp().Msg(std::string("Kind: ") + KindToString(StringToKind(j.at("kind"))));
				}
			}
		}
		else if (j.is_array())
		{
			
		}
		throw NotImp();
	}
	
	
	
	std::shared_ptr<nlohmann::json> RedditSystem::getListingURL_JSON(const std::string url, const std::string query)
	{
		nlohmann::json j = nlohmann::json::parse(this->getPage(api + url, query));
		return getListingJSON(j);
	}
	
	std::shared_ptr<nlohmann::json> RedditSystem::getListingJSON(nlohmann::json& j)
	{
		dassert(j.count("kind") == 1);
		dassert(j.at("kind") == "Listing");
		
		nlohmann::json& data = j.at("data");
		dassert(data.is_object());
		
		dassert(data.count("after") == 1);
		dassert(data.count("before") == 1);
		dassert(data.count("children") == 1);
		nlohmann::json& children = data.at("children");
		dassert(children.is_array());
		
		return std::make_shared<nlohmann::json>(data);
	}
	
	Comment* RedditSystem::parseComment(nlohmann::json& j)
	{
		dassert(j.count("kind") == 1);
		dassert(j.at("kind") == "t1");
		
		nlohmann::json& data = j.at("data");
		dassert(data.is_object());
		
		return new Comment(this, std::make_unique<nlohmann::json>(data));
	}
	
	Account* RedditSystem::parseAccount(nlohmann::json& j)
	{
		dassert(j.count("kind") == 1);
		dassert(j.at("kind") == "t2");
		
		nlohmann::json& data = j.at("data");
		PRINT_KEYS(data);
		dassert(data.is_object());
		
		throw NotImp();
	}
	
	static_assert(sizeof(Listing<Thing>) == sizeof(Listing<Link>), "");
	
	Link* RedditSystem::parseLink(nlohmann::json& j)
	{
		dassert(j.count("kind") == 1);
		dassert(j.at("kind") == "t3");
		
		nlohmann::json& data = j.at("data");
		dassert(data.is_object());
		
		auto link = new Link(this, std::make_unique<nlohmann::json>(data));
		
		return link;
	}
}
}