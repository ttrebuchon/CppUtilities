#include <QUtils/Multi/Task.h>

namespace QUtils { namespace Multi {
	
	namespace Helpers
	{
		template <>
		std::tuple<> FutureHelper::call(std::tuple<>&)
		{
			return std::tuple<>();
		}
	}
}
}