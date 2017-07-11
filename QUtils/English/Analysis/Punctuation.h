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
		
		virtual void toLowerCase() override {}
		
		virtual std::shared_ptr<Token> clone() const override;
		
		virtual std::map<std::shared_ptr<Token>, std::vector<unsigned int>> indexes() const override;
		
		virtual std::vector<std::shared_ptr<Token>> subTokens() const override { return std::vector<std::shared_ptr<Token>>(); }
	};
}
}
}