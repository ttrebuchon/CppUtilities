#pragma once

#include "../ValueType.h"

namespace QUtils
{
namespace SQL
{
	class SQLType
	{
		protected:
		
		
		public:
		
		
		static std::shared_ptr<SQLType> Create(const std::string);
		static std::shared_ptr<SQLType> Create(const long);
		static std::shared_ptr<SQLType> Create(const long long);
		static std::shared_ptr<SQLType> Create(const double);
		
		
		virtual ValueType type() const = 0;
	};
	
	
	template <class Type>
	class SQLType_Value : public SQLType
	{
		Type val;
		
		public:
		SQLType_Value(const Type val) : SQLType(), val(val)
		{
			
		}
		
		virtual ValueType type() const override
		{
			return SQL_ValueType<Type>::type;
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
}
}