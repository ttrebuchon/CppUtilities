#include <QUtils/English/Analysis/Number.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Number::Number(const std::string num) : Token(), num(num), n(0)
	{
		try
		{
			n = std::stod(num);
		}
		catch (...)
		{
			
		}
	}
	
	std::string Number::text() const
	{
		return num;
	}
	
	std::shared_ptr<Token> Number::clone() const
	{
		return std::make_shared<Number>(num);
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Number::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	return m;
	 }
}
}
}