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
}
}
}