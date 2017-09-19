#pragma once

#include "../Node.h"


namespace QUtils::CodeGen
{
	class NamespaceNode : public BodyNode
	{
		private:
		
		
		protected:
		std::string ns;
		
		virtual NamespaceNode* clone() const override;
		virtual void clone(NamespaceNode*) const;
		
		public:
		
		std::vector<std::shared_ptr<Node>>& children;
		
		NamespaceNode(const std::string);
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<NamespaceNode> copy() const;
	};
}