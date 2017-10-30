#include <QUtils/CodeGen/Generator/Nodes/Invocation.h>
#include <QUtils/CodeGen/Generator/Nodes/StringNode.h>

#include <QUtils/String/String.h>


namespace QUtils::CodeGen
{
	InvocationNode* InvocationNode::clone() const
	{
		auto ptr = new InvocationNode(identifier->copy());
		clone(ptr);
		return ptr;
	}
	
	void InvocationNode::clone(InvocationNode* ptr) const
	{
		Node::clone(ptr);
		
		ptr->identifier = identifier->copy();
		ptr->arguments.clear();
		for (const auto arg : this->arguments)
		{
			if (arg != NULL)
			{
				ptr->arguments.push_back(arg->copy());
			}
			else
			{
				ptr->arguments.push_back(NULL);
			}
		}
		
		ptr->templateArguments.clear();
		for (const auto arg : this->templateArguments)
		{
			ptr->templateArguments.push_back(arg != NULL ? arg->copy() : NULL);
		}
		
	}
	
	
	InvocationNode::InvocationNode(const std::string identifier, std::vector<std::shared_ptr<Node>> arguments) : InvocationNode(StringNode::Create(identifier), arguments)
	{
		
	}
	
	InvocationNode::InvocationNode(const std::shared_ptr<Node> identifier, std::vector<std::shared_ptr<Node>> arguments) : 
	Node(),
	identifier(identifier),
	arguments(arguments),
	templateArguments()
	{
		
	}
	
	InvocationNode::InvocationNode(const std::string identifier) : InvocationNode(StringNode::Create(identifier))
	{
		
	}
	
	InvocationNode::InvocationNode(const std::shared_ptr<Node> identifier) : 
	Node(),
	identifier(identifier),
	arguments(),
	templateArguments()
	{
		
	}
	
	
	std::string InvocationNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string str = identifier->toString(indentation, startIndent);
		
		if (templateArguments.size() > 0)
		{
			str += "<";
			
			bool firstArg = true;
			for (auto arg : templateArguments)
			{
				if (arg != NULL)
				{
					if (!firstArg)
					{
						str += ", ";
					}
					str += arg->toString(0, false);
					firstArg = false;
				}
			}
			
			str += ">";
		}
		
		str += "(";
		for (int i = 0; i < arguments.size(); ++i)
		{
			if (i != 0)
			{
				str += ", ";
			}
			
			str += arguments[i]->toString(0, false);
		}
		
		str += ")";
		return str;
	}
	
	std::shared_ptr<InvocationNode> InvocationNode::copy() const
	{
		return std::shared_ptr<InvocationNode>(clone());
	}
	
	std::shared_ptr<InvocationNode> InvocationNode::Create(const std::string identifier, std::vector<std::shared_ptr<Node>> arguments)
	{
		return std::make_shared<InvocationNode>(identifier, arguments);
	}
	
	std::shared_ptr<InvocationNode> InvocationNode::Create(const std::shared_ptr<Node> identifier, std::vector<std::shared_ptr<Node>> arguments)
	{
		return std::make_shared<InvocationNode>(identifier, arguments);
	}
	
	std::shared_ptr<InvocationNode> InvocationNode::Create(const std::string identifier)
	{
		return std::make_shared<InvocationNode>(identifier);
	}
	
	std::shared_ptr<InvocationNode> InvocationNode::Create(const std::shared_ptr<Node> identifier)
	{
		return std::make_shared<InvocationNode>(identifier);
	}
	
}