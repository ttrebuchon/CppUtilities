#include <QUtils/CLIPS/Fact.h>
#include <iostream>

namespace QUtils
{
namespace Clips
{
	Fact::Fact(void* env, ::fact* fact) : env(env), fact(fact)
	{
		EnvIncrementFactCount(env, fact);
	}


	Fact::~Fact()
	{
		if (fact)
		{
			EnvDecrementFactCount(env, fact);
			ReturnFact(env, fact);
		}
	}
	
	
	
	bool Fact::retract()
	{
		if (!fact)
			return false;
		return EnvRetract(env, fact);
	}
	
}
}