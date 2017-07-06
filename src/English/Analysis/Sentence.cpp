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
}
}
}