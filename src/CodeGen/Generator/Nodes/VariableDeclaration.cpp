#include <QUtils/CodeGen/Generator/Nodes/VariableDeclaration.h>


namespace QUtils::CodeGen
{
	VariableDeclarationNode* VariableDeclarationNode::clone() const
	{
		auto ptr = new VariableDeclarationNode(type, identifier);
		clone(ptr);
		return ptr;
	}
	
	void VariableDeclarationNode::clone(VariableDeclarationNode* ptr) const
	{
		Node::clone(ptr);
		CVQualifiers::clone(ptr);
		ptr->type = this->type;
		ptr->identifier = this->identifier;
		ptr->assignment = (this->assignment != NULL ? assignment->copy() : NULL);
	}
	
	
	
	VariableDeclarationNode::VariableDeclarationNode(const std::string type, const std::string identifier, std::shared_ptr<Node> assignment) : Node(), CVQualifiers(), type(type), identifier(identifier), assignment(assignment)
	{
		
	}
	
	
	
	
	
	std::string VariableDeclarationNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = "";
		if (startIndent)
		{
			Helpers::indent(str, indentation);
		}
		
		auto quals = CVQualifiers::toString(0, false);
		if (quals.length() > 0)
		{
			str += CVQualifiers::toString(0, false) + " ";
		}
		
		str += type + " " + identifier;
		
		if (assignment)
		{
			str += " = " + assignment->toString(0, false);
		}
		str += ";\n";
		
		return str;
	}
	
	std::shared_ptr<VariableDeclarationNode> VariableDeclarationNode::copy() const
	{
		return std::shared_ptr<VariableDeclarationNode>(clone());
	}
	
	std::shared_ptr<VariableDeclarationNode> VariableDeclarationNode::Create(const std::string type, const std::string identifier, std::shared_ptr<Node> assignment)
	{
		return std::make_shared<VariableDeclarationNode>(type, identifier, assignment);
	}
	
}