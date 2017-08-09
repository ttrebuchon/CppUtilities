#pragma once


namespace QUtils
{
namespace SQL
{
	template <class Type, class Destination>
	class SQLPrimitiveModel
	{
		protected:
		ValueType _dbType;
		std::function<
		
		public:
		ValueType dbType() const;
	};
}
}