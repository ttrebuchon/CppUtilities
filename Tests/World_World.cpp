#include "../Tests_Helpers.h"
#include <QUtils/World/World/All.h>
#include <vector>
#include <QUtils/Types/CompilerPrint.h>
#include <iomanip>
#include <QUtils/World/World/Maps/Maps.h>

template <class T>
typename QUtils::World::Maps::Mesh<T>::Ptr createMesh(const std::function<T(T, T)>, T xmin, T xmax, T ymin, T ymax);

typename QUtils::World::Actor::Ptr createTestActor(QUtils::World::World_t*);

void test_EffectSet();
void test_Instances(QUtils::World::World_t*);


void printFace(auto f);

DEF_TEST(World_World)
{
	using namespace QUtils::World;
	test_EffectSet();
	
	
	auto world = new World_t;
	
	auto mFlat = Maps::FunctionalMap<double>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<double>(1, 1, 0);
	});
	
	auto inst = Instance::Create(world, mFlat);
	
	world->resumed += []()
	{
		dout << "World Resumed." << std::endl;
	};
	
	world->paused += []()
	{
		dout << "World Paused." << std::endl;
	};
	
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
	
	auto w = new World_t;
	
	class Eff : public Effect
	{
		protected:
		virtual void activate(Entity::Ptr, bool& remove)
		{
			remove = false;
		}
		
		public:
		Eff(World_t* world) : Effect(world)
		{}
		
		int x;
		Timespan t;
		
		Timespan time() const
		{
			return t;
		}
	};
	
	auto e1 = std::make_shared<Eff>(w);
	auto e2 = std::make_shared<Eff>(w);
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
	e1->t = Timespan(w->clock.now(), 100s);
	e2->t = Timespan(w->clock.now(), 10s);
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
	
	delete w;
}

void test_Instances(QUtils::World::World_t* world)
{
	using namespace QUtils::World;
	typedef double U;
	
	
	auto mesh = createMesh<U>([](auto x, auto y)
	{
		return x + y*x;
	}, 1, 100, 1, 100);
	
	assert_ex(mesh != nullptr);
	
	auto map = Maps::MeshMap<U>::Create(mesh);
	assert_ex(map != nullptr);
	
	Vector<U> closestPt;
	Vector<U> target(1, 1, 0);
	auto closestFace = map->mesh->closestFace(target, &closestPt);
	assert_ex(closestFace != nullptr);
	dout << "Closest Point: " << to_string(closestPt) << std::endl;
	
	auto inst = Instance::Create(world, map);
	assert_ex(inst != nullptr);
	
	auto actor1 = createTestActor(world);
	
	inst->addEntity(actor1);
	assert_ex(inst->entities.size() == 1);
	
	auto fmove = Effects::ForceMove::Create(world, Vector<double>(1,1,0), 1s, world->clock.now() + 10s);
	
	actor1->effects.insert(fmove);
	
	auto fmove2 = Effects::ForceMove::Create(world, Vector<double>(-1,-1,0), 1s, world->clock.now() + 10s);
	
	actor1->effects.insert(fmove2);
	
	
	world->go(fmove->time().duration());
	
	dout << to_string(actor1->pos()) << std::endl;
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
	
	
	auto m = QUtils::World::Maps::Mesh<T>::FromPoints(faces);
	m->triangulate();
	m->mergeLines();
	m->triangulate();
	bool cont = true;
	while (cont)
	{
		cont = false;
		for (auto f : m->faces)
		{
			assert_ex(f->perimeterSize() == 3);
			if (!(f->area() > 0))
			{
				m->mergeLines();
				m->triangulate();
				cont = true;
				break;
			}
		}
	}
	m->calculateNormals();
	
	return m;
}

typename QUtils::World::Actor::Ptr createTestActor(QUtils::World::World_t* world)
{
	using namespace QUtils::World;
	
	auto act = Actor::Create(world, Vector<double>{0,0,0});
	
	return act;
}


void printFace(auto f)
{
	auto e = f->edge;
	do
	{
		dout << to_string(e->vert->pos) << "\n";
		e = e->next;
	}
	while (e != f->edge);
	dout << std::flush;
}