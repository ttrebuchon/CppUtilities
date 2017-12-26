#include "../Tests_Helpers.h"
#include <QUtils/World/World/All.h>
#include <vector>
#include <QUtils/Types/CompilerPrint.h>

void test_EffectSet();

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
	
	auto ent = Entity::Create(world);
	
	if (world)
	{
		delete world;
	}
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
}