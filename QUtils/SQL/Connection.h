#pragma once

#include <string>

#include <QUtils/Exception/Exception.h>

namespace Util
{
namespace SQL
{
	UTIL_CUSTOM_EXCEPTION(SQLErrorException,);
	
	class Query;
	
	class Connection
	{
		protected:
		
		public:
		
		virtual bool isOpen() const = 0;
		virtual void open() = 0;
		virtual void close() = 0;
		
		virtual Query* query(std::string) const = 0;
		
		virtual bool vQuery(std::string) = 0;
		
		virtual Query* tablesQuery() const = 0;
		
	};
}
}