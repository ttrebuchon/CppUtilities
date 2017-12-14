#pragma once
#include <string>
#include <list>
#include <QUtils/Iterable/IIterable.h>
#include <QUtils/Types/Void_t.h>
#include <QUtils/Debug/dassert.h>

#include "Thing.h"
#include "RedditSys.h"

namespace QUtils { namespace Reddit {
	
	namespace Meta
	{
		template <class T, class = void>
		struct NotNone : std::false_type
		{
			
		};
		
		template <class T>
		struct NotNone<T, Types::void_t<decltype(T::Kind)>>
		{
			constexpr static bool value = (T::Kind != Reddit::Kind::none);
		};
		
	}
	
	
	template <class T>
	class Listing : public Iterable::IIterable<T*>
	{
		static_assert(std::is_base_of<Thing, T>::value, "");
		static_assert(std::is_same<T, Thing>::value || Meta::NotNone<T>::value, "");
		private:
		
		
		
		protected:
		RedditSystem* sys;
		std::shared_ptr<nlohmann::json> json;
		std::list<T*> children;
		std::map<std::string, Thing*> things;
		
		Listing(RedditSystem* sys) : Iterable::IIterable<T*>(children), sys(sys), json(nullptr), children(), things()
		{}
		
		Listing(RedditSystem* sys, std::shared_ptr<nlohmann::json> jptr) : Iterable::IIterable<T*>(children), sys(sys), json(jptr), children(), things()
		{
			dassert(json->count("after") > 0);
			dassert(json->count("before") > 0);
			dassert(json->count("modhash") > 0);
			T* c;
			for (const auto& child : json->at("children"))
			{
				if (sys->thingsByName.count(child.at("data").at("name")) > 0)
				{
					c = dynamic_cast<T*>(sys->thingsByName.at(child.at("data").at("name")));
					children.push_back(c);
				}
				else
				{
					c = dynamic_cast<T*>(sys->parseJSON((nlohmann::json&)child));
					
				}
				
				if (c != NULL)
				{
					things[child.at("data").at("name")] = c;
				children.push_back(c);
				}
			}
		}
		
		void push_back(T* t)
		{
			if (t == nullptr)
			{
				return;
			}
			things[t->name()] = t;
			children.push_back(t);
		}
		
		public:
		
		typedef typename Iterable::IIterable<T*>::iterator iterator;
		typedef typename Iterable::IIterable<T*>::const_iterator const_iterator;
		
		iterator begin()
		{
			return children.begin();
		}
		
		iterator end()
		{
			return children.end();
		}
		
		const_iterator begin() const
		{
			return children.begin();
		}
		
		const_iterator end() const
		{
			return children.end();
		}
		
		const_iterator cbegin() const
		{
			return children.begin();
		}
		
		const_iterator cend() const
		{
			return children.end();
		}
		
		
		std::string after() const
		{
			auto& a = json->at("after");
			if (!a.is_null())
			{
				return a;
			}
			else
			{
				return "";
			}
		}
		
		std::string before() const
		{
			auto& b = json->at("before");
			if (!b.is_null())
			{
				return b;
			}
			else
			{
				return "";
			}
		}
		
		std::string modhash() const
		{
			return json->at("modhash");
		}
		
		
		friend class RedditSystem;
		
	};
	
	
	
}
}