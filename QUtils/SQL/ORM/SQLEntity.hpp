#pragma once
#include "../ValueType.h"

namespace QUtils
{
namespace SQL
{
	template <class Object, class Type>
	ValueType SQLFullTypeEntity<Object, Type>::getValueType(SQLModels* models) const
	{
		ValueType type = SQL_TryValueType<Type>::type;
		if (type != Null)
		{
			return type;
		}
		
		return models->getSQLType(std::type_index(typeid(Type)));
	}
}
}