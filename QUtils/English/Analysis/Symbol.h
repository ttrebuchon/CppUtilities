#pragma once
#include "Token.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Symbol : public Token
	{
		protected:
		std::string symbol;
		
		public:
		Symbol(std::string);
		
		virtual std::string text() const override;
		virtual std::string type() const override { return "symbol"; }
	};
}
}
}