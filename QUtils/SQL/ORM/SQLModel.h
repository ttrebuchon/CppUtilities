#pragma once
#include <memory>

#include "../SQLTableBuilder.h"

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
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		
		SQLModel() : SQLMinModel(), loader()
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLModel() {}
		
		
		void save(SQLSystem*, const Object&, bool includeReferenced = true);
		void load(SQLSystem*, Object&, bool includeReferenced = true);
		
		friend class SQLModels;
	};
}
}