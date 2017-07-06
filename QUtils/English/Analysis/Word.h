#pragma once
#include "Token.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Word : public Token
	{
		protected:
		std::string word;
		
		public:
		Word(std::string);
		Word();
		
		virtual std::string text() const override;
		virtual std::string type() const override { return "word"; }
	};
}
}
}