#pragma once

#include "GenericLiteral.h"


namespace QUtils::CodeGen
{
	class CharLiteralNode : public GenericLiteralNode<char>
	{
		private:
		
		protected:
		
		virtual CharLiteralNode* clone() const override;
		
		virtual std::string literalText() const override;
		
		public:
		CharLiteralNode(const char);
		
		static std::shared_ptr<CharLiteralNode> Create(const char);
		
	};
}