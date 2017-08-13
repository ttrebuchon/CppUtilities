#include <QUtils/Network/Network.h>
#include <QUtils/Exception/NotAvailable.h>

#ifdef QUTILS_HAS_CURL
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#endif

#include <sstream>

#ifdef QUTILS_HAS_CURL
using namespace curlpp::options;
using namespace curlpp;
#endif

namespace QUtils
{
namespace Network
{
	#ifdef QUTILS_HAS_CURL
	std::shared_ptr<curlpp::Cleanup> Curl::cleanPtr = NULL;
	#endif
	
	void Curl::Init()
	{
		#ifdef QUTILS_HAS_CURL
		if (cleanPtr == NULL)
		{
			cleanPtr = std::make_shared<curlpp::Cleanup>();
		}

		#else
		throw NotAvailableException().File(__FILE__).Line(__LINE__);
		#endif
	}
}
}