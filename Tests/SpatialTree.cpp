#include "../Tests_Helpers.h"
#include <QUtils/Spatial/SpatialTree.h>
#include <QUtils/World/Vector.h>


DEF_TEST(SpatialTree)
{
	using namespace QUtils::Spatial;
	
	typedef QUtils::World::Vector<float> Vec;
	
	{
		auto s = new SpatialTree<Vec, float>;
		s->test();
	}
	return true;
}