#pragma once
#include <functional>


namespace QUtils
{
namespace SQL
{
	template <class Object>
	struct SQLEntity
	{
		private:
		
		protected:
		std::string _name;
		bool _notNull;
		bool _unique;
		
		public:
		
		SQLEntity(const std::string name) : _name(name)
		{
			
		}
		
		virtual ValueType getValueType(SQLModels*) const = 0;
	};
	
	
	template <class Object, class Type>
	struct SQLEntityType : public SQLEntity<Object>
	{
		private:
		std::function<Type&(Object&)> entity;
		public:
		
		SQLEntityType(const std::string name, const std::function<Type&(Object&)> accessor) : SQLEntity<Object>(name), entity(accessor)
		{
			
		}
		
		virtual ValueType getValueType(SQLModels*) const override;
	};
	
	
}
}