#pragma once
#include "../ValueType.h"

namespace QUtils
{
namespace SQL
{
	template <class Object, class Type>
	ValueType SQLFullTypeEntity<Object, Type>::getValueType(SQLModels* models)
	{
		ValueType type = SQL_TryValueType<Type>::type;
		if (type != Null)
		{
			this->_dbType = type;
			return type;
		}
		
		this->_dbType =  models->getSQLType(std::type_index(typeid(Type)));
		
		//auto converter = models->get
		
		
		return this->_dbType;
	}
}
}