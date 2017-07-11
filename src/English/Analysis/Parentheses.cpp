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
	
	void Parentheses::toLowerCase()
	{
		CompositeToken::toLowerCase();
		start->toLowerCase();
		end->toLowerCase();
	}
	
	std::shared_ptr<Token> Parentheses::clone() const
	{
		std::vector<std::shared_ptr<Token>> nTokens(this->tokens.size());
		for (int i = 0; i < this->tokens.size(); i++)
		{
			nTokens[i] = this->tokens[i]->clone();
		}
		return std::make_shared<Parentheses>(std::dynamic_pointer_cast<Punctuation>(start->clone()), nTokens, std::dynamic_pointer_cast<Punctuation>(end->clone()));
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Parentheses::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	for (int i = 0; i < this->tokens.size(); i++)
	 	{
	 		m[this->tokens[i]].push_back(i+1);
	 		auto subM = this->tokens[i]->indexes();
	 		for (auto pair : subM)
	 		{
	 			for (auto subIndex : pair.second)
	 			{
	 				m[pair.first].push_back(subIndex+i+1);
	 			}
	 		}
	 	}
	 	m[end].push_back(this->tokens.size()+1);
	 	m[start].push_back(0);
	 	return m;
	 }
	 
	 std::vector<std::shared_ptr<Token>> Parentheses::subTokens() const
	{
		auto v = CompositeToken::subTokens();
		v.push_back(start);
		v.push_back(end);
		return v;
	}
}
}
}