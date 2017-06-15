#ifndef INCLUDED_UTIL_DEBUG_OUT_H
#define INCLUDED_UTIL_DEBUG_OUT_H

#include <iostream>

namespace Util
{
	class DebugOut
{
	static std::ostream* out;
	static DebugOut inst;
	static bool disabled;
	
	class NullBuffer : public std::streambuf
	{
		public:
		int overflow(int c)
		{
			return c;
		}
	};
	
	public:
	
	DebugOut()
	{
		#ifndef TEST_DEBUG
		Disable();
		#endif
	}
	
	static void Disable()
	{
		if (!disabled)
		{
		out = new std::ostream(new NullBuffer());
		disabled = true;
		}
	}
	
	static std::ostream& Out()
	{
		return *out;
	}
	
	
	
};
	
}


#endif