#include <QUtils/Debug/DebugOut.h>

namespace QUtils
{
	
	DebugOut DebugOut::inst;
	bool DebugOut::disabled = false;
	std::ostream* DebugOut::out = &std::cerr;
	
	
}