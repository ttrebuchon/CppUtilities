#include <QUtils/English/Analysis/CompositeToken.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	CompositeToken::CompositeToken(const std::vector<std::shared_ptr<Token>>& tokens) : Token(), tokens(tokens)
	{
		
	}
	CompositeToken::CompositeToken(const int size) : Token(), tokens(size)
	{
		
	}
	
	CompositeToken::CompositeToken() : CompositeToken(0)
	{
		
	}
	
	std::string CompositeToken::text() const
	{
		std::string str;
		for (auto token : tokens)
		{
			str += token->text();
		}
		return str;
	}
}
}
}