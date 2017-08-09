#pragma once
#include <memory>

#include "ORM/SQLModels.h"

namespace QUtils
{
namespace SQL
{
	
	
	class SQLConnection;
	template <class Object>
	class SQLModel;
	
	
	class SQLSystem
	{
		private:
		typedef SQLConnection* ConPtr;
		protected:
		
		SQLConnection* con;
		SQLModels* models;
		
		public:
		const ConPtr& connection;
		
		SQLSystem(SQLConnection*);
		
		static std::shared_ptr<SQLSystem> Create(SQLConnection*);
		
		template <class Model>
		void model()
		{
			models->add<Model>();
		}
		
		template <class Object>
		void model(SQLModel<Object>* model)
		{
			models->add(model);
		}
		
		void buildModels();
		
		template <class Source, class Destination, class F1, class F2>
		void primitiveType(const F1, const F2);
		
		template <class Source, class Destination>
		void primitiveType(const std::function<Destination(Source)>, const std::function<Source(Destination)>);
		
		template <class Object>
		void checkIn(const Object&);
		
	};
}
}