#pragma once
#include <memory>
#include <functional>

#include "ORM/SQLModels.h"

namespace QUtils
{
namespace SQL
{
	
	
	class SQLConnection;
	class SQLMinModel;
	template <class Object>
	class SQLModel;
	
	
	class SQLSystem
	{
		private:
		typedef SQLConnection* ConPtr;
		void initDefaultModels();
		protected:
		
		SQLConnection* con;
		SQLModels* models;
		
		public:
		const ConPtr& connection;
		
		SQLSystem(SQLConnection*, bool withDefaultModels);
		
		static std::shared_ptr<SQLSystem> Create(SQLConnection*, bool withDefaultModels = true);
		
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
		
		void buildModels(bool dropIfConflict = false);
		
		template <class Source, class Destination, class F1, class F2>
		void primitiveType(const F1, const F2);
		template <class Source, class Destination, class F1, class F2>
		void primitiveModel(const F1 f1, const F2 f2)
		{
			primitiveModel<Source, Destination, F1, F2>(f1, f2);
		}
		template <class Source, class Destination, class F1, class F2>
		void primitive(const F1 f1, const F2 f2)
		{
			primitiveModel<Source, Destination, F1, F2>(f1, f2);
		}
		
		template <class Source, class Destination>
		void primitiveType(const std::function<Destination(Source)>, const std::function<Source(Destination)>);
		
		template <class Source, class Destination>
		void primitiveModel(const std::function<Destination(Source)> a, const std::function<Source(Destination)> b)
		{
			primitiveType(a, b);
		}
		template <class Source, class Destination>
		void primitive(const std::function<Destination(Source)> a, const std::function<Source(Destination)> b)
		{
			primitiveType(a, b);
		}
		
		template <class Source, class Destination>
		void primitiveType();
		template <class Source, class Destination>
		void primitiveModel()
		{
			primitiveType<Source, Destination>();
		}
		template <class Source, class Destination>
		void primitive()
		{
			primitiveType<Source, Destination>();
		}
		
		template <class Object>
		void checkIn(Object&, bool includeReferenced = true);
		
		template <class Object>
		void refresh(Object&, bool includeReferenced = true);
		
	};
}
}