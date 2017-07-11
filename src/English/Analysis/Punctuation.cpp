#include <QUtils/English/Analysis/Punctuation.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Punctuation::Punctuation(const std::string punc) : Token(), punc(punc)
	{
		
	}
	
	Punctuation::Punctuation(const char punc) : Punctuation(std::string() + punc)
	{
		
	}
	
	Punctuation::Punctuation() : Punctuation("")
	{
		
	}
	
	std::string Punctuation::text() const
	{
		return punc;
	}
	
	std::shared_ptr<Token> Punctuation::clone() const
	{
		return std::make_shared<Punctuation>(punc);
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Punctuation::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	return m;
	 }
}
}
}