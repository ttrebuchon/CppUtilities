#include <QUtils/English/Analysis/Parentheses.h>
#include <QUtils/English/Analysis/Punctuation.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Parentheses::Parentheses(const std::shared_ptr<Punctuation> start, const std::vector<std::shared_ptr<Token>>& tokens, std::shared_ptr<Punctuation> end) : CompositeToken(tokens), start(start), end(end)
	{
		
	}
	
	
	std::string Parentheses::text() const
	{
		return start->text() + CompositeToken::text() + end->text();
	}
	
	std::vector<std::shared_ptr<const Token>> Parentheses::expand() const
	{
		int size;
		std::vector<std::shared_ptr<const Token>> v((size = 2 + this->tokens.size()));
		v[0] = start;
		for (int i = 1; i < size-1; i++)
		{
			v[i] = this->tokens[i-1];
		}
		v[size-1] = end;
		return v;
	}
}
}
}