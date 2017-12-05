#include "Tests_Helpers.h"
#include <QUtils/Reddit/Reddit.h>
#include <QUtils/Network/Utilities.h>

DEF_TEST(Reddit)
{
	using namespace QUtils;
	
	Reddit::RedditSystem* sys = new Reddit::GenericRedditSystem<>(Network::getPage);
	
	
	auto gaming = sys->subreddit("Gaming");
	//auto tAll = gaming->getTopAll();
	
	dout << gaming->display_name() << std::endl;
	dout << gaming ->name() << std::endl;
	
	auto link1 = sys->link("7hgmrf");
	
	dout << link1->over_18() << std::endl;
	assert_ex(link1->subreddit_name() == "gaming");
	dout << link1->subreddit_id() << " --- " << gaming->id() << std::endl;
	assert_ex(link1->subreddit_id() == gaming->id());
	assert_ex(link1->subreddit() == gaming);
	
	
	delete sys;
	
	return true;
}