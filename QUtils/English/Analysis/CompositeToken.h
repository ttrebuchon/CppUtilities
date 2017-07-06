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
		
		virtual bool operator==(const CompositeToken&) const;
		
		virtual bool operator!=(const CompositeToken& t) const
		{ return !operator==(t); }
		
		virtual std::string text() const override;
		virtual std::string type() const override = 0;
	};
}
}
}