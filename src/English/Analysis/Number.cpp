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
}
}
}