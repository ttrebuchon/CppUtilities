#pragma once
#include "Listing.h"
#include "Comment.h"
#include "More.h"

#include <QUtils/Exception/NotImplemented.h>
#include <string>

namespace QUtils { namespace Reddit {
	
	template <class T>
	class MoreListing : public Listing<T>
	{
		protected:
		std::list<More*> more;
		
		public:
		
		MoreListing(RedditSystem* sys, std::shared_ptr<nlohmann::json> jptr) : Listing<T>(sys), more()
		{
			this->json = jptr;
			
			dassert(this->json->count("after") > 0);
			dassert(this->json->count("before") > 0);
			dassert(this->json->count("modhash") > 0);
			
			T* c;
			for (auto& child : this->json->at("children"))
			{
				if (StringToKind(child.at("kind")) == Kind::more)
				{
					std::string oldName = child.at("data").at("name").template get<std::string>();
					child.at("data").at("name") = "more_" + oldName;
					more.push_back(
					new More(
						sys,
						std::make_unique<nlohmann::json>(
						child.at("data")
						)
					)
					);
					continue;
				}
				if (sys->thingsByName.count(child.at("data").at("name")) > 0)
				{
					c = dynamic_cast<T*>(sys->thingsByName.at(child.at("data").at("name")));
				}
				else
				{
					c = dynamic_cast<T*>(sys->parseJSON((nlohmann::json&)child));
					
				}
				
				if (c != NULL)
				{
					this->things[child.at("data").at("name")] = c;
				this->children.push_back(c);
				}
			}
			
			
		}
		
		
		
		std::size_t loadMore(bool all = false)
		{
			for (auto& m : more)
			{
				for (auto& mm : m->children())
				{
					std::cerr << mm << "\n";
				}
			}
			throw NotImp();
		}
		
		inline bool canLoadMore() const
		{
			return more.size() > 0;
		}
		
		friend class RedditSystem;
	};
	
	
	template <>
	std::size_t MoreListing<Comment>::loadMore(bool all);
	
}
}