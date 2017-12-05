#pragma once
#include <functional>

#include "RedditSys.h"

namespace QUtils { namespace Reddit {
	
	template <class F = std::function<std::string(const std::string)>>
	class GenericRedditSystem : public RedditSystem
	{
		private:
		F func;
		protected:
		
		virtual std::string getPage(const std::string URL, const std::string queryStr) const override
		{
			return func(URL + "?" + queryStr);
		}
		
		public:
		GenericRedditSystem(F f) : func(f)
		{}
		
	};
	
	
	
}
}