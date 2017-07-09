#pragma once
#include <string>
#include <memory>
#include <vector>
#include "TokenType.h"

namespace QUtils
{
namespace English
{
namespace Internal
{
	class Token : public std::enable_shared_from_this<Token>
	{
		protected:
		
		public:
		
		virtual std::string text() const = 0;
		virtual TokenType type() const = 0;
		
		virtual bool operator==(const Token& t) const
		{ return text() == t.text(); }
		virtual bool operator!=(const Token& t) const
		{ return !operator==(t); }
		
		virtual std::vector<std::shared_ptr<const Token>> expand() const {
			std::vector<std::shared_ptr<const Token>> v;
			v.push_back(shared_from_this()); 
			return v;
		}
	};
}
}
}