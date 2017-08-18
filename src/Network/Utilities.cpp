#include <QUtils/Network/Utilities.h>
#include <QUtils/Exception/NotImplemented.h>
#include <sstream>
#include <fstream>

#ifdef QUTILS_HAS_CURL
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

using namespace curlpp::options;
using namespace curlpp;

#else

#include <QUtils/Exception/NotAvailable.h>

#define NOT_AVAIL_MSG "The Network module requires libcurl"

#endif

namespace QUtils::Network
{
	#ifdef QUTILS_HAS_CURL
	void setupRequest(curlpp::Easy& request)
	{
		request.setOpt<FollowLocation>(true);
		request.setOpt<Timeout>(5000);
	}
	#endif
	
	std::string getPage(const std::string url)
	{
		#ifdef QUTILS_HAS_CURL
		curlpp::Easy request;
		setupRequest(request);
		request.setOpt<Url>(url);
		
		std::stringstream ss;
		request.setOpt<WriteStream>(&ss);
		request.perform();
		return ss.str();
		#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
		#endif
	}
	
	bool savePage(const std::string url, const std::string path)
	{
		#ifdef QUTILS_HAS_CURL
		curlpp::Easy request;
		setupRequest(request);
		request.setOpt<Url>(url);
		
		std::ofstream file(path);
		if (!file.is_open())
		{
			return false;
		}
		request.setOpt<WriteStream>(&file);
		request.perform();
		file.close();
		return true;
		#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
		#endif
	}
	
	bool savePage(const std::string url, const std::string path, bool includeLinks)
	{
		#ifdef QUTILS_HAS_CURL
		if (!includeLinks)
		{
			return savePage(url, path);
		}
		throw NotImp();
		#else
		throw FeatureNotAvailableException().Msg(NOT_AVAIL_MSG);
		#endif
	}
}