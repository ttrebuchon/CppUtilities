#pragma once

#include "../Literal.h"


namespace QUtils::CodeGen
{
	template <class T>
	class GenericLiteralNode : public LiteralNode
	{
		private:
		
		protected:
		T value;
		
		virtual GenericLiteralNode<T>* clone() const = 0;
		
		virtual std::string literalText() const = 0;
		
		public:
		GenericLiteralNode(const T value) : LiteralNode(), value(value)
		{
			
		}
		
	};
}