#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/StringLiteral.h>



namespace QUtils::CodeGen
{
	StringLiteralNode* StringLiteralNode::clone() const
	{
		auto ptr = new StringLiteralNode();
		ptr->value = value;
		return ptr;
	}
	
	std::string StringLiteralNode::literalText() const
	{
		return value;
	}
	
	StringLiteralNode::StringLiteralNode() : GenericLiteralNode<std::string>("")
	{
		
	}
	
	StringLiteralNode::StringLiteralNode(const std::string literal) : GenericLiteralNode<std::string>("\"" + Helpers::escapeString(literal) + "\"")
	{
		
	}
	
	std::shared_ptr<StringLiteralNode> StringLiteralNode::Create(const std::string val)
	{
		return std::make_shared<StringLiteralNode>(val);
	}
}