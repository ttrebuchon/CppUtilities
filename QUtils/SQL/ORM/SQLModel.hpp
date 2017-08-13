#pragma once

#include "SQLModels.h"
#include "SQLModels.hpp"
#include "../Errors.h"
#include "../SQLConnection.h"
#include "../SQLQuery.h"
#include "SQLType.h"

#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Exception/NullPointer.h>
#include <iostream>

namespace QUtils
{
namespace SQL
{
	template <class Object>
	SQLTableBuilder SQLModel<Object>::initModel(SQLModels* models)
	{
		
		if (this->idType != Null)
		{
			return this->tableBuilder;
		}
		SQLModelBuilder<Object> builder(models);
		builder.tablename(this->modelName());
		this->buildModel(builder);
		
		if (builder.idEntity() == NULL)
		{
			throw SQLModelConfigException().Msg("Model does not indicate any sort of identifier");
		}
		
		builder.resolveTypes(models);
		
		
		this->idType = builder.idEntity()->dbType;
		
		std::string tableName = builder.getTableName();
		
		this->tableBuilder = builder.buildTableDec();
		this->tableBuilder.name = tableName;
		
		std::vector<std::tuple<std::string, Helpers::ToSQL_t<Object>>> serializers;
		
		serializers.emplace_back(builder.idEntity()->name(), builder.idEntity()->serialize);
		
		for (auto ent : builder.entities)
		{
			serializers.emplace_back(ent->name(), ent->serialize);
		}
		
		
		
		
		this->serializer = [serializers](auto& obj)
		{
			std::unordered_map<std::string, SQLType_ptr> values;
			for (auto& serial : serializers)
			{
				values[std::get<0>(serial)] = std::get<1>(serial)(obj);
			}
			return values;
		};
		
		
		return this->tableBuilder;
	}
	
	template <class Object>
	void SQLModel<Object>::save(SQLSystem* sys, Object& obj, bool includeReferenced)
	{
		auto values = this->serializer(obj);
		std::string PK_Name = "";
		for (auto col : tableBuilder.columns)
		{
			if (col.PK)
			{
				PK_Name = col.name;
				break;
			}
		}
		if (PK_Name == "")
		{
			throw SQLModelConfigException().Line(__LINE__).File(__FILE__).Msg("Could not find primary key column in table builder");
		}
		
		bool exists = false;
		
		auto q = sys->connection->query("SELECT COUNT(*) FROM [" + tableBuilder.name + "] WHERE [" + PK_Name + "]=" + values.at(PK_Name)->to_string() + ";");
		while (q->next())
		{
			exists = (q->template column<int>(0)) > 0;
		}
		delete q;
		
		if (!exists)
		{
			throw NotImp();
		}
		
		
		std::string query = "UPDATE [" + tableBuilder.name + "] SET";
		
		bool first = true;
		for (auto val : values)
		{
			if (!first)
			{
				query += ",";
			}
			query += " [" + val.first + "]=@" + val.first;
			first = false;
		}
		//query += " WHERE " + idEnt
		std::cerr << "Query: " << query << "\n";
		q = sys->connection->query(query);
		std::cerr << q->statement() << "\n";
		/*
		for (auto val : values)
		{
			if (!val.second)
			{
				throw NullPtrEx();
			}
			throw NotImp();
			val.second->bind("@" + val.first, q);
		}*/
		std::cerr << q->statement() << "\n";
		while (q->next()) ;
		
		delete q;
		throw NotImp();
	}
	
	template <class Object>
	void SQLModel<Object>::load(SQLSystem* sys, Object& obj, bool includeReferenced)
	{
		throw NotImp();
	}
}
}