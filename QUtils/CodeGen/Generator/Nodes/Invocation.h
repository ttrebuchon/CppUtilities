#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class InvocationNode : public Node
	{
		private:
		
		protected:
		std::shared_ptr<Node> identifier;
		
		
		virtual InvocationNode* clone() const override;
		virtual void clone(InvocationNode*) const;
		
		public:
		InvocationNode(const std::string identifier, std::vector<std::shared_ptr<Node>> arguments);
		InvocationNode(const std::shared_ptr<Node> identifier, std::vector<std::shared_ptr<Node>> arguments);
		
		InvocationNode(const std::string identifier);
		InvocationNode(const std::shared_ptr<Node> identifier);
		
		std::vector<std::shared_ptr<Node>> arguments;
		std::vector<std::shared_ptr<Node>> templateArguments;
		
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<InvocationNode> copy() const;
		
		static std::shared_ptr<InvocationNode> Create(const std::string identifier, std::vector<std::shared_ptr<Node>> arguments);
		static std::shared_ptr<InvocationNode> Create(const std::shared_ptr<Node> identifier, std::vector<std::shared_ptr<Node>> arguments);
		static std::shared_ptr<InvocationNode> Create(const std::string identifier);
		static std::shared_ptr<InvocationNode> Create(const std::shared_ptr<Node> identifier);
	};
}