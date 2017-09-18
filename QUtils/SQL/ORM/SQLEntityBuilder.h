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
			std::function<Type(SQLType_ptr, SQLSystem*, bool)> toType;
			
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
		
		virtual void resolve(SQLModels* models) override
		{
			auto fAccess = accessor;
			std::function<SQLType_ptr(Type&)> toSQL;
		std::function<Type(SQLType_ptr, SQLSystem*, bool)> fromSQL;
		ValueType vType = models->getSQLType<Type>(toSQL, fromSQL);
		
		if (vType == Null)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("Error retrieving ValueType for Type with Index '") + std::type_index(typeid(Type)).name() + "'");
		}
		
		if (!toSQL)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("Error retrieving toSQL lambda for Type with Index '") + std::type_index(typeid(Type)).name() + "'");
		}

		if (!fromSQL)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("Error retrieving fromSQL lambda for Type with Index '") + std::type_index(typeid(Type)).name() + "'");
		}

		this->serialize = std::function<SQLType_ptr(Object&)>([fAccess, toSQL] (Object& obj)
		{
			return toSQL(fAccess(obj));
		});
		
		this->deserialize = Helpers::SetSQL_t<Object>([fAccess, fromSQL] (Object& obj, SQLType_ptr ptr, SQLSystem* sys, bool includeReferenced)
		{
			fAccess(obj) = fromSQL(ptr, sys, includeReferenced);
		});
		}
	};
}
}