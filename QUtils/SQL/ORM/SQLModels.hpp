#pragma once

#include "SQLPrimitiveModel.h"
#include "MetaTypeHelpers.h"
#include "../Errors.h"

namespace QUtils
{
namespace SQL
{
	namespace Helpers
	{
		template <class T>
		struct IsPtrType
		{
			constexpr static const bool value = false;
			typedef T type;
		};
		
		template <class T>
		struct IsPtrType<T*>
		{
			constexpr static const bool value = true;
			typedef T type;
		};
		
		template <class T>
		struct TryDeRef
		{
			constexpr static T& call(T& t)
			{
				return t;
			}
		};
		
		template <class T>
		struct TryDeRef<T*>
		{
			constexpr static T& call(T*& t)
			{
				return *t;
			}
		};
		
		template <class T>
		struct TryCreatePtr
		{
			constexpr static T call(T&& t)
			{
				return t;
			}
		};
		
		template <class T>
		struct TryCreatePtr<T*>
		{
			constexpr static T* call(T&& t)
			{
				return new T(t);
			}
		};
	}
	
	
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
		auto ptr = models[tIndex];
		return (SQLModel<Object>*)ptr;
	}
	
	
	template <class Type>
	ValueType SQLModels::getSQLType(std::function<SQLType_ptr(Type&)>& toSQL, std::function<Type(SQLType_ptr, SQLSystem*, bool)>& toType)
	{
		auto vType = Helpers::SQLTypeFromType<Type>::call(toSQL, toType);
		if (vType != Null)
		{
			return vType;
		}

		std::type_index tIndex(typeid(Type));
		
		if (primitiveModels.count(tIndex) > 0)
		{
			auto pModel = (SQLPrimitiveModel<Type>*)primitiveModels.at(tIndex);
			toSQL = pModel->convert();
			toType = pModel->convertFrom();
			if (!toSQL || !toType)
			{
				throw SQLModelConfigException()
					.Line(__LINE__)
					.File(__FILE__)
					.Function(__func__)
					.Msg(std::string("Error with primitive model '") + tIndex.name() + "' conversion lambda(s)");
			}
			return pModel->dbType();
		}
		
		
		if (models.count(tIndex) > 0)
		{
			auto model = (SQLModel<Type>*)models.at(tIndex);
			if (model->idType == Null)
			{
				model->initModel(this);
			}
			
			auto idEnt = model->idEntity();
			
			if (idEnt == NULL)
			{
				std::cerr << "idEnt is NULL!!!\n";
				throw NotImp();
			}
			
			toSQL = idEnt->serialize;
			
			std::function<void(Type&, SQLType_ptr, SQLSystem*, bool)> idEntFrom = idEnt->deserialize;
			//toType = idEnt->deserialize;
			toType = std::function<Type(SQLType_ptr, SQLSystem*, bool)>([idEntFrom](auto val, auto sys, auto includeReferenced) -> Type
			{
				//TODO
				Type t;
				idEntFrom(t, val, sys, includeReferenced);
				return t;
				throw NotImp();
			});
			
			return model->idType;
			
			throw NotImp();
		}
		
		
		
		typedef typename Helpers::IsPtrType<Type>::type NonPtr_t;
		std::type_index nonPtrIndex(typeid(NonPtr_t));
		
		std::function<SQLType_ptr(NonPtr_t&)> toNonPtrSQL;
		std::function<NonPtr_t(SQLType_ptr, SQLSystem*, bool)> toNonPtrType;
		
		
		if (Helpers::IsPtrType<Type>::value)
		{
		
		auto ret = getSQLType<NonPtr_t>(toNonPtrSQL, toNonPtrType);
		if (toNonPtrSQL)
		{
		toSQL = [toNonPtrSQL] (auto ptr)
		{
			return toNonPtrSQL(Helpers::TryDeRef<Type>::call(ptr));
		};
		
		toType = [toNonPtrType] (auto sql, auto sys, auto includeReferenced) -> Type
		{
			//TODO
			return Helpers::TryCreatePtr<Type>::call(toNonPtrType(sql, sys, includeReferenced));
		};
		}
		
		return ret;
		}
		else
		{
			throw SQLModelConfigException()
				.Line(__LINE__)
				.File(__FILE__)
				.Function(__func__)
				.Msg(
					std::string("Unable to find model for '") + tIndex.name() + "'"
				);
		}
		
		
		
	}
}
}