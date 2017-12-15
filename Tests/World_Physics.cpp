#include "../Tests_Helpers.h"

#include <QUtils/World/Physics/Physics.h>
constexpr QUtils::World::Vector<double> testF()
{
	return QUtils::World::Vector<double>();
}

DEF_TEST(World_Physics)
{
	using namespace QUtils::World::Physics;
	
	
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
	
	
	
	
	
	{
		System<double> sys;
		sys.timescale = pow(10, -3);
		sys.env = std::make_shared<Environment<double>>();
		sys.env->gravity = pow(10, 11);
		auto part = std::make_shared<StandardParticle<double>>();
		sys.particles.push_back(part);
		
		
		sys.env->forces.push_back(std::make_shared<UniformGravity<double>>(Vec(0, -10, 0)));
		sys.env->forces.push_back(std::make_shared<MagneticFieldForce<double>>());
		sys.env->fields.push_back(std::make_shared<UniformMagnetic<double>>(Vec(10, 0, 0)));
		
		part->_mass = 1000;
		part->properties["charge"] = {-1000, 0, 0};
		
		auto part2 = std::make_shared<StandardParticle<double>>();
		sys.particles.push_back(part2);
		part2->position({1000, 20, 0});
		part2->_mass = 1;
		part2->properties["charge"] = {1, 0, 0};
		
		dout << "\n\n" << to_string(part->position()) << "\n";
		
		for (int i = 0; i < 10000; ++i)
		{
			sys.step();
			if (i % 1000 == 999)
			{
			dout << "\n\nTime: " << sys.ticks*sys.timescale << "s\n";
			dout << "P1: " << to_string(part->position()) << "\n\tv: " << to_string(part->velocity()) << "\n\tF: " << to_string(sys.forces.at(part)) << "\n";
			dout << "P2: " << to_string(part2->position()) << "\n\tv: " << to_string(part2->velocity()) << "\n\tF: " << to_string(sys.forces.at(part2)) << "\n\n";
			}
			
		}
		
	}
	
	
	return true;
}