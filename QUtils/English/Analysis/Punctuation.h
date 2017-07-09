#pragma once
#include "Token.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Punctuation : public Token
	{
		protected:
		std::string punc;
		
		public:
		Punctuation(const std::string);
		Punctuation(const char);
		Punctuation();
		
		virtual std::string text() const override;
		virtual TokenType type() const override { return TokenType::Punctuation; }
	};
}
}
}