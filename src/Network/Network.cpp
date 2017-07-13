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
	void Test(std::ostream& dout)
	{
		auto br = [&] () -> std::ostream& {
			return (dout << "---------------------" << "\n\n\n\n\n" << "---------------------" << "\n");
		};
		
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		request.setOpt<Url>("http://www.reddit.com/.json");
		request.perform();
		
		br() << std::flush;
		
		dout << "\n\n\n\n" << "\"" << curlpp::options::Url("www.reddit.com/.json") << "\"" << std::endl;
		
		br();
		//dout << request << std::endl;
		
		Url rUrl;
		request.getOpt(rUrl);
		
		dout << rUrl.getValue() << std::endl;
		
		dout << curlpp::infos::ResponseCode::get(request) << std::endl;
		dout << curlpp::infos::EffectiveUrl::get(request) << std::endl;
		
		Easy request2;
		request2.setOpt<Url>("https://www.reddit.com/.json");
		request2.setOpt(Header(true));
		std::stringstream ss;
		request2.setOpt(WriteStream(&ss));
		try
		{
		request2.perform();
		}
		catch (std::exception& ex)
		{
			dout << ex.what() << std::endl;
		}
		
		br() << ss.str() << std::endl;
		
		
		auto tryRequest = [&dout](std::string url, bool printInfo = true, bool followRedirect = true) -> std::string
		{
			Easy request;
			std::stringstream ss;
			request.setOpt<FollowLocation>(followRedirect);
			
			request.setOpt<Url>(url);
			request.setOpt<WriteStream>(&ss);
			
			try
			{
				request.perform();
			}
			catch (std::exception& ex)
			{
				ss << ex.what();
			}
			
			if (printInfo)
			{
				dout << "Effective URL: " <<  curlpp::infos::EffectiveUrl::get(request) << std::endl;
				
				dout << "Response Code: " << curlpp::infos::ResponseCode::get(request) << std::endl;
			}
			
			return ss.str();
		};
		
		
		
		const std::string annaURL = "http://testing.project-anna.com/";
		dout << "Trying " << annaURL << "\n";
		request2.setOpt<Url>(annaURL);
		request2.setOpt<FollowLocation>(true);
		request2.setOpt<Header>(false);
		
		try
		{
			request2.perform();
			dout << request2 << std::endl;
		}
		catch (std::exception& ex)
		{
			dout << ex.what() << "\n";
		}
		
		dout << "sstream: \n";
		br() << ss.str() << std::endl;
		
		dout << "Effective URL: " <<  curlpp::infos::EffectiveUrl::get(request2) << std::endl;
		
		dout << "Response Code: " << curlpp::infos::ResponseCode::get(request2) << std::endl;
		
		br() << "Trying lambda request for \"" << annaURL << "\"\n";
		br() << tryRequest(annaURL) << std::endl;
		
		
		br() << tryRequest("http://testing.project-anna.com/Services/api/Web/SessionsCount") << std::endl;
		
	}
}
}