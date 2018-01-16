#include "../Tests_Helpers.h"
#include <QUtils/World/World/All.h>
#include <vector>
#include <QUtils/NearestNeighborTree/NearestNeighborTree.h>


void TestMesh();


using namespace QUtils::World;

auto m1_func = [](auto x, auto y)
{
	return Vector<float>(x, y, sin(x)*sin(y) + x + y);
};

auto m2_func = [](auto x, auto y)
{
	return Vector<float>(x, y, 2);
};
	
/*auto mWavey_func = [](auto x, auto y)
{
	return Vector<float>(x, y, sin(atan(1)*x));
};*/



DEF_TEST(World_Maps)
{
	
	auto m1 = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(cos(x)*sin(y) + 1, sin(x)*cos(y) + 1, 0);
	});
	
	auto mFlat = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(0, 0, 0);
	});
	
	auto mSlope = Maps::FunctionalMap<float>::Create([](auto x, auto y, auto sz, auto ez)
	{
		return Vector<float>(1, 1, 0);
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
	
	
	TestMesh();
	return true;
}
	
	
void TestMesh()
{
	
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
	
	
	{
		std::vector<std::vector<Vector<float>>> points
		{
			{
				{-1,0,0},
				{0,0,0},
				{0,1,0},
				{-1,0,0},
				{0.5,0.5,1},
				{0,0,0},
				{0.5,0.5,1},
				{0,1,0}
			},
			{
				Vector<float>{0,0,0},
				Vector<float>{1,0,0},
				Vector<float>{1,1,0},
				Vector<float>{0,1,0},
				Vector<float>{0,0,0}
			},
			/*{
				Vector<float>{0,1,0},
				Vector<float>{0,0,0},
				Vector<float>{1,0,0}
			},
			{
				Vector<float>{1,0,0},
				Vector<float>{1,1,0},
				Vector<float>{0,1,0}
			},
			{
				Vector<float>{1,1,0},
				Vector<float>{0,1,0},
				Vector<float>{0,0,0}
			},*/
		};
		
		if (points[0].size() == 5)
		{
			assert_ex(points[0][0] == points[0][4]);
		}
		
		auto mesh = Maps::Mesh<double>::FromPoints(points);
		assert_ex(mesh->faces.size() == 2);
		
		/*for (auto& v : mesh->points)
		{
			dout << to_string(v.first) << "\n";
		}*/
		mesh.reset();
	}
	
	
	{
		std::vector<std::vector<Vector<float>>> points
		{
			{
				{0,0,0},
				{1,0,0},
				{1,1,0},
				{0,1,0},
			}
		};
		
		auto mesh = Maps::Mesh<double>::FromPoints(points);
		assert_ex(mesh->faces.size() == 1);
		
		auto v = mesh->points.at({0,0,0});
		assert_ex(v != nullptr);
		auto e = v->edge;
		assert_ex(e != nullptr);
		auto nextV = e->next->vert;
		assert_ex(nextV != nullptr);
		dout << "\n\n" << to_string(nextV->pos) << std::endl;
		
		if (nextV->pos != Vector<double>{1,0,0})
		{
			
			e = e->sym;
			assert_ex(e != nullptr);
			nextV = e->next->vert;
			assert_ex(nextV != nullptr);
			dout << "\n\n" << to_string(nextV->pos) << std::endl;
		}
		
		mesh->splitEdge(e, {0.5, 0, 0});
		
		assert_ex(e->next != nullptr);
		assert_ex(e->next->vert != nullptr);
		assert_ex(e->next->vert->pos == (Vector<double>{0.5,0,0}));
		assert_ex(e->next->vert->index == points[0].size());
		
		
		assert_ex(mesh->faces.size() == 1);
		auto face = mesh->faces.front();
		assert_ex(face->norm() == Vector<double>(0,0,1));
		
		mesh.reset();
	}
	
	auto printFace = [](auto f)
	{
		auto sEdge = f->edge;
		dout << to_string(sEdge->vert->pos) << "\n";
		auto ptr = sEdge->next;
		while (ptr != sEdge)
		{
			dout << to_string(ptr->vert->pos) << "\n";
			ptr = ptr->next;
		}
	};
	
	
	{
		std::vector<std::vector<Vector<float>>> points
		{
			{
				{0,0,0},
				{1,0,0},
				{1,1,0},
				{0,1,0},
			}
		};
		
		auto mesh = Maps::Mesh<double>::FromPoints(points);
		assert_ex(mesh->faces.size() == 1);
		
		/*auto len = mesh->edges.size();
		for (int i = 0; i < len; ++i)
		{
			mesh->splitEdge(mesh->edges[i], (mesh->edges[i]->next->vert->pos + mesh->edges[i]->vert->pos)/2);
		}
		
		assert_ex(mesh->vertices.size() == 2*len);*/
		
		
		dout << "Face: \n";
		printFace(mesh->faces.front());
		dout << std::flush;
		
		mesh->triangulate(mesh->faces.front());
		
		dout << "\n\nFace(s) After Tri: \n\n";
		for (auto face : mesh->faces)
		{
			printFace(face);
			dout << "\n";
		}
		dout << "Done\n\n" << std::flush;
		
		
		mesh.reset();
	}
	
	{
		std::vector<std::vector<Vector<float>>> points
		{
			//Bottom
			{
				{0,0,0},
				{1,0,0},
				{1,1,0},
				{0,1,0},
			},
			//Top
			{
				{0,0,1},
				{1,0,1},
				{1,1,1},
				{0,1,1},
			},
			//Front
			{
				{0,0,0},
				{1,0,0},
				{1,0,1},
				{0,0,1},
			},
			//Back
			{
				{0,1,0},
				{1,1,0},
				{1,1,1},
				{0,1,1},
			},
			//Left
			{
				{0,0,0},
				{0,0,1},
				{0,1,1},
				{0,1,0},
			},
			//Right
			{
				{1,0,0},
				{1,0,1},
				{1,1,1},
				{1,1,0},
			},
		};
		
		auto mesh = Maps::Mesh<double>::FromPoints(points);
		assert_ex(mesh->faces.size() == points.size());
		
		/*auto len = mesh->edges.size();
		for (int i = 0; i < len; ++i)
		{
			mesh->splitEdge(mesh->edges[i], (mesh->edges[i]->next->vert->pos + mesh->edges[i]->vert->pos)/2);
		}
		
		assert_ex(mesh->vertices.size() == 2*len);*/
		
		
		dout << "Face: \n";
		printFace(mesh->faces.front());
		dout << std::flush;
		
		
		mesh->triangulate();
		
		dout << "\n\nFace(s) After Tri: \n\n";
		for (auto face : mesh->faces)
		{
			printFace(face);
			dout << "\n";
		}
		dout << "Done\n\n" << std::flush;
		
		
		mesh.reset();
	}
	
	{
		const float width = 100;
		const float height = 100;
		const int xCount = 100;
		const int yCount = 100;
		std::vector<std::vector<Vector<float>>> meshPoints;
		meshPoints.reserve(xCount);
		std::list<Vector<float>>* lastRow = nullptr;
		for (float x = 0; x <= width; x += width/(xCount-1))
		{
			std::list<Vector<float>>* row = new std::list<Vector<float>>;
			for (float y = 0; y <= height; y += height/(yCount-1))
			{
				row->push_front(m1_func(x, y));
			}
			if (lastRow != nullptr)
			{
				meshPoints.emplace_back();
				std::vector<Vector<float>>& points = meshPoints.back();
				points = std::vector<Vector<float>>(lastRow->begin(), lastRow->end());
				points.reserve(lastRow->size() + row->size());
				for (auto& p : *row)
				{
					points.push_back(p);
				}
				delete lastRow;
			}
			lastRow = new std::list<Vector<float>>(row->rbegin(), row->rend());
			lastRow = row;
		}
		meshPoints.shrink_to_fit();
		
		
		auto mesh = Maps::Mesh<double>::FromPoints(meshPoints);
		assert_ex(mesh->faces.size() == meshPoints.size());
		
		
		
		
		
		/*dout << "\n\nFace(s) Before Tri: \n\n";
		int i = 0;
		for (auto face : mesh->faces)
		{
			if (i > 0)
			{
				break;
			}
			printFace(face);
			dout << "\n";
			++i;
		}
		dout << "Done\n\n" << std::flush;*/
		
		mesh->triangulate();
		
		/*dout << "\n\nFace(s) After Tri: \n\n";
		for (auto face : mesh->faces)
		{
			printFace(face);
			dout << "\n";
		}
		dout << "Done\n\n" << std::flush;*/
		
		dout << mesh->faces.size() << " vs. " << meshPoints.size() << "\n\n";
		assert_ex(mesh->faces.size() > meshPoints.size());
		
		dout << "First Face:\n";
		auto face = mesh->faces.front();
		printFace(face);
		dout << "\nNormal: " << to_string(face->norm()) << "\n";
		dout << "\n\n";
		
		
		mesh->mergeLines();
		mesh->triangulate();
		
		for (int i = 0; i < 2; ++i)
		{
			mesh->splitEdges();
			mesh->triangulate();
			mesh->mergeLines();
		}
		
		{
		long double totalA = 0;
		for (auto f : mesh->faces)
		{
			totalA += f->area();
		}
		dout << "\n\nTotal Area: " << totalA << std::endl;
		dout << "Average Area (Per Face): " << (totalA / mesh->faces.size()) << std::endl;
		}
		
		for (auto face : mesh->faces)
		{
			if (!(face->area() > 0))
			{
				auto vertices = face->vertices();
				assert_ex(vertices.size() > 0);
				for (auto v : vertices)
				{
					dout << "\t" << to_string(v->pos) << "\n";
				}
			}
			assert_ex(face->area() > 0);
		}
		
		
		mesh.reset();
	}
}