#pragma once

#include <string>
#include <QUtils/Types/Void_t.h>

namespace QUtils
{
namespace SQL
{
	enum ValueType
	{
		Text = 0,
		Integer = 1,
		Integer64 = 2,
		Double = 3,
		Null = 4,
		Blob = 5,
		
	};
	
	template <typename T>
	struct SQL_ValueType
	{ };
	
	template <>
	struct SQL_ValueType<std::string>
	{
		constexpr static ValueType type = Text;
	};
	
	template <>
	struct SQL_ValueType<const char*>
	{
		constexpr static ValueType type = Text;
	};
	
	template <>
	struct SQL_ValueType<int>
	{
		constexpr static ValueType type = Integer;
	};
	
	template <>
	struct SQL_ValueType<long>
	{
		constexpr static ValueType type = Integer64;
	};
	
	template <>
	struct SQL_ValueType<double>
	{
		constexpr static ValueType type = Double;
	};
	
	
	
	
	
	
	template <ValueType T>
	struct C_ValueType
	{ };
	
	template <>
	struct C_ValueType<Text>
	{
		typedef std::string type;
	};
	
	template <>
	struct C_ValueType<Integer>
	{
		typedef int type;
	};
	
	template <>
	struct C_ValueType<Integer64>
	{
		typedef long type;
	};
	
	template <>
	struct C_ValueType<Double>
	{
		typedef double type;
	};
	
	
	template <typename T>
	constexpr bool SQL_Primitive()
	{
		return false;
	}
	
	
	namespace Helpers
	{
		
	}
	
	template <class Type, class = void>
	struct SQL_ValueTypeExists : std::false_type
	{
		//const bool value;
	};
	
	template <class Type>
	struct SQL_ValueTypeExists<Type, Types::void_t<typename C_ValueType<SQL_ValueType<Type>::type>::type>> : std::true_type
	{
		const ValueType t = SQL_ValueType<Type>::type;
	};
	
	
	
	
	
	
}
}