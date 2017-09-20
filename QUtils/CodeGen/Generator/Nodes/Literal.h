#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class StringLiteralNode;
	class NumericLiteralNode;
	class CharLiteralNode;
	
	class LiteralNode : public Node
	{
		private:
		
		protected:
		
		virtual LiteralNode* clone() const = 0;
		
		virtual std::string literalText() const = 0;
		
		public:
		LiteralNode();
		
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		
		std::shared_ptr<LiteralNode> copy() const;
		
		static std::shared_ptr<LiteralNode> Create(const std::string);
		static std::shared_ptr<LiteralNode> Create(const char);
		static std::shared_ptr<LiteralNode> Create(const int);
		static std::shared_ptr<LiteralNode> Create(const long);
		static std::shared_ptr<LiteralNode> Create(const float);
		static std::shared_ptr<LiteralNode> Create(const double);
		static std::shared_ptr<LiteralNode> Create(const long long);
		static std::shared_ptr<LiteralNode> Create(const unsigned int);
		static std::shared_ptr<LiteralNode> Create(const unsigned long);
		static std::shared_ptr<LiteralNode> Create(const unsigned long long);
	};
}