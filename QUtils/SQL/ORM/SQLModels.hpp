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
			auto old = primitiveModels.at(tIndex);
			if (old != NULL)
			{
				
				delete old;
			}
		}
		primitiveModels[tIndex] = new SQLFullPrimitiveModel<Type, Equivalent>(toEquivalent, toType);
	}
	
	template <class Object>
	SQLModel<Object>* SQLModels::getModel()
	{
		std::type_index tIndex(typeid(Object));
		auto ptr = models.at(tIndex);
		return (SQLModel<Object>*)ptr;
	}
}
}