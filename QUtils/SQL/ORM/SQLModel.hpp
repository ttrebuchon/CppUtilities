#pragma once

#include "SQLModels.h"
#include "SQLModels.hpp"
#include "../Errors.h"

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace SQL
{
	template <class Object>
	SQLTableBuilder SQLModel<Object>::initModel(SQLModels* models)
	{
		throw NotImp();
		/*
		if (this->idType != Null)
		{
			return this->tableBuilder;
		}
		SQLModelBuilder<Object> builder;
		//builder.setName(this->modelName());
		this->buildModel(builder);
		
		if (builder.idEntity() == NULL)
		{
			throw SQLModelConfigException().Msg("Model does not indicate any sort of identifier!");
		}
		
		builder.resolveTypes(models);
		
		
		this->idType = builder.idEntity()->dbType;
		//this->idType = builder.idEntity()->getValueType(models);
		std::cerr << "Model: " << this->modelName() << "\nidType: " << this->idType << "\n";
		
		for (auto ent : builder.entities)
		{
			std::cerr << "Entity: " << ent->name() << "\nType: " << ent->dbType << "\n";
		}
		
		std::cerr << "\n";
		
		std::string tableName = builder.getTableName();
		if (tableName == "")
		{
			tableName = this->modelName();
		}
		
		this->tableBuilder = builder.buildTableDec();
		
		
		
		
		
		return this->tableBuilder;*/
		
	}
	
	template <class Object>
	void SQLModel<Object>::save(SQLSystem* sys, const Object& obj, bool includeReferenced)
	{
		throw NotImp();
	}
	
	template <class Object>
	void SQLModel<Object>::load(SQLSystem* sys, Object& obj, bool includeReferenced)
	{
		throw NotImp();
	}
}
}