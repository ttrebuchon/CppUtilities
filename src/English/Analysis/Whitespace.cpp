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
}
}
}