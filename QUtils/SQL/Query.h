#pragma once
#include "ValueType.h"
#include <string>

namespace Util
{
namespace SQL
{
	class Query
	{
		protected:
		virtual double columnDouble(int) const = 0;
		virtual int columnInt(int) const = 0;
		virtual long columnLong(int) const = 0;
		virtual std::string columnString(int) const = 0;
		
		
		public:
		
		virtual ~Query();
		
		template <class T> T column(int index) const;
		
		virtual int width() const = 0;
		virtual ValueType columnType(int Index) const = 0;
		virtual bool columnNULL(int) const = 0;
		virtual bool next() = 0;
		virtual void reset() = 0;
		virtual bool operator()() = 0;
		virtual std::string columnName(int) const = 0;
		virtual std::string tableName(int) const = 0;
		virtual std::string dbName(int) const = 0;
		virtual std::string statement() const = 0;
		
		
	};
	
}
}