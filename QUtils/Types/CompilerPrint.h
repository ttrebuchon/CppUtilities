#pragma once
#include <iostream>
#include <QUtils/String/String.h>

namespace QUtils
{
namespace Types
{
	
	
	template <int... N, class ...T>
	std::string PrintTypes()
	{
		String str(__PRETTY_FUNCTION__);
		str = str.substr(str.find("int ...N ="));
		str = str.substr(0, str.find(";", str.find(";")+1));
		str = str
		    .substr(11)
		    .replace("}; T = {", "} : {");
		return str;
	}
	
	template <int... N, class ...T>
	std::ostream& PrintTypes(std::ostream& os)
	{
		return (os << PrintTypes<N..., T...>());
	}
	
	
	
	
	template <class ...T>
	std::string PrintTypes()
	{
		String str(__PRETTY_FUNCTION__);
		str = str.substr(str.find("T ="));
		str = str.substr(4, str.find(";")-4);
		return str;
	}
	
	template <class ...T>
	std::ostream& PrintTypes(std::ostream& os)
	{
		return (os << PrintTypes<T...>());
	}
	
	
	template <class ...T>
	struct Printer
	{
		static std::ostream& print(std::ostream& os)
		{
			return PrintTypes<T...>(os);
		}
		
		static std::string print()
		{
			return PrintTypes<T...>();
		}
	};
}
}