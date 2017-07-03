#include <QUtils/Network/Network.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;

namespace QUtils
{
namespace Network
{
	void Test()
	{
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt<Url>("www.google.com");
		request.perform();
	}
}
}