#pragma once
#include <string>
#include <list>
#include <QUtils/Iterable/Interfaces/IList.h>

#include "Thing.h"

namespace QUtils { namespace Reddit {
	
	
	template <class T>
	class Listing : public Thing, public Iterable::IList<T>
	{
		static_assert(std::is_base_of<Thing, T>::value, "");
		private:
		
		
		
		protected:
		std::list<T*> children;
		
		Listing(RedditSystem* sys, json_ptr&&);
		
		public:
		
		auto begin()
		{
			return children.begin();
		}
		
		auto end()
		{
			return children.end();
		}
		
		auto begin() const
		{
			return children.begin();
		}
		
		auto end() const
		{
			return children.end();
		}
		
		auto cbegin() const
		{
			return children.begin();
		}
		
		auto cend() const
		{
			return children.end();
		}
		
		
		friend class RedditSystem;
		
	};
	
	
	
}
}