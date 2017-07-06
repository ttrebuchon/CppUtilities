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
		
		virtual std::string type() const override { return "number"; }
	};
}
}
}