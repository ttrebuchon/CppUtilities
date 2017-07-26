#pragma once
#include <memory>

namespace curlpp
{
	class Cleanup;
}

namespace QUtils
{
namespace Network
{
	class Curl
	{
		static std::shared_ptr<curlpp::Cleanup> cleanPtr;
		public:
		static void Init();
	};
}
}