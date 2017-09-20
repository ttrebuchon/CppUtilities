#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class StatementNode : public Node
	{
		private:
		
		protected:
		std::shared_ptr<Node> child;
		
		virtual StatementNode* clone() const override;
		virtual void clone(StatementNode*) const;
		
		public:
		
		StatementNode(std::shared_ptr<Node> = NULL);
		
		virtual std::string toString(const unsigned int, bool startIndent = false) const override;
		
		std::shared_ptr<StatementNode> copy() const;
		
		static std::shared_ptr<StatementNode> Create(std::shared_ptr<Node> = NULL);
	};
}