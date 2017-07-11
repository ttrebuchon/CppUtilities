#include <QUtils/English/Analysis/Sentence.h>
#include <QUtils/English/Analysis/Punctuation.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Sentence::Sentence(const std::vector<std::shared_ptr<Token>>& tokens, const std::shared_ptr<Punctuation> punc) : CompositeToken(tokens), punc(punc)
	{
		
	}
	
	std::string Sentence::text() const
	{
		return CompositeToken::text() + punc->text();
	}
	
	std::vector<std::shared_ptr<const Token>> Sentence::expand() const
	{
		std::vector<std::shared_ptr<const Token>> v(this->tokens.begin(), this->tokens.end());
		v.push_back(punc);
		return v;
	}
	
	void Sentence::toLowerCase()
	{
		CompositeToken::toLowerCase();
		punc->toLowerCase();
	}
	
	std::shared_ptr<Token> Sentence::clone() const
	{
		std::vector<std::shared_ptr<Token>> nTokens(this->tokens.size());
		for (int i = 0; i < this->tokens.size(); i++)
		{
			nTokens[i] = this->tokens[i]->clone();
		}
		return std::make_shared<Sentence>(nTokens, std::dynamic_pointer_cast<Punctuation>(punc->clone()));
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Sentence::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	for (int i = 0; i < this->tokens.size(); i++)
	 	{
	 		m[this->tokens[i]].push_back(i);
	 		auto subM = this->tokens[i]->indexes();
	 		for (auto pair : subM)
	 		{
	 			for (auto subIndex : pair.second)
	 			{
	 				m[pair.first].push_back(subIndex+i);
	 			}
	 		}
	 	}
	 	m[punc].push_back(this->tokens.size());
	 	return m;
	 }
	 
	 std::vector<std::shared_ptr<Token>> Sentence::subTokens() const
	{
		auto v = CompositeToken::subTokens();
		v.push_back(punc);
		return v;
	}
}
}
}