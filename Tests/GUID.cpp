#include "../Tests_Helpers.h"

#include <QUtils/GUID/GUID.h>
#include <sstream>


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
	
	return true;
}