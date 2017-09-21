#include <QUtils/CodeGen/Generator/Nodes/CVQualifiers.h>

#include <QUtils/CodeGen/Generator/Node.h>


namespace QUtils::CodeGen
{
	void CVQualifiers::clone(CVQualifiers* ptr) const
	{
		ptr->isConst = isConst;
		ptr->isConstexpr = isConstexpr;
		ptr->isExtern = isExtern;
		ptr->isMutable = isMutable;
		ptr->isStatic = isStatic;
		ptr->isThread_Local = isThread_Local;
		ptr->isVirtual = isVirtual;
		ptr->isVolatile = isVolatile;
	}
	
	
	std::string CVQualifiers::toString(const unsigned int indentation, bool startIndent) const
	{
		std::string s;
		if (startIndent)
		{
			s = Helpers::indent(indentation);
		}
		
		
		if (isExtern)
		{
			s += "extern ";
		}
		if (isConstexpr)
		{
			s += "constexpr ";
		}
		if (isVirtual)
		{
			s += "virtual ";
		}
		if (isStatic)
		{
			s += "static ";
		}
		if (isMutable)
		{
			s += "mutable ";
		}
		if (isThread_Local)
		{
			s += "thread_local ";
		}
		if (isVolatile)
		{
			s += "volatile ";
		}
		if (isConst)
		{
			s += "const ";
		}
		
		if (s.length() > 0)
		{
			return s.substr(0, s.length()-1);
		}
		else
		{
			return s;
		}
	}
	
}