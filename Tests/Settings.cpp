#include "../Tests_Helpers.h"
#include <QUtils/Settings.h>

DEF_TEST(Settings)
{
	using namespace QUtils;
	
	const std::string val1 = "Val1";
	const std::string val1_2 = "Val1.2";
	Settings::Default->set("Key1", val1);
	assert_ex(Settings::Default->get("Key1") == val1);
	
	
	Settings::Default->save();
	assert_ex(Settings::Default->get("Key1") == val1);
	Settings::Default->set("Key1", val1_2);
	assert_ex(Settings::Default->get("Key1") == val1_2);
	Settings::Default->reload();
	assert_ex(Settings::Default->get("Key1") == val1);
	
	Settings::Default->set("Key1", val1_2);
	assert_ex(Settings::Default->get("Key1") == val1_2);
	Settings::Default->save();
	assert_ex(Settings::Default->get("Key1") == val1_2);
	
	
	
	
	
	Settings::Default->set("Key2", 1);
	Settings::Default->save();
	assert_ex(Settings::Default->get("Key2") == "1");
	
	Settings::Default->set("Key2", 1.64);
	assert_ex(Settings::Default->get("Key2") == "1.64");
	assert_ex(Settings::Default->get<double>("Key2") == 1.64);
	
	Settings::Default->reload();
	assert_ex(Settings::Default->get<int>("Key2") == 1);
	assert_ex(Settings::Default->get("Key2") == "1");
	
	
	Settings::Default->set("Key2", 1.64);
	
	return true;
}