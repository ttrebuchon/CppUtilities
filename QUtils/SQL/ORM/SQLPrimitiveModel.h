#pragma once


namespace QUtils
{
namespace SQL
{
	class SQLPrimitiveModel
	{
		protected:
		ValueType _dbType;
		
		public:
		SQLPrimitiveModel(ValueType t) : _dbType(t) {}
		virtual ~SQLPrimitiveModel() {}
		
		virtual std::type_index type() const = 0;
		virtual std::type_index equivalent() const = 0;
		
		ValueType dbType() const
		{
			return _dbType;
		}
	};
	
	template <class Type>
	class SQLTypePrimitiveModel : public SQLPrimitiveModel
	{
		protected:
		
		public:
		SQLTypePrimitiveModel(ValueType t) : SQLPrimitiveModel(t)
		{
			
		}
		
		virtual ~SQLTypePrimitiveModel() {}
	};
	
	template <class Type, class Equivalent>
	class SQLFullTypePrimitiveModel : public SQLTypePrimitiveModel<Type>
	{
		protected:
		
		std::function<Equivalent(Type)> toEquivalent;
		std::function<Type(Equivalent)> toType;
		
		public:
		SQLFullTypePrimitiveModel(const std::function<Equivalent(Type)> toEquivalent,
		const std::function<Type(Equivalent)> toType) : SQLTypePrimitiveModel<Type>(SQL_ValueType<Equivalent>::type), toEquivalent(toEquivalent), toType(toType)
		{
			
		}
		
		virtual ~SQLFullTypePrimitiveModel() {}
		
		ValueType dbType() const;
		
		virtual std::type_index type() const override
		{
			return std::type_index(typeid(Type));
		}
		
		virtual std::type_index equivalent() const override
		{
			return std::type_index(typeid(Equivalent));
		}
	};
}
}