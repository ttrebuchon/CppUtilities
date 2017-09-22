#pragma once

#include "../Node.h"
#include "CVQualifiers.h"

namespace QUtils::CodeGen
{
	class VariableDeclarationNode : public Node, public CVQualifiers
	{
		private:
		
		protected:
		std::string type;
		std::string identifier;
		
		virtual VariableDeclarationNode* clone() const override;
		virtual void clone(VariableDeclarationNode*) const;
		
		
		public:
		std::shared_ptr<Node> assignment;
		
		VariableDeclarationNode(const std::string type, const std::string identifier, std::shared_ptr<Node> assignment = NULL);
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<VariableDeclarationNode> copy() const;
		
		static std::shared_ptr<VariableDeclarationNode> Create(const std::string type, const std::string identifier, std::shared_ptr<Node> assignment = NULL);
	};
	
}