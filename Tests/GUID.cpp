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
		const int count = 10000;
		std::set<QUtils::GUID> ids;
		for (int i = 0; i < count; ++i)
		{
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
		
		for (int i = 0; i < futures.size(); ++i)
		{
			auto set = futures[i].get();
			ids.insert(set.begin(), set.end());
		}
		
		assert_ex(ids.size() == 2*count);
		
		dout << 2*count << " GUIDs Tested.\n";
	}
	
	{
		QUtils::GUID id1 = QUtils::GUID::Create();
		std::string str1 = to_string(id1);
		QUtils::GUID id1_1;
		id1_1 = QUtils::GUID::FromString(str1);
		assert_ex(id1 == id1_1);
		
		std::map<QUtils::GUID, std::string> ids;
		
		
		for (int i = 0; i < 10000; ++i)
		{
			QUtils::GUID id;
			id = QUtils::GUID::Create();
			std::string str = to_string(id);
			QUtils::GUID id_1 = QUtils::GUID::FromString(str);
			assert_ex(id == id_1);
			
			ids[id] = str;
		}
		
		for (auto pair : ids)
		{
			assert_ex(ids.at(QUtils::GUID::FromString(pair.second)) == pair.second);
			assert_ex(ids.at(pair.first) == pair.second);
		}
		
		dout << "GUID Serialization Tested.\n";
	}
	
	return true;
}