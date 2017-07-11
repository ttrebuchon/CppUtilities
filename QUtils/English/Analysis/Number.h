#pragma once
#include "Token.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Number : public Token
	{
		protected:
		std::string num;
		long double n;
		
		public:
		Number(const std::string);
		
		virtual std::string text() const override;
		
		virtual TokenType type() const override { return TokenType::Number; }
		
		virtual void toLowerCase() override {}
		
		virtual std::shared_ptr<Token> clone() const override;
		
		virtual std::map<std::shared_ptr<Token>, std::vector<unsigned int>> indexes() const override;
		
		virtual std::vector<std::shared_ptr<Token>> subTokens() const override { return std::vector<std::shared_ptr<Token>>(); }
		
	};
}
}
}