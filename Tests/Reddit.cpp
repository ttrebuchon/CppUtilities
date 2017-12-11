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
	
	auto links = gaming->getListing();
	dout << "Retrieved!\n";
	for (auto link : *links)
	{
		dout << link << "\n";
		dout << "\t" << link->name() << "\n";
		dout << "\t" << link->permalink() << "\n";
	}
	
	dout << "[\n" << links->before() << "\n" << links->after() << "\n" << links->modhash() << "\n]\n";
	
	
	
	dout << "Checking duplicate links...\n";
	std::set<Reddit::Link*> linksSet(links->begin(), links->end());
	{
	auto len1 = linksSet.size();
	auto links2 = gaming->getListing(5);
	
	for (auto link : *links2)
	{
		linksSet.insert(link);
	}
	assert_ex(linksSet.size() == len1);
	}
	
	/*std::set<Reddit::Account*> accounts;
	for (auto link : *links)
	{
		accounts.insert(link->author());
	}
	
	for (auto auth : accounts)
	{
		dout << auth->name() << "\n";
		dout << auth->has_verified_email() << "\n";
	}*/
	
	auto link2 = links->front();
	
	auto comments2 = link2->comments();
	
	int comm2_len = 0;
	for (auto com : *comments2)
	{
		dout << com << "\n\t" << com->name() << "\n";
		++comm2_len;
	}
	
	dout << "\n\nLen: " << comm2_len << "\n";
	
	dout << "Loading more...\n";
	
	comm2_len = 0;
	int loaded = comments2->loadMore(true);
	dout << loaded << " more loaded\n\n\n";
	
	
	std::set<Reddit::Comment*> searched, toSearch;
	
	for (auto com : *comments2)
	{
		toSearch.insert(com);
	}
	
	search:
	
	for (auto it = toSearch.begin(); it != toSearch.end();)
	{
		auto pcom = *it;
		toSearch.erase(it);
		searched.insert(pcom);
		pcom->replies()->loadMore(true);
		bool added = false;
		for (auto com : *pcom->replies())
		{
			if (toSearch.count(com) <= 0 && searched.count(com) <= 0)
			{
				toSearch.insert(com);
				added = true;
			}
		}
		
		searched.insert(pcom);
		it = toSearch.begin();
	}
	
	for (auto it = searched.begin(); it != searched.end();)
	{
		if ((*it)->replies()->canLoadMore())
		{
			toSearch.insert(*it);
			it = searched.erase(it);
		}
		else
		{
			++it;
		}
	}
	
	if (toSearch.size() > 0)
	{
		goto search;
	}
	
	comm2_len = searched.size();
	
	dout << "\n\nLen: " << comm2_len << "\n";
	
	dout << "Total Len: " << link2->num_comments() << "\n\n";
	
	for (auto comment : searched)
	{
		assert_ex(!comment->replies()->canLoadMore());
	}
	
	
	if (links)
	{
		delete links;
	}
	delete sys;
	
	return true;
}