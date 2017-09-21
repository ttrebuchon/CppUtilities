#pragma once

#include "../Node.h"
#include "CVQualifiers.h"

namespace QUtils::CodeGen
{
	class FunctionDeclarationNode : public Node, public CVQualifiers
	{
		private:
		
		protected:
		std::string identifier;
		std::string returnType;
		
		
		virtual FunctionDeclarationNode* clone() const override;
		virtual void clone(FunctionDeclarationNode*) const;
		
		public:
		FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<Node> body = NULL);
		FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::shared_ptr<Node> body = NULL);
		
		std::vector<std::shared_ptr<Node>> arguments;
		std::vector<std::shared_ptr<Node>> templateArguments;
		std::shared_ptr<Node> body;
		
		
		bool isNoExcept;
		bool isOverride;
		
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<FunctionDeclarationNode> copy() const;
		
		static std::shared_ptr<FunctionDeclarationNode> Create(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<Node> body = NULL);
		static std::shared_ptr<FunctionDeclarationNode> Create(const std::string returnType, const std::string identifier, std::shared_ptr<Node> body = NULL);
	};
}