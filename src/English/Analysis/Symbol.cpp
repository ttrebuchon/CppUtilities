#include <QUtils/English/Analysis/Symbol.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Symbol::Symbol(const std::string symbol) : Token(), symbol(symbol)
	{
		
	}
	
	std::string Symbol::text() const
	{
		return symbol;
	}
}
}
}