#pragma once

#include "Listing.h"

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Reddit {
	
	template <class T>
	class MoreListing : public Listing<T>
	{
		protected:
		const nlohmann::json* more;
		
		MoreListing(RedditSystem* sys, std::shared_ptr<nlohmann::json> jptr) : Listing<T>(sys), more(nullptr)
		{
			this->json = jptr;
			more = nullptr;
			T* c;
			for (const auto& child : this->json->at("children"))
			{
				if (StringToKind(child.at("kind")) == Kind::more)
				{
					more = &child;
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
		public:
		
		
		
		std::size_t loadMore()
		{
			throw NotImp();
		}
		
		friend class RedditSystem;
	};
	
}
}