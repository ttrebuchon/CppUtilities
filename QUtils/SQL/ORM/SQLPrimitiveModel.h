#pragma once

#include "SQLType.h"
#include <QUtils/Exception/NullPointer.h>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace SQL
{
	class SQLMinPrimitiveModel
	{
		protected:
		ValueType _dbType;
		
		public:
		SQLMinPrimitiveModel(ValueType t) : _dbType(t) {}
		virtual ~SQLMinPrimitiveModel() {}
		
		virtual std::type_index type() const = 0;
		virtual std::type_index equivalent() const = 0;
		
		virtual ValueType dbType() const = 0;
	};
	
	template <class Type>
	class SQLPrimitiveModel : public SQLMinPrimitiveModel
	{
		protected:
		
		public:
		SQLPrimitiveModel(ValueType t) : SQLMinPrimitiveModel(t)
		{
			
		}
		
		virtual ~SQLPrimitiveModel() {}
		
		virtual std::function<std::shared_ptr<SQLType>(Type)> convert() const = 0;
		
		virtual std::function<Type(std::shared_ptr<SQLType>)> convertFrom() const = 0;
	};
	
	template <class Type, class Equivalent>
	class SQLFullPrimitiveModel : public SQLPrimitiveModel<Type>
	{
		protected:
		
		std::function<Equivalent(Type)> toEquivalent;
		std::function<Type(Equivalent)> toType;
		
		public:
		SQLFullPrimitiveModel(const std::function<Equivalent(Type)> toEquivalent,
		const std::function<Type(Equivalent)> toType) : SQLPrimitiveModel<Type>(SQL_ValueType<Equivalent>::type), toEquivalent(toEquivalent), toType(toType)
		{
			
		}
		
		virtual ~SQLFullPrimitiveModel() {}
		
		virtual std::type_index type() const override
		{
			return std::type_index(typeid(Type));
		}
		
		virtual std::type_index equivalent() const override
		{
			return std::type_index(typeid(Equivalent));
		}
		
		
		virtual std::function<std::shared_ptr<SQLType>(Type)> convert() const override
		{
			auto f = toEquivalent;
			return std::function<std::shared_ptr<SQLType>(Type)>([f](Type t) {
				return SQLType::Create(f(t));
			});
		}
		
		virtual std::function<Type(std::shared_ptr<SQLType>)> convertFrom() const override
		{
			auto dbT = dbType();
			auto f = toType;
			return std::function<Type(std::shared_ptr<SQLType>)>([f, dbT](std::shared_ptr<SQLType> val) {
				if (val == NULL)
				{
					throw NullPointerException();
				}
				
				if (val->type() != dbT)
				{
					//TODO
					throw NotImp().Line(__LINE__);
				}
				auto ptr = (SQLType_Value<Equivalent>*)val.get();
				
				return f(ptr->get());
			});
		}
		
		virtual ValueType dbType() const override
		{
			return SQL_ValueType<Equivalent>::type;
		}
	};
}
}