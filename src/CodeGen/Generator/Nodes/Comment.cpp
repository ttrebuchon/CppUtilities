#include <QUtils/CodeGen/Generator/Nodes/Comment.h>
#include <QUtils/CodeGen/Generator/Nodes/StringNode.h>


namespace QUtils::CodeGen
{
	CommentNode* CommentNode::clone() const
	{
		auto ptr = new CommentNode();
		this->clone(ptr);
		return ptr;
	}
	
	void CommentNode::clone(CommentNode* ptr) const
	{
		Node::clone(ptr);
		ptr->lines.clear();
		for (auto arg : lines)
		{
			if (arg != NULL)
			{
				ptr->lines.push_back(arg->copy());
			}
			else
			{
				ptr->lines.push_back(NULL);
			}
		}
	}
	
	
	CommentNode::CommentNode(std::shared_ptr<Node> line) : Node(), lines(1, line)
	{
		lines[0] = line;
	}
	
	CommentNode::CommentNode(const std::string line) : CommentNode(StringNode::Create(line))
	{
		
	}
	
	CommentNode::CommentNode() : Node(), lines()
	{
		
	}
	
	std::string CommentNode::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string indent = Helpers::indent(indentation);
		
		std::string s;
		if (startIndent)
		{
			s += indent;
		}
		if (lines.size() > 1)
		{
			s += "/*\n";
			for (auto line : lines)
			{
				if (line != NULL)
				{
					s += line->toString(indentation, true);
				}
				else
				{
					s += indent;
				}
				s += "\n";
			}
			s += "*/\n";
		}
		else if (lines.size() == 1)
		{
			s += "//";
			if (lines[0] != NULL)
			{
				s += lines[0]->toString(0, false);
			}
			s += "\n";
		}
		else
		{
			s += "//\n";
		}
		return s;
	}
		
	std::shared_ptr<CommentNode> CommentNode::copy() const
	{
		return std::shared_ptr<CommentNode>(clone());
	}
	
	std::shared_ptr<CommentNode> CommentNode::Create(std::shared_ptr<Node> line)
	{
		return std::make_shared<CommentNode>(line);
	}
	
	std::shared_ptr<CommentNode> CommentNode::Create(const std::string line)
	{
		return std::make_shared<CommentNode>(line);
	}
	
	std::shared_ptr<CommentNode> CommentNode::Create()
	{
		return std::make_shared<CommentNode>();
	}
	
	void CommentNode::add(std::shared_ptr<Node> line)
	{
		lines.push_back(line);
	}
	
	void CommentNode::add(const std::string line)
	{
		lines.push_back(StringNode::Create(line));
	}
	
	size_t CommentNode::size() const
	{
		return lines.size();
	}
}