#pragma once

#include "../Node.h"


namespace QUtils::CodeGen
{
	class FunctionBodyNode : public BodyNode
	{
		private:
		
		
		protected:
		
		virtual FunctionBodyNode* clone() const override;
		virtual void clone(FunctionBodyNode*) const;
		
		public:
		
		std::vector<std::shared_ptr<Node>>& children;
		
		FunctionBodyNode();
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<FunctionBodyNode> copy() const;
		
		static std::shared_ptr<FunctionBodyNode> Create();
	};
}