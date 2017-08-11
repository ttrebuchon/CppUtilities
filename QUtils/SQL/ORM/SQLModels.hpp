#pragma once

#include "SQLPrimitiveModel.h"

namespace QUtils
{
namespace SQL
{
	template <class Model, class Object>
	void SQLModels::add()
	{
		std::type_index index(typeid(Object));
		if (models.count(index) <= 0)
		{
			models[index] = new Model();
		}
	}
	
	
	template <class Type, class Equivalent>
	void SQLModels::addPrimitive(const std::function<Equivalent(Type)> toEquivalent, const std::function<Type(Equivalent)> toType)
	{
		std::type_index tIndex(typeid(Type));
		if (primitiveModels.count(tIndex) > 0)
		{
			if (primitiveModels[tIndex] != NULL)
			{
				delete primitiveModels[tIndex];
			}
		}
		primitiveModels[tIndex] = new SQLFullTypePrimitiveModel<Type, Equivalent>(toEquivalent, toType);
	}
}
}