#include <QUtils/Network/Network.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <sstream>

using namespace curlpp::options;
using namespace curlpp;

namespace QUtils
{
namespace Network
{
	std::shared_ptr<curlpp::Cleanup> Curl::cleanPtr = NULL;
	
	
	void Curl::Init()
	{
		if (cleanPtr == NULL)
		{
			cleanPtr = std::make_shared<curlpp::Cleanup>();
		}
	}
}
}