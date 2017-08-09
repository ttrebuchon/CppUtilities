#pragma once
#include <memory>


namespace QUtils
{
namespace SQL
{
	template <class Object>
	class SQLModelBuilder;
	
	template <class Object>
	class SQLModel
	{
		private:
		
		std::shared_ptr<SQLModel<Object>>& GetEntity();
		
		void registerModel(SQLModels*);
		
		protected:
		virtual void buildModel(SQLModelBuilder<Object>&) = 0;
		virtual std::string modelName() const = 0;
		SQLModel()
		{
		}
		
		public:
		typedef Object type;
		virtual ~SQLModel() {}
		
		//void add(
		
		ValueType idType;
		
		template <class>
		friend class Internal::TypedModelContainer;
	};
}
}