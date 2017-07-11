#pragma once
#include "Token.h"
#include <vector>

namespace QUtils
{
namespace English
{
namespace Internal
{
	class CompositeToken : public Token
	{
		protected:
		std::vector<std::shared_ptr<Token>> tokens;
		
		public:
		CompositeToken(const std::vector<std::shared_ptr<Token>>&);
		CompositeToken(const int size);
		CompositeToken();
		virtual ~CompositeToken();
		
		virtual bool operator==(const CompositeToken&) const;
		
		virtual bool operator!=(const CompositeToken& t) const
		{ return !operator==(t); }
		
		virtual std::string text() const override;
		virtual TokenType type() const override = 0;
		
		virtual std::vector<std::shared_ptr<const Token>> expand() const override = 0;
		
		virtual void toLowerCase() override;
		
		virtual std::shared_ptr<Token> clone() const override = 0;
		
		virtual std::map<std::shared_ptr<Token>, std::vector<unsigned int>> indexes() const override = 0;
		
		virtual std::vector<std::shared_ptr<Token>> subTokens() const override;
	};
}
}
}