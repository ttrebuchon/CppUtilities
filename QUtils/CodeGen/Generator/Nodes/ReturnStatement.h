#pragma once

#include "Statement.h"


namespace QUtils::CodeGen
{
	class ReturnStatementNode : public StatementNode
	{
		private:
		
		
		protected:
		virtual ReturnStatementNode* clone() const override;
		virtual void clone(ReturnStatementNode*) const;
		
		public:
		
		ReturnStatementNode(std::shared_ptr<Node> = NULL);
		
		virtual std::string toString(const unsigned int, bool startIndent = false) const override;
		std::shared_ptr<ReturnStatementNode> copy() const;
		
		static std::shared_ptr<ReturnStatementNode> Create(std::shared_ptr<Node> = NULL);
	};
	
}