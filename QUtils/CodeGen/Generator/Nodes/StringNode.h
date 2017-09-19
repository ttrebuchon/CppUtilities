#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class StringNode : public Node
	{
		private:
		
		protected:
		std::string str;
		
		virtual StringNode* clone() const override;
		virtual void clone(StringNode*) const;
		
		public:
		
		StringNode(const std::string);
		
		virtual std::string toString(const unsigned int, bool startIndent = false) const override;
		
		std::shared_ptr<StringNode> copy() const;
	};
}