#pragma once

#include <QUtils/Exception/Exception.h>


namespace QUtils
{
namespace SQL
{
	QUTILS_CUSTOM_EXCEPTION(SQLModelConfigException,);
	
	
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
	}
}
}