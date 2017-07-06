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
		
		
		/*Easy request2;
		request2.setOpt<Url>("https://www.reddit.com/.json");
		request2.setOpt(Header(true));
		std::stringstream ss;
		request2.setOpt(WriteStream(&ss));
		request2.perform();
		
		br() << ss.str() << std::endl;
		*/
	}
}
}