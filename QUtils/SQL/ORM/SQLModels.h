#pragma once
#include <typeindex>
#include <unordered_map>

#include "../ValueType.h"
#include "SQLModel.h"
#include "SQLType.h"

namespace QUtils
{
namespace SQL
{
	namespace Helpers
	{
		template <class Model>
		struct ModelExtractor
		{
			
			private:
			template <class T>
			static T func(SQLModel<T>&);
			
			public:
			typedef decltype(func(std::declval<Model&>())) type;
		};
		
	}
	
	
	
	
	
	
	
	class SQLSystem;
	class SQLMinModel;
	class SQLMinPrimitiveModel;
	
	class SQLModels
	{
		private:
		std::unordered_map<std::type_index, SQLMinModel*> models;
		
		std::unordered_map<std::type_index, SQLMinPrimitiveModel*> primitiveModels;
		
		public:
		
		template <class Model>
		void add()
		{
			this->add<Model, typename Helpers::ModelExtractor<Model>::type>();
		}
		
		template <class Model, class Object>
		void add();
		template <class Type, class Equivalent>
		void addPrimitive(const std::function<Equivalent(Type)>, const std::function<Type(Equivalent)>);
		
		void build(SQLSystem*);
		
		ValueType getSQLType(std::type_index);
		
		template <class Type>
		ValueType getSQLType(std::function<SQLType_ptr(Type&)>&, std::function<Type(SQLType_ptr, SQLSystem*, bool)>&);
		
		template <class Object>
		SQLModel<Object>* getModel();
	};
}
}