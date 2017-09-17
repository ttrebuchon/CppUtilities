#include "../Tests_Helpers.h"

#include <QUtils/GUID/GUID.h>
#include <sstream>

#include <set>
#include <future>
#include <vector>


bool Test_GUID()
{
	QUtils::GUID id1 = QUtils::GUID::Create();
	dout << id1 << "\n";
	std::stringstream ss;
	ss << id1;
	assert_ex(to_string(id1) == to_string(id1));
	assert_ex(ss.str() == to_string(id1));
	
	
	QUtils::GUID id1_1 = id1;
	assert_ex(to_string(id1_1) == to_string(id1_1));
	assert_ex(id1 == id1_1);
	assert_ex(to_string(id1) == to_string(id1_1));
	
	assert_ex(id1 >= id1_1);
	assert_ex(id1 <= id1_1);
	assert_ex(id1_1 >= id1);
	assert_ex(id1_1 <= id1);
	assert_ex(!(id1 > id1_1));
	assert_ex(!(id1 < id1_1));
	assert_ex(!(id1 != id1_1));
	
	
	{
		const int count = 100000;//000;
		std::set<QUtils::GUID> ids;
		for (int i = 0; i < count; ++i)
		{
			if (i % (count/10) == 0)
			{
				dout << i << "/" << count << "(" << (100*i)/count << "%)\n";
			}
			QUtils::GUID id = QUtils::GUID::Create();
			auto str = to_string(id);
			assert_ex(QUtils::GUID::FromString(str) == id);
			ids.insert(id);
		}
		assert_ex(ids.size() == count);
		
		
		
		
		auto func = [](auto count) -> std::set<QUtils::GUID>
		{
			std::set<QUtils::GUID> ids;
			for (int i = 0; i < count; ++i)
			{
				QUtils::GUID id = QUtils::GUID::Create();
				auto str = to_string(id);
				assert_ex(QUtils::GUID::FromString(str) == id);
				ids.insert(id);
			}
			assert_ex(ids.size() == count);
			return ids;
		};
		
		std::vector<std::future<std::set<QUtils::GUID>>> futures;
		
		const int tCount = 10;
		for (int i = 0; i < tCount; ++i)
		{
			futures.push_back(std::async(std::launch::async, func, count/tCount));
		}
		
		dout << "Threads launched, joining..." << std::endl;
		for (int i = 0; i < futures.size(); ++i)
		{
			auto set = futures[i].get();
			dout << (i+1) << "/" << futures.size() << "\n";
			ids.insert(set.begin(), set.end());
		}
		
		assert_ex(ids.size() == 2*count);
		
		dout << 2*count << " GUIDs Tested!\n";
	}
	
	return true;
}