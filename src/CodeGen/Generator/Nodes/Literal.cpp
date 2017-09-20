#include <QUtils/CodeGen/Generator/Nodes/Literal.h>
#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/StringLiteral.h>
#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/CharLiteral.h>
#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/NumericLiteral.h>


namespace QUtils::CodeGen
{
	LiteralNode::LiteralNode() : Node()
	{
		
	}
	
	
	std::string LiteralNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = "";
		if (startIndent)
		{
			Helpers::indent(str, indentation);
		}
		
		str += literalText();
		
		return str;
	}
	
	
	std::shared_ptr<LiteralNode> LiteralNode::copy() const
	{
		return std::shared_ptr<LiteralNode>(clone());
	}
	
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const std::string value)
	{
		return StringLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const char c)
	{
		return CharLiteralNode::Create(c);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const int value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const long value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const float value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const double value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const long long value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const unsigned int value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const unsigned long value)
	{
		return NumericLiteralNode::Create(value);
	}
	
	std::shared_ptr<LiteralNode> LiteralNode::Create(const unsigned long long value)
	{
		return NumericLiteralNode::Create(value);
	}
	
}