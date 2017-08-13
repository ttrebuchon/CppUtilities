#pragma once

#include "SQLEntityBuilder.h"
#include "SQLModels.h"

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
		
		std::function<SQLType_ptr(Type&)> toSQL;
		std::function<Type(SQLType_ptr)> fromSQL;
		ValueType vType = models->getSQLType<Type>(toSQL, fromSQL);
		std::function<SQLType_ptr(Object&)> serialize([fAccess, toSQL] (Object& obj)
		{
			return toSQL(fAccess(obj));
		});
		
		Helpers::SetSQL_t<Object> deserialize([fAccess, fromSQL] (Object& obj, SQLType_ptr ptr)
		{
			fAccess(obj) = fromSQL(ptr);
		});
		
		ptr->serialize = serialize;
		ptr->deserialize = deserialize;
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
		if (idEnt->dbType == Null)
		{
			idEnt->resolveType(models);
		}
		
		for (auto ent : entities)
		{
			if (ent->dbType == Null)
			{
				ent->resolveType(models);
			}
		}
	}
	
	
	template <class Object>
	SQLTableBuilder SQLModelBuilder<Object>::buildTableDec()
	{
		SQLTableBuilder builder;
		
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
		
		return builder;
	}
}
}