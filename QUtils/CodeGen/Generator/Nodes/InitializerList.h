#pragma once

#include "../Node.h"
#include <vector>

namespace QUtils::CodeGen
{
	class InitializerListNode : public Node
	{
		private:
		
		protected:
		
		virtual InitializerListNode* clone() const override;
		virtual void clone(InitializerListNode*) const;
		
		public:
		InitializerListNode();
		std::vector<std::shared_ptr<Node>> children;
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<InitializerListNode> copy() const;
		
		static std::shared_ptr<InitializerListNode> Create();
	};
}