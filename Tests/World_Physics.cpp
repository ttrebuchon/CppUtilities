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
	
	
	using namespace QUtils::World;
	
	{
	
	Vector<double> v(1, 1, 0);
	Vector<double> v2(1, 1, 0);
	auto v3 = v.cross(v2);
	assert_ex(v3.x == 0);
	assert_ex(v3.y == 0);
	assert_ex(v3.z == 0);
	
	static_assert(Vector<double>(1, 1, 0).cross(Vector<double>(1, 1, 0)) == Vector<double>(0, 0, 0), "");
	
	v2.x = -1;
	v3 = v.cross(v2);
	assert_ex(v3.x == 0);
	assert_ex(v3.y == 0);
	assert_ex(v3.z == 2);
	
	static_assert(Vector<double>(1, 1, 0).cross(Vector<double>(-1, 1, 0)) == Vector<double>(0, 0, 2), "");
	
	}
	
	{
	
	Vector<double> v(1, 1, 0);
	Vector<double> v2(1, 1, 0);
	auto d = v.dot(v2);
	assert_ex(d == 2);
	
	static_assert(Vector<double>(1, 1, 0).dot(Vector<double>(1, 1, 0)) == 2, "");
	
	v2.x = -1;
	d = v.dot(v2);
	assert_ex(d == 0);
	
	static_assert(Vector<double>(1, 1, 0).dot(Vector<double>(-1, 1, 0)) == 0, "");
	
	}
	
	typedef Vector<double> Vec;
	
	{
		Vec v(1, 0, 0);
		assert_ex(v.value() == 1);
		static_assert(Vec(1, 0, 0).magnitude() == 1);
		static_assert(Vec(1, 0, 0).value() == 1);
		
		
	}
	
	
	return true;
}