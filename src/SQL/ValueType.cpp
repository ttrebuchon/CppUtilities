#include <QUtils/SQL/ValueType.h>

namespace QUtils
{
namespace SQL
{
	namespace Internal
	{
		std::map<std::string, ValueType> reverseMap(const std::map<ValueType, std::string>& mappings)
		{
			std::map<std::string, ValueType> map;
			for (auto pair : mappings)
			{
				if (map.count(pair.second) <= 0)
				{
					map[pair.second] = pair.first;
				}
				
			}
			return map;
		}
		
		std::map<ValueType, std::string> ValueType_String_Mappings =
		{
			{ Text, "TEXT" },
			{ Integer, "INTEGER"},
			{ Integer64, "INTEGER" },
			{ Double, "DOUBLE" },
			{ Null, "NULL" },
			{ Blob, "BLOB" }
		};
		
		std::map<std::string, ValueType> String_ValueType_Mappings =
		{
			{ "TEXT", Text },
			{ "INTEGER", Integer },
			{ "INT", Integer },
			{ "DOUBLE", Double },
			{ "NULL", Null },
			{ "BLOB", Blob }
		};
	}
	
	
	template <>
	constexpr bool SQL_Primitive<std::string>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<int>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<long>()
	{
		return true;
	}
	
	template <>
	constexpr bool SQL_Primitive<double>()
	{
		return true;
	}
	
	#ifdef DEBUG
}
}
#include <QUtils/SQL/Errors.h>
namespace QUtils
{
namespace SQL
{
	#endif
	
	ValueType SQL_ParseType(const std::string type)
	{
		if (Internal::String_ValueType_Mappings.count(type) > 0)
		{
			return Internal::String_ValueType_Mappings.at(type);
		}
		std::string str = type;
		
		for (int i = 0; i < str.length(); ++i)
		{
			str[i] = std::toupper(str[i]);
		}
		#ifdef DEBUG
		try
		{
			#endif
		
		return Internal::String_ValueType_Mappings.at(str);
		#ifdef DEBUG
		}
		catch (std::exception&)
		{
			throw SQLErrorException().Msg("Could not find ValueType for " + str).File(__FILE__).Line(__LINE__);
		}
		#endif
	}
	
	std::string to_string(const ValueType t)
	{
		#ifdef DEBUG
		try
		{
		#endif
		return Internal::ValueType_String_Mappings.at(t);
		#ifdef DEBUG
		}
		catch (std::exception& ex)
		{
			throw SQLErrorException(std::current_exception()).Line(__LINE__).File(__FILE__).Msg("Could not find string name for ValueType " + std::to_string((int)t));
		}
		#endif
		
	}
	
	
}
}