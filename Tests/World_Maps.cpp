#include "../Tests_Helpers.h"
#include <QUtils/World/World/All.h>
#include <vector>
#include <QUtils/NearestNeighborTree/NearestNeighborTree.h>


DEF_TEST(World_Maps)
{
	using namespace QUtils::World;
	auto world = new World_t;
	
	auto m1_func = [](auto x, auto y)
	{
		return Vector<float>(x, y, sin(x)*sin(y) + x + y);
	};
	
	auto m1 = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(cos(x)*sin(y) + 1, sin(x)*cos(y) + 1, 0);
	});
	
	auto mFlat = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(1, 1, 0);
	});
	
	auto mSlope = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(1, 0, 0);
	});
	
	{
		Vector<float> pos = {0, 0, 0};
		Vector<float> dir = {1, 1, 1};
		dout << "Slant 1: " << m1->slant(pos, dir) << "\n";
		dout << "Slant Flat: " << mFlat->slant(pos, dir) << "\n";
		dout << "Sloped Slant: " << mSlope->slant(pos, dir) << "\n";
		
		Vector<float> dir2 = {1, 1, 0};
		assert_ex(mFlat->slant(pos, dir) == mFlat->slant(pos, dir2));
		assert_ex(mSlope->slant(pos, dir) == mSlope->slant(pos, dir2));
		assert_ex(m1->slant(pos, dir) == m1->slant(pos, dir2));
	}
	
	{
		std::vector<Vector<float>> meshPoints;
		meshPoints.reserve(101*101);
		const float width = 100;
		const float height = 100;
		for (float x = 0; x <= width; x += width/100)
		{
			for (float y = 0; y <= height; y += height/100)
			{
				meshPoints.push_back(m1_func(x, y));
			}
		}
		meshPoints.shrink_to_fit();
		
		QUtils::NearestNeighbor<Vector<float>, float, float, float> tree(
		[](auto v)
		{
			return v->x;
		},
		[](auto v)
		{
			return v->y;
		},
		[](auto v)
		{
			return v->z;
		});
		tree.dist = [](auto v1, auto v2)
		{
			return (*v1 - *v2).value();
		};
		
		std::random_shuffle(meshPoints.begin(), meshPoints.end());
		
		
		int count = 0;
		for (auto& v : meshPoints)
		{
			tree.insert(&v);
			if (count++ > 10000)
			{
				//break;
			}
		}
		dout << count << "\n";
		assert_ex(tree.size() == count);
		
		dout << "Target: " << to_string(meshPoints[0]) << "\n\n";
		
		auto closest = tree.traverse(&meshPoints[0], 30);
		for (auto& close : closest)
		{
			dout << to_string(*close) << "\n";
		}
	}
	
	return true;
}