#pragma once
#include <functional>

#include "RedditSys.h"
#include <QUtils/Exception/Exception.h>

namespace QUtils { namespace Reddit {
	
	template <class F = std::function<std::string(const std::string)>>
	class GenericRedditSystem : public RedditSystem
	{
		public:
		QUTILS_CUSTOM_EXCEPTION(MissingJSONException,);
		QUTILS_CUSTOM_EXCEPTION(WebErrorException,);
		private:
		F func;
		protected:
		
		virtual std::string getPage(const std::string URL, const std::string queryStr) const override
		{
			size_t len = URL.length();
			if (URL.substr((len > 5 ? len-5 : 0)) != ".json")
			{
				throw MissingJSONException().File(__FILE__).Line(__LINE__).Function(__func__).Msg("URL doesn't have \".json\" extension: \"" + URL + "\"");
			}
			try
			{
			return func(URL + "?" + queryStr);
			}
			catch (...)
			{
				throw WebErrorException(std::current_exception(), "Error getting URL").Line(__LINE__).Function(__func__).File(__FILE__).Msg("Unable to get api call to [" + URL + "?" + queryStr + "]");
			}
		}
		
		public:
		GenericRedditSystem(F f) : func(f)
		{}
		
	};
	
	
	
}
}