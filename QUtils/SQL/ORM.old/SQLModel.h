#pragma once
#include <memory>

#include "../SQLTableBuilder.h"

namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModelBuilder;
	
	class SQLModel
	{
		protected:
		SQLTableBuilder tableBuilder;
		
		virtual SQLTableBuilder registerModel(SQLModels*) = 0;
		
		virtual std::string modelName() const = 0;
		public:
		SQLModel() : tableBuilder(), idType(Null) {}
		virtual ~SQLModel() {}
		
		ValueType idType;
		
		friend class SQLModels;
	};
	
	template <class Object>
	class SQLTypeModel : public SQLModel
	{
		private:
		
		std::shared_ptr<SQLTypeModel<Object>>& GetEntity();
		
		SQLTableBuilder registerModel(SQLModels*) override;
		
		//std::function<std::vector<std::tuple<std::string, std::shared_ptr<SQLType>>>(const Object&)> retriever;
		
		//std::function<void(std::vector<std::tuple<std::string, std::shared_ptr<SQLType>>>, Object&)> setter;
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		
		SQLTypeModel() : SQLModel()
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLTypeModel() {}
		
		//void add(
		
		void save(SQLSystem*, const Object&);
		void load(SQLSystem*, Object&);
		
		friend class SQLModels;
	};
}
}