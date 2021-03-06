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
		
		this->entities = builder.entities;
		this->idEnt = builder.idEnt;
		if (idEnt == NULL)
		{
			std::cerr << "Somehow builder.idEnt is null...\n";
		}
		
		builder.resolveTypes(models);
		
		
		this->idType = builder.idEntity()->dbType;
		
		std::string tableName = builder.getTableName();
		
		this->tableBuilder = builder.buildTableDec();
		this->tableBuilder.name = tableName;
		
		std::vector<std::tuple<std::string, Helpers::ToSQL_t<Object>>> serializers;


		if (!builder.idEntity()->serialize)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("ID entity '") + builder.idEntity()->name() + "' does not have valid serialize lambda, model is for type: '" + std::type_index(typeid(Object)).name() + 
					"' and entity type is '" + builder.idEntity()->typeIndex().name());
		}
		serializers.emplace_back(builder.idEntity()->name(), builder.idEntity()->serialize);
		_idRetriever = builder.idEntity()->serialize;
		
		for (auto ent : builder.entities)
		{
			if (!ent->serialize)
			{
				throw SQLModelConfigException()
					.Function(__func__)
					.File(__FILE__)
					.Line(__LINE__)
					.Msg(std::string("Entity '") + ent->name() + "' does not have valid serialize lambda, model is for type: '" + std::type_index(typeid(Object)).name() + 
						"' and entity type is '" + ent->typeIndex().name());
			}
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
		
		
		std::vector<std::tuple<std::string, Helpers::SetSQL_t<Object>>> deserializers;
		
		
		for (auto ent : builder.entities)
		{
			if (!ent->deserialize)
			{
				throw SQLModelConfigException()
					.Function(__func__)
					.File(__FILE__)
					.Line(__LINE__)
					.Msg(std::string("Entity '") + ent->name() + "' does not have valid deserialize lambda, model is for type: '" + std::type_index(typeid(Object)).name() + 
						"' and entity type is '" + ent->typeIndex().name());
			}
			deserializers.emplace_back(ent->name(), ent->deserialize);
		}
		
		
		this->loader = [deserializers](Object& obj, SQLQuery* q, SQLSystem* sys, bool includeReferenced) -> void
		{
			
			for (auto& deserial : deserializers)
			{
				std::get<1>(deserial)(obj, SQLType::Create(q, std::get<0>(deserial)), sys, includeReferenced);
			}
		};
		
		
		return this->tableBuilder;
	}
	
	template <class Object>
	void SQLModel<Object>::save(SQLSystem* sys, Object& obj, bool includeReferenced)
	{
		std::string query;
		if (!this->serializer)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("Model does not have valid serializer lambda during save() function, model is for type: '") + std::type_index(typeid(Object)).name() + "'");
		}
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
		
		auto q = sys->connection->query("SELECT COUNT(*) FROM [" + tableBuilder.name + "] WHERE [" + PK_Name + "]=" + to_string(*values.at(PK_Name)) + ";");
		while (q->next())
		{
			exists = (q->template column<int>(0)) > 0;
		}
		delete q;
		
		if (!exists)
		{
			query = "";
			std::string insVals = "";
			for (auto val : values)
			{
				query += ", " + val.first;
				insVals += ", @" + val.first;
			}

			query = "INSERT INTO [" + tableBuilder.name + "] (" + query.substr(2) + ") VALUES (" + insVals.substr(2) + ");";
		}
		else
		{
		
		
		query = "UPDATE [" + tableBuilder.name + "] SET";
		
		bool first = true;
		for (auto val : values)
		{
			if (val.first != PK_Name)
			{
			if (!first)
			{
				query += ",";
			}
			query += " [" + val.first + "]=@" + val.first;
			first = false;
			}
		}
		
		query += " WHERE [" + PK_Name + "]=@" + PK_Name + ";";
		}
		q = sys->connection->query(query);
		
		for (auto val : values)
		{
			if (!val.second)
			{
				throw NullPtrEx();
			}
			val.second->bind("@" + val.first, q);
		}
		while (q->next()) ;
		
		delete q;
	}
	
	template <class Object>
	void SQLModel<Object>::load(SQLSystem* sys, Object& obj, bool includeReferenced)
	{
		std::string query;
		if (!this->loader)
		{
			throw SQLModelConfigException()
				.Function(__func__)
				.File(__FILE__)
				.Line(__LINE__)
				.Msg(std::string("Model does not have valid loader lambda during load() function, model is for type: '") + std::type_index(typeid(Object)).name() + "'");
		}
		
		
		
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
		
		auto idVal = idRetriever(obj);
		
		query = "SELECT * FROM [" + tableBuilder.name + "] WHERE [" + PK_Name + "]=@" + PK_Name + ";";
		
		query += " WHERE [" + PK_Name + "]=@" + PK_Name + ";";
		
		auto q = sys->connection->query(query);
		
		
		idVal->bind("@" + PK_Name, q);
		
		if (!q->next())
		{
			std::cerr << "ERR LOADING\n";
			throw NotImp();
		}
		
		this->loader(obj, q, sys, includeReferenced);
		delete q;
	}
}
}