#pragma once
#include <memory>
#include <functional>

#include "../SQLTableBuilder.h"
#include "SQLType.h"

namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModelBuilder;
	
	class SQLModels;
	class SQLSystem;
	class SQLQuery;
	
	class SQLMinModel
	{
		protected:
		SQLTableBuilder tableBuilder;
		
		virtual SQLTableBuilder initModel(SQLModels*) = 0;
		
		virtual std::string modelName() const = 0;
		public:
		SQLMinModel() : tableBuilder(), idType(Null) {}
		virtual ~SQLMinModel() {}
		
		ValueType idType;
		
		friend class SQLModels;
	};
	
	template <class Object>
	class SQLModel : public SQLMinModel
	{
		private:
		
		std::shared_ptr<SQLModel<Object>>& GetEntity();
		
		SQLTableBuilder initModel(SQLModels*) override;
		
		std::function<void(Object&, SQLQuery*)> loader;
		
		std::function<std::unordered_map<std::string, SQLType_ptr>(Object&)> serializer;
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		
		SQLModel() : SQLMinModel(), loader(), serializer()
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLModel() {}
		
		
		void save(SQLSystem*, Object&, bool includeReferenced = true);
		void load(SQLSystem*, Object&, bool includeReferenced = true);
		
		friend class SQLModels;
	};
}
}