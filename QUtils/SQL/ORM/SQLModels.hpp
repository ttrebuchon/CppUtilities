#pragma once

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
			Internal::TypedModelContainer<Object>* ptr;
			models[index] = ptr = new Internal::TypedModelContainer<Object>();
			ptr->model = new Model();
		}
	}
}
}