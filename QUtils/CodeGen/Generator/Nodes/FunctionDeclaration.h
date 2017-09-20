#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class FunctionDeclarationNode : public Node
	{
		private:
		
		protected:
		std::string identifier;
		std::string returnType;
		std::vector<std::shared_ptr<Node>> arguments;
		std::shared_ptr<BodyNode> body;
		
		virtual FunctionDeclarationNode* clone() const override;
		virtual void clone(FunctionDeclarationNode*) const;
		
		public:
		FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<BodyNode> body = NULL);
		FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::shared_ptr<BodyNode> body = NULL);
		
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<FunctionDeclarationNode> copy() const;
		
		static std::shared_ptr<FunctionDeclarationNode> Create(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<BodyNode> body = NULL);
		static std::shared_ptr<FunctionDeclarationNode> Create(const std::string returnType, const std::string identifier, std::shared_ptr<BodyNode> body = NULL);
	};
}