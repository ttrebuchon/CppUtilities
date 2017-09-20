#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/CharLiteral.h>



namespace QUtils::CodeGen
{
	CharLiteralNode* CharLiteralNode::clone() const
	{
		auto ptr = new CharLiteralNode(value);
		return ptr;
	}
	
	std::string CharLiteralNode::literalText() const
	{
		//TODO
		return std::string("") + value;
	}
	
	CharLiteralNode::CharLiteralNode(const char literal) : GenericLiteralNode<char>(literal)
	{
		
	}
	
	std::shared_ptr<CharLiteralNode> CharLiteralNode::Create(const char val)
	{
		return std::make_shared<CharLiteralNode>(val);
	}
}