#pragma once

#include "../Errors.h"
#include "SQLModelBuilder.h"
#include "SQLEntity.h"
#include "SQLModelBuilder.hpp"
#include "../SQLConnection.h"

#include <iostream>

#include <QUtils/Exception/NullPointer.h>


namespace QUtils
{
namespace SQL
{
	
	
	
	template <class Object>
	SQLTableBuilder SQLTypeModel<Object>::registerModel(SQLModels* models)
	{
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
		
		
		
		
		
		return this->tableBuilder;
	}
}
}