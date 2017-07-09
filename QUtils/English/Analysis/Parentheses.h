#pragma once

#include "CompositeToken.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Punctuation;
	
	
	class Parentheses : public CompositeToken
	{
		protected:
		std::shared_ptr<Punctuation> start;
		std::shared_ptr<Punctuation> end;
		
		public:
		Parentheses(const std::shared_ptr<Punctuation> start, const std::vector<std::shared_ptr<Token>>&, std::shared_ptr<Punctuation> end);
		
		virtual std::string text() const override;
		
		virtual TokenType type() const override { return TokenType::Parentheses; }
		
		virtual std::vector<std::shared_ptr<const Token>> expand() const override;
	};
}
}
}