#pragma once
#include <memory>


namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModelBuilder;
	
	class SQLModel
	{
		protected:
		
		virtual void registerModel(SQLModels*) = 0;
		
		virtual std::string modelName() const = 0;
		public:
		SQLModel() : idType(Null) {}
		virtual ~SQLModel() {}
		
		ValueType idType;
		
		friend class SQLModels;
	};
	
	template <class Object>
	class SQLTypeModel : public SQLModel
	{
		private:
		
		std::shared_ptr<SQLTypeModel<Object>>& GetEntity();
		
		void registerModel(SQLModels*) override;
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		
		SQLTypeModel() : SQLModel()
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLTypeModel() {}
		
		//void add(
		
		
		
		friend class SQLModels;
	};
}
}