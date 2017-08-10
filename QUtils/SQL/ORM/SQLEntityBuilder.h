#pragma once

#include "SQLEntity.h"


namespace QUtils
{
namespace SQL
{
	template <class Object, class Type>
	class SQLEntityBuilder : public SQLFullTypeEntity<Object, Type>
	{
		private:
		
		protected:
		
		public:
		
		SQLEntityBuilder(const std::string name, const std::function<Type&(Object&)> accessor) : SQLFullTypeEntity<Object, Type>(name, accessor)
		{
			
		}
		
		SQLEntityBuilder<Object, Type>& notNull(bool value = true)
		{
			this->_notNull = value;
			return *this;
		}
		
		SQLEntityBuilder<Object, Type>& name(const std::string name)
		{
			this->_name = name;
			return *this;
		}
		
		SQLEntityBuilder<Object, Type>& unique(const bool value = true)
		{
			this->_unique = value;
			return *this;
		}
	};
}
}