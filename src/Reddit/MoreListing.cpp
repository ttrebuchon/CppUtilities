#include <QUtils/Reddit/MoreListing.h>
#include <QUtils/Debug/dassert.h>
#ifdef DEBUG
#include <fstream>
#endif

namespace QUtils { namespace Reddit {
	
	template <>
	std::size_t MoreListing<Comment>::loadMore(bool all)
	{
		if (more.size() == 0)
		{
			return 0;
		}
		std::size_t count = 0;
		if (all)
		{
			while (more.size() > 0)
			{
				count += loadMore();
			}
			return count;
		}
		More* more = this->more.front();
		this->more.pop_front();
		try
		{
		
		
		
		
		const std::string parentName = more->parent_id();
		std::string link_id = parentName;
		if (link_id.substr(0, 3) != "t3_")
		{
			Comment* parent = dynamic_cast<Comment*>(sys->thingsByName.at(parentName));
			link_id = parent->link_id();
		}
		const std::string id = more->id();
		const std::string path = "/api/morechildren.json";
		//const std::string query = "api_type=json&limit_children=false&link_id=" + link_id + "&id=" + id + "&children=";
		const std::string query = "api_type=json&link_id=" + link_id + "&id=" + id + "&children=";
		more->children();
		auto& children = more->_children;
		
		
		
		std::string childrenStr;
		{
		auto it = children.begin();
		int i = 1;
		while (it != children.end())
		{
			if (*it != "")
			{
				break;
			}
		}
		if (it == children.end())
		{
			return 0;
		}
		childrenStr += *it;
		dassert(*it != "");
		++it;
		while (it != children.end() && i < 100)
		{
			if (*it == "")
			{
				++it;
				continue;
			}
			if (sys->thingsByName.count("t1_" + *it) > 0)
			{
				it = children.erase(it);
				continue;
			}
			if (childrenStr.length() + 1 + it->length() + path.length() + query.length() >= 900)
			{
				//break;
			}
			childrenStr += ",";
			childrenStr += *it;
			++i;
			++it;
		}
		}
		
		nlohmann::json result;
		sys->getJSON(result, path, query + childrenStr);
		
		std::list<nlohmann::json> jcomments;
		std::map<std::string, Comment*> comments;
		
		std::list<More*> mores;
		for (auto& thing : result.at("json").at("data").at("things"))
		{
			if (thing.at("data").at("id").get<std::string>()[0] == '_')
			{
				continue;
			}
			if (thing.at("kind").get<std::string>() == "more")
			{
				std::string oldName = thing.at("data").at("name").get<std::string>();
				
				dassert(oldName[3] != '_');
				thing.at("data")["name"] = "more_" + oldName;
				dassert(thing.at("data").at("name").get<std::string>().substr(0, 5) == "more_");
				if (thing.at("data").at("parent_id") == more->parent_id())
				{
					More* m = new More(sys, std::make_unique<nlohmann::json>(thing.at("data")));
					this->more.push_back(m);
				}
				else
				{
					More* m = new More(sys, std::make_unique<nlohmann::json>(thing.at("data")));
					dassert(m->name().substr(0, 4) == "more");
					mores.push_back(m);
				}
				continue;
			}
			
			std::string name = thing.at("data").at("name");
			if (sys->thingsByName.count(name) > 0)
			{
				dassert(sys->thingsByName.at(name) != NULL);
				comments[name] = dynamic_cast<Comment*>(sys->thingsByName.at(name));
				dassert(sys->thingsByName.at(name)->name() == name);
				if (sys->thingsByName.at(name)->kind() != Kind::t1)
				{
					std::cerr << "[" << KindToString(sys->thingsByName.at(name)->kind()) << "] - ";
					std::cerr << sys->thingsByName.at(name)->name() << "\n";
				}
				dassert(sys->thingsByName.at(name)->kind() == Kind::t1);
				dassert(comments[name] != NULL);
			}
			else
			{
				jcomments.push_back(thing);
			}
		}
		
		
		
		
		
		
		result = nlohmann::json();
		
		for (auto& c : jcomments)
		{
			c.at("data").at("replies") = {
				{"kind",  "Listing"},
				{"data", {
					
					{"children",  "[]"_json },
					{"after", "null"_json},
					{"before", "null"_json},
					{"modhash", "null"_json}
					
				}
				}
			};
			dassert(c.at("data").at("replies").is_object());
			dassert(c.at("data").at("replies").at("data").is_object());
			dassert(c.at("data").at("replies").at("data").at("children").is_array());
			
		}
		
		for (auto it = jcomments.begin(); it != jcomments.end();)
		{
			if (it->at("data").at("parent_id").get<std::string>() == parentName)
			{
				std::string name = it->at("data").at("name");
				this->children.push_back(comments[name] = new Comment(sys, std::make_unique<nlohmann::json>(it->at("data"))));
				dassert(comments.at(name) != NULL);
				++count;
				it = jcomments.erase(it);
			}
			else
			{
				++it;
			}
		}
		
		
		
		auto it = jcomments.begin();
		while (jcomments.size() > 0)
		{
			std::string parentName = it->at("data").at("parent_id").get<std::string>();
			if (comments.count(parentName) > 0)
			{
				Comment* parent = comments.at(parentName);
				dassert(parent != NULL);
				std::string name = it->at("data").at("name");
				Comment* child = new Comment(sys, std::make_unique<nlohmann::json>(it->at("data")));
				++count;
				dassert(parent->replies() != NULL);
				parent->replies()->children.push_back(child);
				dassert(child != NULL);
				comments[name] = child;
				
				
				it = jcomments.erase(it);
			}
			else
			{
				++it;
			}
			
			if (it == jcomments.end())
			{
				it = jcomments.begin();
			}
		}
		
		for (auto m : mores)
		{
			std::string parentName = m->parent_id();
			Comment* parent = comments.at(parentName);
			parent->replies()->more.push_back(m);
		}
		
		return count;
		}
		catch (...)
		{
			this->more.push_front(more);
			throw;
		}
	}
}
}