#pragma once
#include "Token.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Whitespace : public Token
	{
		protected:
		std::string space;
		
		public:
		Whitespace(const std::string);
		
		virtual std::string text() const override;
		virtual std::string type() const override { return "whitespace"; }
	};
}
}
}