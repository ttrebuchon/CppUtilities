#pragma once

#include "SQLEntity.h"

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
	};
}
}