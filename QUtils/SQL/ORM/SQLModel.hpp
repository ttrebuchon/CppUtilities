#pragma once

#include "../Errors.h"


namespace QUtils
{
namespace SQL
{
	
	
	
	template <class Object>
	void SQLModel<Object>::registerModel(SQLModels* models)
	{
		SQLModelBuilder<Object> builder;
		//builder.setName(this->modelName());
		this->buildModel(builder);
		
		if (builder.idEntity() == NULL)
		{
			throw SQLModelConfigException().Msg("Model does not indicate any sort of identifier!");
		}
		
		this->idType = builder.idEntity()->getValueType(models);
		
		throw NotImp();
	}
}
}