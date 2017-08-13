#pragma once

#include "../ValueType.h"
#include "MetaTypeHelpers.h"

namespace QUtils
{
namespace SQL
{
	class SQLMinEntity
	{
		protected:
		std::string _name;
		bool _notNull;
		bool _unique;
		
		public:
		SQLMinEntity(const std::string name) : _name(name), _notNull(false), _unique(false), dbType(Null)
		{
			
		}
		
		virtual ValueType resolveType(SQLModels*) = 0;
		
		ValueType dbType;
		
		virtual std::type_index objectIndex() const = 0;
		virtual std::type_index typeIndex() const = 0;
		/*virtual std::type_index dbTypeIndex() const = 0;*/
		
		std::string name() const
		{
			return _name;
		}
		
		bool notNull() const
		{
			return _notNull;
		}
		
		bool unique() const
		{
			return _unique;
		}
		
		
	};
	
	template <class Object>
	class SQLEntity : public SQLMinEntity
	{
		public:
		std::function<std::shared_ptr<SQLType>(Object&)> toSQLType;
		
		Helpers::ToSQL_t<Object> serialize;
		Helpers::SetSQL_t<Object> deserialize;
		
		SQLEntity(const std::string name) : SQLMinEntity(name), toSQLType()
		{
			
		}
		
		virtual std::type_index objectIndex() const override
		{
			return std::type_index(typeid(Object));
		}
	};
}
}