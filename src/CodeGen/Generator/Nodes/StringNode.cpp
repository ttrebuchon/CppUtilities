#include <QUtils/CodeGen/Generator/Nodes/StringNode.h>


namespace QUtils::CodeGen
{
	StringNode* StringNode::clone() const
	{
		return new StringNode(str);
	}
	
	void StringNode::clone(StringNode* ptr) const
	{
		Node::clone(ptr);
		ptr->str = this->str;
	}
	
	
	StringNode::StringNode(const std::string str) : Node(), str(str)
	{
		
	}
	
	
	std::string StringNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string s;
		if (startIndent)
		{
			s = Helpers::indent(indentation);
		}
		s += str;
		Helpers::indentMultiLine(s, indentation);
		return s;
	}
	
	std::shared_ptr<StringNode> StringNode::copy() const
	{
		return std::shared_ptr<StringNode>(clone());
	}
}