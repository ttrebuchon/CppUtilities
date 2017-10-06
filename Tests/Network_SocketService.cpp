#include "Tests_Helpers.h"

#include <QUtils/Network/Service/Service.h>

void Test_TimeSrv();

DEF_TEST(Network_SocketService)
{
	Test_TimeSrv();
	
	return true;
}


void Test_TimeSrv()
{
	class TimeService : public QUtils::Network::Service
	{
		
	};
}