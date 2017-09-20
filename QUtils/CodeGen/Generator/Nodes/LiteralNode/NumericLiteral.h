#pragma once

#include "../Literal.h"


namespace QUtils::CodeGen
{
	class NumericLiteralNode : public LiteralNode
	{
		private:
		
		protected:
		
		virtual NumericLiteralNode* clone() const override;
		
		virtual std::string literalText() const override;
		
		public:
		NumericLiteralNode(const char);
		
		
		static std::shared_ptr<NumericLiteralNode> Create(const int);
		static std::shared_ptr<NumericLiteralNode> Create(const long);
		static std::shared_ptr<NumericLiteralNode> Create(const float);
		static std::shared_ptr<NumericLiteralNode> Create(const double);
		static std::shared_ptr<NumericLiteralNode> Create(const long long);
		static std::shared_ptr<NumericLiteralNode> Create(const unsigned int);
		static std::shared_ptr<NumericLiteralNode> Create(const unsigned long);
		static std::shared_ptr<NumericLiteralNode> Create(const unsigned long long);
		
	};
}