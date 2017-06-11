#include "../Tests.h"
#include <clips.h>

bool Testing::CLIPS()
{
	void* theEnv = CreateEnvironment();
	
	EnvBuild(theEnv, "(assert (mother Jill Tom))");
	DATA_OBJECT OBJ;
	EnvEval(theEnv, "(assert (mother Jill Bill))", &OBJ);
	auto str = EnvAssertString(theEnv, "(father Tim Bill)");
	EnvCreateFact(theEnv, str);
	
	
	//DestroyEnvironment(theEnv);
	return true;
}