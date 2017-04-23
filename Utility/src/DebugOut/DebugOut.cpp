#include "DebugOut/DebugOut.h"

namespace Util
{
	
	DebugOut DebugOut::inst;
	bool DebugOut::disabled = false;
	std::ostream* DebugOut::out = &std::cerr;
	
	
}