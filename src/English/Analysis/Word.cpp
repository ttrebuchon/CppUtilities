#include <QUtils/English/Analysis/Word.h>
#include <QUtils/String/String.h>

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
	
	void Word::toLowerCase()
	{
		word = QUtils::String(word).toLower();
	}
	
	std::shared_ptr<Token> Word::clone() const
	{
		return std::make_shared<Word>(word);
	}
	
	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> Word::indexes() const
	 {
	 	std::map<std::shared_ptr<Token>, std::vector<unsigned int>> m;
	 	return m;
	 }
}
}
}