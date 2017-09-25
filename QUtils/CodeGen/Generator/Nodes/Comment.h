#pragma once

#include "../Node.h"


namespace QUtils::CodeGen
{
	class CommentNode : public Node
	{
		private:
		
		
		protected:
		std::vector<std::shared_ptr<Node>> lines;
		
		virtual CommentNode* clone() const override;
		virtual void clone(CommentNode*) const;
		
		public:
		
		CommentNode(std::shared_ptr<Node>);
		CommentNode(const std::string);
		CommentNode();
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<CommentNode> copy() const;
		
		static std::shared_ptr<CommentNode> Create(std::shared_ptr<Node>);
		static std::shared_ptr<CommentNode> Create(const std::string);
		static std::shared_ptr<CommentNode> Create();
		
		void add(std::shared_ptr<Node>);
		void add(const std::string);
		
		size_t size() const;
	};
}