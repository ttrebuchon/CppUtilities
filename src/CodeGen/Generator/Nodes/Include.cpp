#include <QUtils/CodeGen/Generator/Nodes/Include.h>


namespace QUtils::CodeGen
{
	IncludeNode* IncludeNode::clone() const
	{
		auto ptr = new IncludeNode(path, relative);
		clone(ptr);
		return ptr;
	}
	
	void IncludeNode::clone(IncludeNode* ptr) const
	{
		Node::clone(ptr);
		ptr->path = this->path;
		ptr->relative = this->relative;
	}
	
	
	
	IncludeNode::IncludeNode(const std::string path, bool relative) : Node(), path(path), relative(relative)
	{
		
	}
	
	
	
	
	
	std::string IncludeNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = "";
		if (startIndent)
		{
			Helpers::indent(str, indentation);
		}
		str += "#include ";
		if (relative)
		{
			str += "\"" + path + "\"\n";
		}
		else
		{
			str += "<" + path + ">\n";
		}
		return str;
	}
	
	std::shared_ptr<IncludeNode> IncludeNode::copy() const
	{
		return std::shared_ptr<IncludeNode>(clone());
	}
	
}