#pragma once

#include <Clips/clips.h>

namespace QUtils
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