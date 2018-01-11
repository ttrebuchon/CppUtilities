#include "../Tests_Helpers.h"
#include <QUtils/World/World/All.h>
#include <vector>
#include <QUtils/Types/CompilerPrint.h>
#include <iomanip>
#include <QUtils/World/World/Maps/Maps.h>

template <class T>
typename QUtils::World::Maps::Mesh<T>::Ptr createMesh(const std::function<T(T, T)>, T xmin, T xmax, T ymin, T ymax);

void test_EffectSet();
void test_Instances(QUtils::World::World_t*);

DEF_TEST(World_World)
{
	using namespace QUtils::World;
	test_EffectSet();
	
	
	auto world = new World_t;
	
	auto mFlat = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(1, 1, 0);
	});
	
	auto inst = Instance::Create(world, mFlat);
	
	//auto ent = Entity::Create(world);
	assert_ex(world->go(10s) == 10s);
	auto goFuture = world->goAsync(5s);
	assert_ex(goFuture.get() == 5s);
	assert_ex(world->go(WorldClock::duration(1000)) == 1s);
	
	
	test_Instances(world);
	
	
	return true;
}



void test_EffectSet()
{
	using namespace QUtils::World;
	
	class Eff : public Effect
	{
		public:
		int x;
		Timespan t;
		
		Timespan time() const
		{
			return t;
		}
	};
	
	auto e1 = std::make_shared<Eff>();
	auto e2 = std::make_shared<Eff>();
	e1->x = 0;
	e2->x = 1;
	
	assert_ex(e1 != e2);
	
	EffectSet es;
	es.insert(e1);
	assert_ex(es.size() == 1);
	es.insert(e1);
	assert_ex(es.size() == 1);
	es.insert(e2);
	assert_ex(es.size() == 2);
	
	
	es.clear();
	e1->t = Timespan(Clock::now(), 100s);
	e2->t = Timespan(Clock::now(), 10s);
	es.insert(e1);
	assert_ex(es.size() == 1);
	es.insert(e1);
	assert_ex(es.size() == 1);
	es.insert(e2);
	assert_ex(es.size() == 2);
	
	for (auto& e : es)
	{
		assert_ex(e == e2);
		break;
	}
}

void test_Instances(QUtils::World::World_t* world)
{
	using namespace QUtils::World;
	typedef float U;
	
	
	auto mesh = createMesh<U>([](auto x, auto y)
	{
		return x + y;
	}, 0, 100, 0, 100);
	
	assert_ex(mesh != nullptr);
	mesh->calculateNormals();
	
	auto map = Maps::MeshMap<U>::Create(mesh);
	assert_ex(map != nullptr);
	
	Vector<U> target(1, 1, 0);
	Vector<U> closestVert;
	auto closestFace = map->mesh->closestFace(target, &closestVert);
	dout << "Closest Vertex: " << to_string(closestVert) << "\n";
	assert_ex(closestFace != nullptr);
	
	Vector<U> closestPt = target - ((target - closestVert).dot(closestFace->norm()))*closestFace->norm();
	
	dout << "Closest Point: " << to_string(closestPt) << std::endl;
	
	
}





template <class T>
typename QUtils::World::Maps::Mesh<T>::Ptr createMesh(const std::function<T(T, T)> func, T xmin, T xmax, T ymin, T ymax)
{
	typedef QUtils::World::Vector<T> Vec;
	
	std::list<std::list<Vec>> faces;
	std::list<Vec> lastRow;
	std::list<Vec> row;
	for (T x = xmin; x <= xmax; ++x)
	{
		faces.emplace_back();
		auto& f = faces.back();
		for (T y = ymin; y <= ymax; ++y)
		{
			row.push_back(Vec{x, y, func(x, y)});
		}
		
		
		
		for (auto it = lastRow.rbegin(); it != lastRow.rend(); ++it)
		{
			f.push_back(*it);
		}
		lastRow = row;
		for (auto& p : row)
		{
			f.push_back(p);
		}
		row.clear();
	}
	
	
	return QUtils::World::Maps::Mesh<T>::FromPoints(faces);
}