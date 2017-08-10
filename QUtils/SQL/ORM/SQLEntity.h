#pragma once
#include <functional>


namespace QUtils
{
namespace SQL
{
	class SQLEntity
	{
		protected:
		std::string _name;
		bool _notNull;
		bool _unique;
		
		SQLEntity(const std::string name) : _name(name), _notNull(false), _unique(false)
		{
			
		}
		
		public:
		
		virtual ValueType getValueType(SQLModels*) const = 0;
	};
	
	
	template <class Object>
	struct SQLTypeEntity : public SQLEntity
	{
		private:
		
		
		
		public:
		
		SQLTypeEntity(const std::string name) : SQLEntity(name)
		{
			
		}
		
		
	};
	
	
	template <class Object, class Type>
	struct SQLFullTypeEntity : public SQLTypeEntity<Object>
	{
		private:
		std::function<Type&(Object&)> entity;
		public:
		
		SQLFullTypeEntity(const std::string name, const std::function<Type&(Object&)> accessor) : SQLTypeEntity<Object>(name), entity(accessor)
		{
			
		}
		
		virtual ValueType getValueType(SQLModels*) const override;
	};
	
	
}
}