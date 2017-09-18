#pragma once
#include <memory>
#include <functional>

#include "../SQLTableBuilder.h"
#include "SQLType.h"
#include "MetaTypeHelpers.h"

namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModelBuilder;
	
	class SQLModels;
	class SQLSystem;
	class SQLQuery;
	
	template <class>
	class SQLEntity;
	
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
		
		std::function<void(Object&, SQLQuery*, SQLSystem*, bool)> loader;
		
		std::vector<std::shared_ptr<SQLEntity<Object>>> entities;
		std::shared_ptr<SQLEntity<Object>> idEnt;
		
		std::function<std::unordered_map<std::string, SQLType_ptr>(Object&)> serializer;
		
		Helpers::ToSQL_t<Object&> _idRetriever;
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		
		SQLModel() : SQLMinModel(), loader(), serializer(), idRetriever(_idRetriever)
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLModel() {}
		
		
		void save(SQLSystem*, Object&, bool includeReferenced = true);
		void load(SQLSystem*, Object&, bool includeReferenced = true);
		
		const Helpers::ToSQL_t<Object&>& idRetriever;
		
		inline std::shared_ptr<const SQLEntity<Object>> idEntity() const
		{ return idEnt; }
		
		friend class SQLModels;
	};
}
}