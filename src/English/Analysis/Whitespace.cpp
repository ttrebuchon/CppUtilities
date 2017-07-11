#include <QUtils/English/Analysis/Whitespace.h>
#include <string>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Whitespace::Whitespace(const std::string space) : Token(), space(space)
	{
		
	}
	
	std::string Whitespace::text() const
	{
		return space;
	}
	
	std::shared_ptr<Token> Whitespace::clone() const
	{
		return std::make_shared<Whitespace>(space);
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Whitespace::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	return m;
	 }
}
}
}