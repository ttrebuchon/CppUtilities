#pragma once

#include "SQLEntityBuilder.h"

namespace QUtils
{
namespace SQL
{
	template <class Object>
	template <class F>
	SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& SQLModelBuilder<Object>::property(F access)
	{
		int index = currentCol.length() - 1;
		auto thisCol = currentCol;
		if (currentCol[index] != 'Z')
		{
			++currentCol[index];
		}
		else
		{
			
			while (index >= 0)
			{
				if (currentCol[index] == 'Z')
				{
					currentCol[index] = 'A';
				}
				else
				{
					++currentCol[index];
					break;
				}
				--index;
			}
			if (index == -1)
			{
				currentCol = "A" + currentCol;
			}
		}
		
		return property(thisCol, access);
		
	}
	
	template <class Object>
	template <class F>
	SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& SQLModelBuilder<Object>::property(const std::string name, F access)
	{
		typedef Internal::Result_t<F, Object> Type;
		auto fAccess = std::function<Type&(Object&)>([access](auto& obj) -> Type& { return access(obj); });
		auto ptr = std::make_shared<SQLEntityBuilder<Object, Type>>(name, fAccess);
		entities.push_back(std::static_pointer_cast<SQLEntity<Object>>(ptr));
		return *ptr;
	}
	
	template <class Object>
	template <class F>
	SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& SQLModelBuilder<Object>::id(F access)
	{
		return id("id", access);
	}
	
	template <class Object>
	template <class F>
	SQLEntityBuilder<Object, Internal::Result_t<F, Object>>& SQLModelBuilder<Object>::id(const std::string name, F access)
	{
		typedef Internal::Result_t<F, Object> Type;
		auto fAccess = std::function<Type&(Object&)>([access](auto& obj) -> Type& { return access(obj); });
		auto ptr = std::make_shared<SQLEntityBuilder<Object, Type>>(name, fAccess);
		idEnt = ptr;
		return *ptr;
	}
	
	template <class Object>
	void SQLModelBuilder<Object>::resolveTypes(SQLModels* models)
	{
		throw NotImp();
	}
	
	
	template <class Object>
	SQLTableBuilder SQLModelBuilder<Object>::buildTableDec()
	{
		/*SQLTableBuilder builder;
		
		auto idEnt = idEntity();
		SQLColumnBuilder idCol;
		idCol.name = idEnt->name();
		idCol.PK = true;
		idCol.type = idEnt->dbType;
		builder.columns.push_back(idCol);
		
		for (auto ent : entities)
		{
			SQLColumnBuilder col;
			col.name = ent->name();
			col.type = ent->dbType;
			col.notNull = ent->notNull();
			col.unique = ent->unique();
			builder.columns.push_back(col);
			
		}
		
		return builder;*/
		throw NotImp();
	}
}
}