#pragma once

#include "SQLTableBuilder.h"

namespace QUtils
{
namespace SQL
{
	namespace Internal
	{
		template <
			class Object,
			class ID, //Object id
			class... Members //Model Members
		>
		class SQLModelConfig
		{
			
		};
		
		
		template <class T>
		struct RemoveRef
		{
			typedef T type;
		};
		
		template <class T>
		struct RemoveRef<T&>
		{
			typedef T type;
		};
		
		
		template <class F, class Object>
		using Result_t = typename RemoveRef<decltype(std::declval<F>()(std::declval<Object&>()))>::type;
	}
	
	template <class Object>
	class SQLTypeEntity;
	
	
	template <class Object, class Type>
	class SQLEntityBuilder;
	
	template <class Object>
	class SQLModelBuilder
	{
		private:
		std::string currentCol;
		
		protected:
		std::string name;
		std::vector<std::shared_ptr<SQLTypeEntity<Object>>> entities;
		std::shared_ptr<SQLTypeEntity<Object>> idEnt;
		
		public:
		
		template <class F>
		SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& property(F);
		template <class F>
		SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& property(const std::string name, F);
		
		template <class F>
		SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& id(F);
		template <class F>
		SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& id(const std::string name, F);
		
		void tablename(const std::string name)
		{
			this->name = name;
		}
		
		std::string getTableName() const
		{
			return name;
		}
		
		std::shared_ptr<const SQLTypeEntity<Object>> idEntity() const
		{
			return idEnt;
		}
		
		void resolveTypes(SQLModels*);
		SQLTableBuilder buildTableDec();
		
		template <class>
		friend class SQLTypeModel;
	};
}
}