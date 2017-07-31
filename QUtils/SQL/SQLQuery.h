#pragma once
#include "ValueType.h"
#include <string>
#include <memory>

namespace QUtils
{
namespace SQL
{
	class SQLQuery : public std::enable_shared_from_this<SQLQuery>
	{
		protected:
		virtual double columnDouble(int) const = 0;
		virtual int columnInt(int) const = 0;
		virtual long columnLong(int) const = 0;
		virtual std::string columnString(int) const = 0;
		
		
		public:
		
		virtual ~SQLQuery();
		
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
		
		
		virtual void unbind() = 0;
		
		virtual void bind(std::string parameter, double value) = 0;
		virtual void bind(std::string parameter, int value) = 0;
		virtual void bind(std::string parameter, long value) = 0;
		virtual void bind(std::string parameter, std::string value) = 0;
		
		virtual void bind(unsigned int index, double value) = 0;
		virtual void bind(unsigned int index, int value) = 0;
		virtual void bind(unsigned int index, long value) = 0;
		virtual void bind(unsigned int index, std::string value) = 0;
		
		
	};
	
}
}