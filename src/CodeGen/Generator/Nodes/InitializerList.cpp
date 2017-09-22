#include <QUtils/CodeGen/Generator/Nodes/InitializerList.h>


namespace QUtils::CodeGen
{
	InitializerListNode* InitializerListNode::clone() const
	{
		auto ptr = new InitializerListNode();
		clone(ptr);
		return ptr;
	}
	
	void InitializerListNode::clone(InitializerListNode* ptr) const
	{
		Node::clone(ptr);
		ptr->children.clear();
		for (auto child : this->children)
		{
			ptr->children.push_back( child != NULL ? child->copy() : NULL);
		}
	}
	
	
	
	InitializerListNode::InitializerListNode() : Node(), children()
	{
		
	}
	
	
	
	
	
	std::string InitializerListNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = "";
		if (startIndent)
		{
			Helpers::indent(str, indentation);
		}
		str += "{ ";
		bool first = true;
		for (auto child : children)
		{
			if (!first)
			{
				str += ", ";
			}
			first = false;
			str += (child != NULL ? child->toString(0, false) : "");
		}
		str += " }";
		
		return str;
	}
	
	std::shared_ptr<InitializerListNode> InitializerListNode::copy() const
	{
		return std::shared_ptr<InitializerListNode>(clone());
	}
	
	std::shared_ptr<InitializerListNode> InitializerListNode::Create()
	{
		return std::make_shared<InitializerListNode>();
	}
	
}