#include <QUtils/CodeGen/Generator/Nodes/LiteralNode/NumericLiteral.h>



namespace QUtils::CodeGen
{
	NumericLiteralNode* NumericLiteralNode::clone() const
	{
		return new NumericLiteralNode(value, suffix);
	}
		
	std::string NumericLiteralNode::literalText() const
	{
		return value + suffix;
	}
		
	NumericLiteralNode::NumericLiteralNode(const std::string val, const std::string suffix) : LiteralNode(), value(val), suffix(suffix)
	{
		
	}
	
	
	
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const int value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), ""));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const long value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "L"));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const float value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "F"));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const double value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), ""));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const long long value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "LL"));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const unsigned int value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "U"));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const unsigned long value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "UL"));
	}
	
	std::shared_ptr<NumericLiteralNode> NumericLiteralNode::Create(const unsigned long long value)
	{
		return std::shared_ptr<NumericLiteralNode>(new NumericLiteralNode(std::to_string(value), "ULL"));
	}
}