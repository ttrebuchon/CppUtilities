#pragma once
#include <functional>
#include "../ValueType.h"
#include "SQLType.h"

namespace QUtils
{
namespace SQL
{
	class SQLSystem;
	
	
	namespace Helpers
	{
		template <class Object, class Type, class = void>
		struct ToSQLTypeHelper
		{
			static std::function<std::shared_ptr<SQLType>(Object&)> call(std::function<Type&(Object&)> access)
			{
				return std::function<std::shared_ptr<SQLType>(Object&)>();
			}
		};
		
		
		
		template <class Object, class Type>
		struct ToSQLTypeHelper<Object, Type, Types::void_t<decltype(SQL_ValueType<Type>::type)>>
		{
			static std::function<std::shared_ptr<SQLType>(Object&)> call(std::function<Type&(Object&)> access)
			{
				return std::function<std::shared_ptr<SQLType>(Object&)>([access](auto& obj) {
					return SQLType::Create(access(obj));
				});
			}
		};
		
		
		
		
		template <class Type>
		using ToSQL_t = std::function<SQLType_ptr(Type&)>;
		
		template <class Type>
		using FromSQL_t = std::function<Type(SQLType_ptr, SQLSystem*, bool)>;
		
		template <class Object>
		using SetSQL_t = std::function<void(Object&, SQLType_ptr, SQLSystem*, bool)>;
		
		
		template <class Type, class = void>
		struct SQLTypeFromType
		{
			static ValueType call(ToSQL_t<Type>& toSQL, FromSQL_t<Type>& fromSQL)
			{
				return Null;
			}
		};
		
		
		
		template <class Type>
		struct SQLTypeFromType<Type, Types::void_t<decltype(SQL_ValueType<Type>::type)>>
		{
			static ValueType call(ToSQL_t<Type>& toSQL, FromSQL_t<Type>& fromSQL)
			{
				toSQL = [](auto& obj) {
					return SQLType::Create(obj);
				};
				typedef typename C_ValueType<SQL_ValueType<Type>::type>::type SQLType_Value_Type;
				fromSQL = [](auto ptr, auto sys, auto includeReferenced)
				{
					return (std::static_pointer_cast<SQLType_Value<SQLType_Value_Type>>(ptr))->template get<Type>();
				};
				return SQL_ValueType<Type>::type;
			}
		};
		
		
	}
}
}