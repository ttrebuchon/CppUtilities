#pragma once
#include <string>
#include <memory>

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Token
	{
		protected:
		
		public:
		
		virtual std::string text() const = 0;
		virtual std::string type() const = 0;
		
		virtual bool operator==(const Token& t) const
		{ return text() == t.text(); }
		virtual bool operator!=(const Token& t) const
		{ return !operator==(t); }
		
	};
}
}
}