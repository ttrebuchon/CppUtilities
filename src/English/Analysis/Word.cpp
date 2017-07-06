#include <QUtils/English/Analysis/Word.h>

namespace QUtils
{
namespace English
{
namespace Internal
{
	Word::Word(const std::string word) : Token(), word(word)
	{
		
	}
	
	Word::Word() : Word("")
	{
		
	}
	
	std::string Word::text() const
	{
		return word;
	}
}
}
}