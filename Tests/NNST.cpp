#include "../Tests_Helpers.h"
#include "QUtils/NearestNeighborTree/NearestNeighborTree.h"
#include <cmath>
#include <climits>
#include <unordered_map>

template <typename ...T>
using NNT = QUtils::NearestNeighbor<T...>;

using std::vector;

struct Item
{
	double x;
	double y;
	int z;
	
	Item(double x, double y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

double dist(Item i1, Item i2)
{
	double dx, dy;
	int dz;
	dx = i2.x - i1.x;
	dy = i2.y - i1.y;
	dz = i2.z - i1.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double Test2();
#define TEST2_THRESHOLD 10

bool Test_NNST()
{
	Item i1 {4, 3, 2};
	Item i2 {0, 0, 0};
	Item i3 {2, 6, 10};
	
	auto tree = NNT<Item, double, double, int>(
	[](Item* e) {return e->x;},
	[](Item* e) {return e->y;},
	[](Item* e) {return e->z;}
	);
	
	const int count = 10000;
	std::unordered_map<Item*, Item*> closestItems;
	std::vector<Item*> items;
	items.reserve(count + 5);
	
	tree.dist = [](Item* i1, Item* i2) { return dist(*i1, *i2); };
	
	tree.insert(&i1);
	tree.insert(&i2);
	tree.insert(&i3);
	
	items.push_back(&i1);
	items.push_back(&i2);
	items.push_back(&i3);
	
	assert_ex(tree.size() == 3);
	
	
	
	
	
	Item goal(count/2, count/2, 5);
	
	
	
	double shortest_d = INT_MAX;
	Item* shortest = NULL;
	dout << "Building tree..." << endl;
	vector<Item*> goals;
	int goalCount = std::min(10000, count);
	for (int i = tree.size(); i < count; i++)
	{
		double x = count*((double)rand())/RAND_MAX;
		double y = count*((double)rand())/RAND_MAX;
		int z = rand() % 10;
		Item* newItem = new Item(x, y, z);
		items.push_back(newItem);
		tree.insert(newItem);
		if (dist(*newItem, goal) < shortest_d)
		{
			shortest_d = dist(*newItem, goal);
			shortest = newItem;
		}
		if (goals.size() < goalCount)
		{
			goals.push_back(newItem);
		}
	}
	dout << "Verifying tree..." << endl;
	assert_ex(tree.size() == count);
	assert_ex(tree.size() == items.size());
	dout << "Traversing..." << endl;
	
	{
	static_assert(count > 1, "");
	double tmpDist;
	Item* current = nullptr;
	double distance = INT_MAX;
	for (auto i1 : items)
	{
		distance = INT_MAX;
		current = nullptr;
		for (auto i2 : items)
		{
			if (i2 == i1)
			{
				continue;
			}
			tmpDist = dist(*i1, *i2);
			if (tmpDist < distance)
			{
				current = i2;
				distance = tmpDist;
			}
		}
		assert_ex(current != nullptr);
		closestItems[i1] = current;
		current = nullptr;
	}
	for (auto item : items)
	{
		auto results = tree.traverse(item, 2);
		assert_ex(results.size() == 2);
		auto minDist = dist(*item, *closestItems[item]);
		auto d1 = dist(*item, *results.front());
		auto d2 = dist(*item, *results.back());
		
		if (!((d1 == minDist) || (d2 == minDist)))
		{
			Item* it = item;
			dout << "Item: <" << it->x << ", " << it->y << ", " << it->z << "> Dist: " << dist(*item, *it) << "\n";
			
			it = results.front();
			dout << "Result 1: <" << it->x << ", " << it->y << ", " << it->z << "> Dist: " << dist(*item, *it) << "\n";
			
			it = results.back();
			dout << "Result 2: <" << it->x << ", " << it->y << ", " << it->z << "> Dist: " << dist(*item, *it) << "\n";
			
			it = closestItems[item];
			dout << "Closest Item: <" << it->x << ", " << it->y << ", " << it->z << "> Dist: " << dist(*item, *it) << "\n";
		}
		
		
		assert_ex((d1 == minDist) || (d2 == minDist));
		/*
		if (results.front() != item)
		{
			assert_ex(results.back() == item);
			assert_ex(results.front() == closestItems[item]);
		}
		else
		{
			assert_ex(results.front() == item);
			assert_ex(results.back() == closestItems[item]);
		}*/
	}
	}
	
	
	auto closest = tree.traverse(&goal, 1);
	
	for (Item* it : closest)
	{
		dout << "(" << it->x << ", " << it->y << ", " << it->z << ")" << endl;
		dout << dist(*it, goal) << endl;
	}
	assert_ex(closest[0] == shortest);
	
	
	dout << "\n\n" << endl;
	//tree.insert(&goal);
	
	
	auto closest2 = tree.traverse(shortest, 4);
	
	for (Item* it : closest2)
	{
		dout << "(" << it->x << ", " << it->y << ", " << it->z << ")" << endl;
		dout << dist(*it, goal) << endl;
	}
	
	dout << "Actual shortest: " << shortest_d << endl;
	dout << "(" << shortest->x << ", " << shortest->y << ", " << shortest->z << ")" << endl;
	
	
	
	dout << "\n\n\n" << endl;
	
	
	
	
	dout << "Testing error using [" << goals.size() << "] values..." << endl;
	Item origin(0, 0, 0);
	double err = 0;
	int errCount = 0;
	double avgVal = 0;
	bool first = true;
	for (Item* it : goals)
	{
		auto results = tree.traverse(it, 4);
		double totalW = 0;
		double tX = 0, tY = 0, tZ = 0;
		for (auto result : results)
		{
			auto d = dist(*it, *result);
			if (d == 0)
			{
				continue;
			}
			
			tX += (result->x/d);
			tY += (result->y/d);
			tZ += ((double)result->z)/d;
			totalW += ((double)1)/d;
		}
		
		Item est(tX/totalW, tY/totalW, tZ/totalW);
		if (first)
		{
			first = false;
			dout << "Target:   \t(" << it->x << ", " << it->y << ", " << it->z << ")" << std::endl;
			dout << "Estimate:\t(" << est.x << ", " << est.y << ", " << est.z << ")" << std::endl;
		}
		double tmpErr = dist(est, *it);
		err += tmpErr;
		avgVal += dist(*it, origin);
		errCount++;
		
		//cout << errCount << ": " << tmpErr << endl;
		//cout << "(" << it->x << ", " << it->y << ", " << it->z << ") -> (" << est.x << ", " << est.y << ", " << est.z << ")" << endl;
	}
	
	dout << "Avg Error: " << err/errCount << endl;
	dout << "Avg Value: " << avgVal/errCount << endl;
	dout << "Relative Avg Error: " << (100*err)/avgVal << "%" << endl;
	if (count >= 5000)
	{
		assert_ex((100*err)/avgVal < 1);
	}
	
	auto test2Err = Test2();
	if (test2Err < 0)
	{
		test2Err *= -1;
	}
	dout << "Test 2 Error: " << test2Err << "%" << std::endl;
	
	return true;
}

















struct TestInput
{
	double x;
	double y;
	double z;
	
	TestInput(double x, double y, double z) : x(x), y(y), z(z) {}
};

double TestFunc(TestInput in)
{
	//f(x, y, z) = xyz
	auto x = in.x;
	auto y = in.y;
	auto z = in.z;
	return (x*x) + x*y + z;
}


double InDist(TestInput* in1, TestInput* in2)
{
	double dx, dy, dz;
	dx = in2->x - in1->x;
	dy = in2->y - in1->y;
	dz = in2->z - in1->z;
	
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double Test2()
{
	auto tree = NNT<TestInput, double, double, double>(
	[](TestInput* in) {return in->x;},
	[](TestInput* in) {return in->y;},
	[](TestInput* in) {return in->z;}
	);
	tree.dist = [](TestInput* i1, TestInput* i2) { return InDist(i1, i2); };
	
	
	
	int count = 100000;
	double xL = -50;
	double xU = 50;
	double yL = 0;
	double yU = 10;
	double zL = 1;
	double zU = 4.9;
	TestInput goal(0.51*(xU - xL) + xL, 0.51*(yU - yL) + yL, 0.51*(zU - zL) + zL);
	dout << "\n\nBuilding tree for test 2..." << endl;
	//vector<TestInput*> goals;
	for (int i = tree.size(); i < count; i++)
	{
		double x = (((double)rand())/RAND_MAX)*(xU - xL) + xL;
		double y = (((double)rand())/RAND_MAX)*(yU - yL) + yL;
		double z = (((double)rand())/RAND_MAX)*(zU - zL) + zL;
		TestInput* newItem = new TestInput(x, y, z);
		tree.insert(newItem);
	}
	
	auto results = tree.traverse(&goal, 10);
	
	double totalRes = 0;
	double totalW = 0;
	
	for (auto result : results)
	{
		auto d = tree.dist(&goal, result);
		if (d == 0)
		{
			continue;
		}
		
		totalRes += (TestFunc(*result))/d;
		totalW += ((double)1)/d;
	}
	
	double est = totalRes/totalW;
	dout << "Estimate: " << est << std::endl;
	double act = TestFunc(goal);
	dout << "Actual: " << act << std::endl;
	
	dout << "Difference: " << est - act << std::endl;
	double relErr = 100*(est - act)/act;
	dout << "Relative Error: " << relErr << "%" << std::endl;
	
	
	
	
	return relErr;
}