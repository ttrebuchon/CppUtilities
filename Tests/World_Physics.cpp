#include "../Tests_Helpers.h"

#include <QUtils/World/Physics/Newtonian/Newtonian.h>
constexpr QUtils::World::Vector<double> testF()
{
	return QUtils::World::Vector<double>();
}

DEF_TEST(World_Physics)
{
	using namespace QUtils::World::Physics::Newtonian;
	
	Environment env;
	Particle part;
	
	
	QUtils::World::Vector<double> v = QUtils::World::Vector<double>{1, 2, 3};
	QUtils::World::Vector<float> v2 = {4, 5, 6};
	
	auto v3 = v + v2;
	dout << to_string(v3) << std::endl;
	
	QUtils::World::Vector<int> v4;
	v4 += v3;
	dout << to_string(v4) << std::endl;
	
	constexpr auto cv1 = testF();
	constexpr QUtils::World::Vector<double> cv2(1, 2, 3);
	
	static_assert(cv1 - cv2 + cv2 == cv1);
	
	QUtils::World::Vector<QUtils::World::Vector<double>> m1;
	m1.x.x = 1;
	
	dout << to_string(m1) << std::endl;
	
	return true;
}