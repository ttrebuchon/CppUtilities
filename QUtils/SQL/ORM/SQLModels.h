#pragma once
#include <typeindex>
#include <unordered_map>

#include "../ValueType.h"

namespace QUtils
{
namespace SQL
{
	
	
	
	template <class Object>
	class SQLModel;
	
	class SQLSystem;
	class SQLModels;
	class SQLPrimitiveModel;
	
	namespace Internal
	{
		struct ModelContainer
		{
			virtual void create(SQLModels*) = 0;
			
			virtual ValueType idType() const = 0;
		};
		
		template <class Object>
		struct TypedModelContainer : public ModelContainer
		{
			SQLModel<Object>* model;
			
			virtual void create(SQLModels* models) override;
			
			virtual ValueType idType() const override;
		};
	}
	
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
	
	class SQLModels
	{
		private:
		std::unordered_map<std::type_index, Internal::ModelContainer*> models;
		
		std::unordered_map<std::type_index, SQLPrimitiveModel*> primitiveModels;
		
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
	};
	
	
	namespace Internal
	{
		template <class Object>
		void TypedModelContainer<Object>::create(SQLModels* models)
		{
			model->registerModel(models);
			//models->add(this->model);
		}
		
		template <class Object>
		ValueType TypedModelContainer<Object>::idType() const
		{
			return model->idType;
		}
	}
}
}