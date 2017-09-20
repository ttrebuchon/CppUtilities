#include <QUtils/CodeGen/Generator/Node.h>
#include <QUtils/String/String.h>

#include <iostream>


namespace QUtils::CodeGen
{
	void Node::clone(Node*) const
	{
		
	}
	
	
	
	
	Node::Node()
	{
		
	}
	
	
	
	std::shared_ptr<Node> Node::copy() const
	{
		return std::shared_ptr<Node>(clone());
	}
	
	
	
	
	
	
	
	
	
	BodyNode* BodyNode::clone() const
	{
		auto ptr = new BodyNode();
		this->clone(ptr);
		return ptr;
	}
	
	void BodyNode::clone(BodyNode* ptr) const
	{
		Node::clone(ptr);
		auto len = this->children.size();
		ptr->children = std::vector<std::shared_ptr<Node>>(len);
		
		for (int i = 0; i < len; ++i)
		{
			ptr->children[i] = this->children[i]->copy();
		}
	}
	
	BodyNode::BodyNode() : children()
	{
		
	}
	
	
	std::string BodyNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string ind = Helpers::indent(indentation);
		std::string str = "";
		for (auto child : children)
		{
			str += child->toString(indentation+1, true);
		}
		str = (startIndent ? ind : "") + "{\n" + str + ind + "}\n";
		return str;
	}
	
	std::shared_ptr<BodyNode> BodyNode::copy() const
	{
		return std::shared_ptr<BodyNode>(clone());
	}
	
	
	
	
	
	
	
	
	
	namespace Helpers
	{
		//const std::string indSym = "|X|";//"\t";
		const std::string indSym = "\t";
		void indent(std::string& str, unsigned int count)
		{
			std::string s2 = "";
			while (count > 0)
			{
				s2 += indSym;
				--count;
			}
			str = s2 + str;
		}
		
		std::string indent(unsigned int count)
		{
			std::string s = "";
			while (count > 0)
			{
				s += indSym;
				--count;
			}
			return s;
		}
		
		
		void modifyEscapeString(std::string& str)
		{
			QUtils::String::Replace(str, "\\", "\\\\");
			QUtils::String::Replace(str, "\n", "\\n");
			QUtils::String::Replace(str, "\r", "\\r");
			QUtils::String::Replace(str, "\t", "\\t");
			//QUtils::String::Replace(str, "\0", "\\0");
			QUtils::String::Replace(str, "\"", "\\\"");
			QUtils::String::Replace(str, "\v", "\\v");
			QUtils::String::Replace(str, "\b", "\\b");
			QUtils::String::Replace(str, "\f", "\\f");
			QUtils::String::Replace(str, "\a", "\\a");
		}
		
		
		std::string escapeString(std::string str)
		{
			modifyEscapeString(str);
			return str;
		}
		
		void indentMultiLine(std::string& str, unsigned int count)
		{
			std::string ind = indent(count);
			
			auto offset = ind.length();
			
			std::string suffix;
			if (str.length() > 0)
			{
				if (str[str.length()-1] == '\n')
				{
					suffix = "\n";
					str = str.substr(0, str.length()-1);
				}
			}
			
			QUtils::String qstr(str);
			qstr = qstr.replace("\n", "\n" + ind);
			qstr += suffix;
			str = qstr;
			return;
			
			auto index = str.find("\n");
			if (index == std::string::npos)
			{
				return;
			}
			
			{
				int i = 0;
				while (i < index)
				{
					if (str.substr(i, offset) != ind)
					{
						i += offset;
					}
					else if (str[i] == ' ')
					{
						++i;
					}
					else
					{
						str = str.substr(0, index) + ind + str.substr(index);
						index += offset;
						break;
					}
				}
			}
			index = str.find('\n', index+1);
			
			std::cout << "[" << index << "/" << str.length() << "]\n";
			while (index != std::string::npos && index < str.length())
			{
				if (index == str.length() - 1)
				{
					break;
				}
				str = str.substr(0, index+1) + ind + str.substr(index+1);
				index += offset;
				index = str.find('\n', index+1);
				std::cout << "[" << index << "/" << str.length() << "]\n";
			}
		}
		
	}
	
	
	
}