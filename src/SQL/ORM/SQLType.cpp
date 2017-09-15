#include <QUtils/SQL/ORM/SQLType.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace SQL
{
	std::shared_ptr<SQLType> SQLType::Create(const std::string val)
	{
		return std::make_shared<SQLTextType>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const long val)
	{
		return std::make_shared<SQLIntegerType>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const long long val)
	{
		return std::make_shared<SQLInteger64Type>(val);
	}
	
	
	std::shared_ptr<SQLType> SQLType::Create(const double val)
	{
		return std::make_shared<SQLDoubleType>(val);
	}
	
	std::shared_ptr<SQLType> SQLType::Create(SQLQuery* q, const std::string col)
	{
		for (int i = 0; i < q->width(); ++i)
		{
			if (q->columnName(i) == col)
			{
				return Create(q, i);
			}
		}
		throw NotImp();
	}
	
	std::shared_ptr<SQLType> SQLType::Create(SQLQuery* q, const int index)
	{
		auto type = q->columnType(index);
		switch (type)
		{
			case Text:
			return Create(q->column<typename C_ValueType<Text>::type>(index));
					
			case Integer:
			return Create(q->column<typename C_ValueType<Integer>::type>(index));
			
			case Integer64:
			return Create(q->column<typename C_ValueType<Integer64>::type>(index));
					
			case Double:
			return Create(q->column<typename C_ValueType<Double>::type>(index));
					
			case Null:
			return Create(q->column<typename C_ValueType<Text>::type>(index));
					
			case Blob:
			throw NotImp();
			//return Create(q->column<std::string>(index));
					
			default:
			throw NotImp();
			std::cout << "Unknown!";
			break;
		}
	}


	std::string to_string(const SQLType& t)
	{
		return t._to_string();
	}

	std::string to_string(std::string str)
	{
		return str;
	}
}
}