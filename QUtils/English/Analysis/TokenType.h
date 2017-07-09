#pragma once

namespace QUtils
{
namespace English
{
	enum TokenType
	{
		Word = 1,
		Number = 2,
		Punctuation = 4,
		Symbol = 8,
		Whitespace = 16,
		Sentence = 32,
		Parentheses = 64,
		
	};
	
	/*inline TokenType operator|(TokenType a, TokenType b)
	{
		return static_cast<TokenType>(static_cast<int>(a) | static_cast<int>(b));
	}*/
}
}