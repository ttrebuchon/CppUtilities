#include <QUtils/CodeGen/Generator/Nodes/ReturnStatement.h>


namespace QUtils::CodeGen
{
	ReturnStatementNode* ReturnStatementNode::clone() const
	{
		if (child != NULL)
		{
			return new ReturnStatementNode(child->copy());
		}
		else
		{
			return new ReturnStatementNode();
		}
	}
	
	void ReturnStatementNode::clone(ReturnStatementNode* ptr) const
	{
		StatementNode::clone(ptr);
	}
	
	
	ReturnStatementNode::ReturnStatementNode(std::shared_ptr<Node> child) : StatementNode(child)
	{
		
	}
	
	
	std::string ReturnStatementNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string s;
		if (startIndent)
		{
			s = Helpers::indent(indentation);
		}
		s += "return ";
		s += StatementNode::toString(indentation, false);
		return s;
	}
	
	std::shared_ptr<ReturnStatementNode> ReturnStatementNode::copy() const
	{
		return std::shared_ptr<ReturnStatementNode>(clone());
	}
	
	std::shared_ptr<ReturnStatementNode> ReturnStatementNode::Create(std::shared_ptr<Node> child)
	{
		return std::make_shared<ReturnStatementNode>(child);
	}
}