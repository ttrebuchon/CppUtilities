#pragma once

#include "SQLEntity.h"
#include "../ValueType.h"

#include "MetaTypeHelpers.h"

namespace QUtils
{
namespace SQL
{
	
	
	
	template <class Object, class Type>
	class SQLEntityBuilder : public SQLEntity<Object>
	{
		
		protected:
		std::function<Type&(Object&)> accessor;
		
		
		public:
		
		
		
		SQLEntityBuilder(const std::string name, const std::function<Type&(Object&)> accessor) : SQLEntity<Object>(name), accessor(accessor)
		{
			
		}
		
		SQLEntityBuilder<Object, Type>& name(std::string value)
		{
			this->_name = value;
			return *this;
		}
		
		SQLEntityBuilder<Object, Type>& notNull(bool value = true)
		{
			this->_notNull = value;
			return *this;
		}
		
		SQLEntityBuilder<Object, Type>& unique(bool value = true)
		{
			this->_unique = value;
			return *this;
		}
		
		std::type_index typeIndex() const override
		{
			return std::type_index(typeid(Type));
		}
		
		/*virtual std::type_index dbTypeIndex() const override
		{
			
		}*/
		
		ValueType resolveType(SQLModels* models) override
		{
			ValueType type = SQL_TryValueType<Type>::type;
			auto accessor = this->accessor;
			if (type != Null)
			{
				this->dbType = type;
				this->toSQLType = Helpers::ToSQLTypeHelper<Object, Type>::call(accessor);
				return type;
			}
			
			
			
			
			std::function<SQLType_ptr(Type&)> toSQL;
			std::function<Type(SQLType_ptr)> toType;
			
			type = models->getSQLType<Type>(toSQL, toType);
			if (type == Null)
			{
				throw SQLModelConfigException().Msg("Could not resolve type").Function(__func__);
			}
			
			this->dbType = type;
			this->toSQLType = [toSQL, accessor](Object& obj)
			{
				return toSQL(accessor(obj));
			};
			
			return type;
			
		}
	};
}
}