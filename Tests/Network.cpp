#include "../Tests_Helpers.h"
#include <QUtils/Network/Network.h>
#include <json/json.hpp>

using json = nlohmann::json;


bool Test_Network()
{
	QUtils::Network::Test(dout);
	
	
	return true;
}