#pragma once
#include <functional>


namespace QUtils
{
namespace SQL
{
	class SQLSystem;
	
	class SQLEntity
	{
		protected:
		std::string _name;
		bool _notNull;
		bool _unique;
		ValueType _dbType;
		
		SQLEntity(const std::string name) : _name(name), _notNull(false), _unique(false), _dbType(Null), dbType(_dbType)
		{
			
		}
		
		public:
		
		virtual ValueType getValueType(SQLModels*) = 0;
		
		const ValueType& dbType;
		
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
	struct SQLTypeEntity : public SQLEntity
	{
		protected:
		
		std::function<std::shared_ptr<SQLType>(const Object&)> getter;
		std::function<void(Object&, std::shared_ptr<SQLType>)> setter;
		
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
		
		virtual ValueType getValueType(SQLModels*) override;
	};
	
	
}
}