#include <QUtils/CodeGen/Generator/Nodes/Statement.h>


namespace QUtils::CodeGen
{
	StatementNode* StatementNode::clone() const
	{
		if (child != NULL)
		{
			return new StatementNode(child->copy());
		}
		else
		{
			return new StatementNode();
		}
	}
	
	void StatementNode::clone(StatementNode* ptr) const
	{
		Node::clone(ptr);
		if (this->child != NULL)
		{
			ptr->child = this->child->copy();
		}
		else
		{
			ptr->child = NULL;
		}
	}
	
	
	StatementNode::StatementNode(std::shared_ptr<Node> child) : Node(), child(child)
	{
		
	}
	
	
	std::string StatementNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string s;
		if (startIndent)
		{
			s = Helpers::indent(indentation);
		}
		if (child != NULL)
		{
			s += child->toString(indentation, false);
		}
		s += ";\n";
		return s;
	}
	
	std::shared_ptr<StatementNode> StatementNode::copy() const
	{
		return std::shared_ptr<StatementNode>(clone());
	}
	
	std::shared_ptr<StatementNode> StatementNode::Create(std::shared_ptr<Node> child)
	{
		return std::make_shared<StatementNode>(child);
	}
}