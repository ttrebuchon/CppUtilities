#pragma once

#include "../ValueType.h"
#include "../SQLQuery.h"

#include <string>
#include <iostream>

namespace QUtils
{
namespace SQL
{
	class SQLQuery;
	
	class SQLType
	{
		protected:
		virtual std::string _to_string() const = 0;
		
		public:
		
		
		static std::shared_ptr<SQLType> Create(const std::string);
		static std::shared_ptr<SQLType> Create(const long);
		static std::shared_ptr<SQLType> Create(const long long);
		static std::shared_ptr<SQLType> Create(const double);
		
		
		virtual ValueType type() const = 0;
		virtual void bind(const std::string, SQLQuery*) const = 0;
		
		friend std::string to_string(const SQLType&);
	};

	using std::to_string;

	std::string to_string(const SQLType& t)
	{
		return t._to_string();
	}

	std::string to_string(std::string str)
	{
		return str;
	}
	
	template <class Type>
	class SQLType_Value : public SQLType
	{
		Type val;
		virtual std::string _to_string() const override
		{
			return to_string(val);
		}
		
		public:
		SQLType_Value(const Type val) : SQLType(), val(val)
		{
			
		}
		
		virtual ValueType type() const override
		{
			return SQL_ValueType<Type>::type;
		}
		
		virtual void bind(const std::string slot, SQLQuery* q) const override
		{
			q->bind(slot, val);
		}
		
		
		
		template <class rType>
		rType get() const
		{
			return static_cast<rType>(val);
		}
		
		Type get() const
		{
			return val;
		}
	};
	
	
	using SQLTextType = SQLType_Value<std::string>;
	
	using SQLIntegerType = SQLType_Value<int>;
	
	using SQLInteger64Type = SQLType_Value<long>;
	
	using SQLDoubleType = SQLType_Value<double>;
	
	typedef std::shared_ptr<SQLType> SQLType_ptr;
}
}