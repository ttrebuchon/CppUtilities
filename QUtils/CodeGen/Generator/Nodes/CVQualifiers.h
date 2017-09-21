#pragma once

#include <string>

namespace QUtils::CodeGen
{
	class CVQualifiers
	{
		private:
		
		protected:
		
		virtual void clone(CVQualifiers*) const;
		
		
		
		public:
		
		
		bool isConst;
		bool isConstexpr;
		bool isExtern;
		bool isMutable;
		bool isStatic;
		bool isThread_Local;
		bool isVirtual;
		bool isVolatile;
		
		std::string toString(const unsigned int indentation, bool startIndent = false) const;
		
	};
}