#pragma once

#include "ORM/SQLModels.hpp"

#include "Errors.h"

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace SQL
{
	template <class Source, class Destination, class F1, class F2>
	void SQLSystem::primitiveType(const F1 f1, const F2 f2)
	{
		primitiveType(std::function<Destination(Source)>(f1), std::function<Source(Destination)>(f2));
	}
	
	template <class Source, class Destination>
	void SQLSystem::primitiveType(const std::function<Destination(Source)> f1, const std::function<Source(Destination)> f2)
	{
		models->addPrimitive(f1, f2);
	}
	
	template <class Source, class Destination>
	void SQLSystem::primitiveType()
	{
		primitiveType<Source, Destination>(
		[](Source obj) {
			return static_cast<Destination>(obj);
		},
		[](Destination val)
		{
			return static_cast<Source>(val);
		});
	}
	
	
	
	
	template <class Object>
	void SQLSystem::checkIn(const Object& obj, bool includeReferenced)
	{
		auto model = models->getModel<Object>();
		if (model == NULL)
		{
			throw SQLModelConfigException().Msg("Could not find model").Function(__func__);
		}
		model->save(this, obj, includeReferenced);
	}
}
}