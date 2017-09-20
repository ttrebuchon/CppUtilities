#pragma once

#include "GenericLiteral.h"


namespace QUtils::CodeGen
{
	class StringLiteralNode : public GenericLiteralNode<std::string>
	{
		private:
		
		protected:
		
		virtual StringLiteralNode* clone() const override;
		
		virtual std::string literalText() const override;
		
		StringLiteralNode();
		
		public:
		StringLiteralNode(const std::string);
		
		static std::shared_ptr<StringLiteralNode> Create(const std::string);
		
	};
}