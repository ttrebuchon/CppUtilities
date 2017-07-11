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
	
	CompositeToken::~CompositeToken()
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
	
	bool CompositeToken::operator==(const CompositeToken& t) const
	{
		if (tokens.size() != t.tokens.size())
		{
			return false;
		}
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] != t.tokens[i])
			{
				return false;
			}
		}
		return true;
	}
	
	void CompositeToken::toLowerCase()
	{
		for (auto t : tokens)
		{
			t->toLowerCase();
		}
	}
	
	std::vector<std::shared_ptr<Token>> CompositeToken::subTokens() const
	{
		return tokens;
	}
}
}
}