#include <QUtils/CodeGen/Generator/Nodes/FunctionDeclaration.h>


namespace QUtils::CodeGen
{
	FunctionDeclarationNode* FunctionDeclarationNode::clone() const
	{
		auto ptr = new FunctionDeclarationNode(returnType, identifier, NULL);
		clone(ptr);
		return ptr;
	}
	
	void FunctionDeclarationNode::clone(FunctionDeclarationNode* ptr) const
	{
		Node::clone(ptr);
		ptr->returnType = returnType;
		ptr->identifier = identifier;
		ptr->arguments.clear();
		for (const auto arg : this->arguments)
		{
			ptr->arguments.push_back(arg->copy());
		}
		
		ptr->body = (this->body != NULL ? this->body->copy() : NULL);
	}
	
	
	FunctionDeclarationNode::FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<BodyNode> body) : identifier(identifier), returnType(returnType), arguments(arguments), body(body)
	{
		
	}
	FunctionDeclarationNode::FunctionDeclarationNode(const std::string returnType, const std::string identifier, std::shared_ptr<BodyNode> body) : FunctionDeclarationNode(returnType, identifier, std::vector<std::shared_ptr<Node>>(), body)
	{
		
	}
	
	
	std::string FunctionDeclarationNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = (startIndent ? Helpers::indent(indentation) : "") + returnType + " " + identifier + "(";
		for (int i = 0; i < arguments.size(); ++i)
		{
			if (i != 0)
			{
				str += ", ";
			}
			
			str += arguments[i]->toString(0, false);
		}
		
		str += ")";
		if (body != NULL)
		{
			str += "\n";
			str += body->toString(indentation, true);
		}
		else
		{
			str += ";\n";
		}
		return str;
	}
	
	std::shared_ptr<FunctionDeclarationNode> FunctionDeclarationNode::copy() const
	{
		return std::shared_ptr<FunctionDeclarationNode>(clone());
	}
	
	std::shared_ptr<FunctionDeclarationNode> FunctionDeclarationNode::Create(const std::string returnType, const std::string identifier, std::vector<std::shared_ptr<Node>> arguments, std::shared_ptr<BodyNode> body)
	{
		return std::make_shared<FunctionDeclarationNode>(returnType, identifier, arguments, body);
	}
	
	std::shared_ptr<FunctionDeclarationNode> FunctionDeclarationNode::Create(const std::string returnType, const std::string identifier, std::shared_ptr<BodyNode> body)
	{
		return std::make_shared<FunctionDeclarationNode>(returnType, identifier, body);
	}
	
}