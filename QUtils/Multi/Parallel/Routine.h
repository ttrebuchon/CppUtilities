#pragma once

#include <QUtils/Types/Functions.h>

namespace QUtils
{
namespace Multi
{
	class Routine
	{
		protected:
		
		public:
		
		
		template <class... Args>
		std::vector<std::shared_ptr<Job>> execute(Args...);
		
	};
	
	template <class Ret, class ...Args>
	class ARoutine : public Routine
	{
		
	};
}
}