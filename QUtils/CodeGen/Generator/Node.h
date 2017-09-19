#pragma once

#include <string>
#include <vector>
#include <memory>

namespace QUtils::CodeGen
{
	class Node
	{
		private:
		
		protected:
		virtual Node* clone() const = 0;
		virtual void clone(Node*) const;
		
		public:
		Node();
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const = 0;
		std::shared_ptr<Node> copy() const;
	};
	
	
	class BodyNode : public Node
	{
		private:
		
		protected:
		std::vector<std::shared_ptr<Node>> children;
		
		virtual BodyNode* clone() const override;
		virtual void clone(BodyNode*) const;
		
		public:
		BodyNode();
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<BodyNode> copy() const;
	};
	
	namespace Helpers
	{
		void indent(std::string&, unsigned int count);
		std::string indent(unsigned int count);
		void escapeString(std::string&);
		
		void indentMultiLine(std::string&, unsigned int count);
	}
}