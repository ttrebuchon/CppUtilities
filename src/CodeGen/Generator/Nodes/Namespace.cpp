#include <QUtils/CodeGen/Generator/Nodes/Namespace.h>


namespace QUtils::CodeGen
{
	NamespaceNode* NamespaceNode::clone() const
	{
		auto ptr = new NamespaceNode(ns);
		this->clone(ptr);
		return ptr;
	}
	
	void NamespaceNode::clone(NamespaceNode* ptr) const
	{
		BodyNode::clone(ptr);
		ptr->ns = this->ns;
	}
	
	
	
	NamespaceNode::NamespaceNode(const std::string ns) : BodyNode(), ns(ns), children(BodyNode::children)
	{
		
	}
	
	std::string NamespaceNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string s = "namespace " + ns + "\n";
		if (startIndent)
		{
			Helpers::indent(s, indentation);
		}
		return s + BodyNode::toString(indentation, true);
	}
		
	std::shared_ptr<NamespaceNode> NamespaceNode::copy() const
	{
		return std::shared_ptr<NamespaceNode>(clone());
	}
	
	std::shared_ptr<NamespaceNode> NamespaceNode::Create(const std::string ns)
	{
		return std::make_shared<NamespaceNode>(ns);
	}
}