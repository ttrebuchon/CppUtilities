#pragma once
#include "CompositeToken.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Punctuation;
	
	
	class Sentence : public CompositeToken
	{
		protected:
		std::shared_ptr<Punctuation> punc;
		
		public:
		Sentence(const std::vector<std::shared_ptr<Token>>&, const std::shared_ptr<Punctuation>);
		
		virtual std::string text() const override;
		
		virtual TokenType type() const override { return TokenType::Sentence; }
		
		virtual std::vector<std::shared_ptr<const Token>> expand() const override;
	};
}
}
}