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
	
	std::shared_ptr<Token> Symbol::clone() const
	{
		return std::make_shared<Symbol>(symbol);
	}
	
	 std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Symbol::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	return m;
	 }
}
}
}