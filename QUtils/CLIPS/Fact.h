#pragma once

#include <Clips/clips.h>

namespace Util
{
namespace Clips
{
	class Fact
	{
		private:
		Fact();
		void* env;
		::fact* fact;
		public:
		Fact(void* env, ::fact* fact);

		~Fact();

		long long index() const
		{
			return fact->factIndex;
		}
		

		bool retract();
	};
	
	
}
}