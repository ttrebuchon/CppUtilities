#pragma once
#include <typeindex>
#include <unordered_map>

namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModel;
	
	class SQLSystem;
	class SQLModels;
	
	namespace Internal
	{
		struct ModelContainer
		{
			virtual void create(SQLModels*) = 0;
		};
		
		template <class Object>
		struct TypedModelContainer : public ModelContainer
		{
			SQLModel<Object>* model;
			
			virtual void create(SQLModels* models) override;
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
		
		public:
		
		template <class Model>
		void add()
		{
			this->add<Model, typename Helpers::ModelExtractor<Model>::type>();
		}
		
		template <class Model, class Object>
		void add();
		
		void build(SQLSystem*);
	};
	
	
	namespace Internal
	{
		template <class Object>
		void TypedModelContainer<Object>::create(SQLModels* models)
		{
			model->registerModel(models);
			//models->add(this->model);
		}
	}
}
}