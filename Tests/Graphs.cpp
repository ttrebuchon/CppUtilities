#include <QUtils/Graphs/v2/Graph.h>
#include "Tests_Helpers.h"


#include <cmath>

using namespace QUtils::Graphs;

template <class T>
using RawPtr = T*;

DEF_TEST(Graphs)
{
	{
		Graph<double> g;
		g.createRoot(4);
		g.addRoot(std::make_shared<Node<double>>(8));
		for (auto n : g)
		{
			assert_ex(n->value == 4 || n->value == 8);
		}
	}
	
	{
		auto n = Node<double>::Create(9);
		n->value = 10;
		
		auto nc = (std::shared_ptr<const Node<double>>)n;
		
		auto n2 = Node<double>::Create(10);
		n->out.push_back(n2);
		assert_ex(n->out.size() == 1);
		assert_ex(n->out[0].out.lock() == n2);
		
		auto nodes = n->getDescendants();
		assert_ex(nodes.size() == 1);
	}
	
	{
		Graph<> g;
		
		
		auto n = Node<>::Create();
		
		auto nc = (std::shared_ptr<const Node<>>)n;
		
		auto n2 = Node<>::Create();
		n->out.push_back(n2);
		assert_ex(n->out.size() == 1);
		assert_ex(n->out[0].out.lock() == n2);
		
		auto nodes = n->getDescendants();
		assert_ex(nodes.size() == 1);
		
		
		g.addRoot(n);
		assert_ex(g.nodes.size() == 2);
		assert_ex(g.roots.size() == 1);
	}
	
	{
		Graph<std::string> g;
		
		
		auto n = Node<std::string>::Create("Hello");
		
		auto nc = (std::shared_ptr<const Node<std::string>>)n;
		
		auto n2 = Node<std::string>::Create(", world!");
		n->out.push_back(n2);
		assert_ex(n->out.size() == 1);
		assert_ex(n->out[0].out.lock() == n2);
		
		auto nodes = n->getDescendants();
		assert_ex(nodes.size() == 1);
		
		
		g.addRoot(n);
		assert_ex(g.nodes.size() == 2);
		assert_ex(g.roots.size() == 1);
		
		
		
		auto gt5 = g.where([](auto ptr)
		{
			return (ptr->value.length() > 5);
		});
		
		
		
		assert_ex(gt5.size() == 1);
	}
	
	{
		
		Graph<std::pair<double, double>, double> nn;
		auto root = nn.createRoot();
		assert_ex(root);
		auto root2 = nn.createRoot();
		assert_ex(root2);
		
		auto end = Node<std::pair<double, double>, double>::Create();
		
		
		auto notNull = [](auto& gr)
		{
			return gr.where([](auto ptr)
			{
				return ptr != NULL;
			});
		};
		
		assert_ex(notNull(nn).size() == nn.nodes.size());
		const int midCount = 3;
		
		for (int i = 0; i < midCount; ++i)
		{
			dout << "Creating mid node " << (i+1) << "\n";
			auto mid = Node<std::pair<double, double>, double>::Create();
			
			
			assert_ex(root);
			root->out.push_back(mid);
			auto& e1 = root->out.back();
			e1.value = static_cast<double>(rand())/RAND_MAX;
			
			root2->out.push_back(mid);
			auto& e2 = root2->out.back();
			e2.value = static_cast<double>(rand())/RAND_MAX;
			
			mid->out.push_back(end);
			auto& e3 = mid->out.back();
			e3.value = static_cast<double>(rand())/RAND_MAX;
			
			
			assert_ex(notNull(nn).size() == nn.nodes.size());
			
			nn.updateNodes();
			
			assert_ex(nn.nodes.size() == 2 + (i+1) + 1);
		}
		
		assert_ex(notNull(nn).size() == nn.nodes.size());
		assert_ex(nn.nodes.size() == 6);
		
		
		auto act = [](auto x) -> double
		{
			return static_cast<double>(1)/(1 + std::exp(-x));
		};
		
		
		root->value.first = 1;
		root2->value.first = 0;
		
		for (auto& e : root->out)
		{
			e.out.lock()->value.second += e.value*root->value.first;
		}
		
		for (auto& e : root2->out)
		{
			e.out.lock()->value.second += e.value*root2->value.first;
		}
		
		for (auto& e : root->out)
		{
			e.out.lock()->value.first = act(e.out.lock()->value.second);
			auto& endE = e.out.lock()->out[0];
			endE.out.lock()->value.second += endE.value*e.out.lock()->value.first;
		}
		
		end->value.first = act(end->value.second);
		
		dout << "Value: " << end->value.first << "\n";
		
		
		auto djikstra = nn.djikstraPath(root, end);
		assert_ex(djikstra.size() == 3);
		assert_ex(djikstra[0] == root);
		assert_ex(djikstra[2] == end);
	}
	
	{
		Graph<> g;
		std::vector<typename Node<>::wptr_t> path;
		typename Node<>::wptr_t wend;
		{
		auto root = g.createRoot();
		auto end = Node<>::Create();
		wend = end;
		auto mid1 = Node<>::Create();
		auto mid1_2 = Node<>::Create();
		auto mid2 = Node<>::Create();
		auto mid12 = Node<>::Create();
		
		root->out.push_back(mid1);
		root->out.push_back(mid2);
		
		mid1->out.push_back(mid1_2);
		
		mid1_2->out.push_back(mid12);
		mid2->out.push_back(mid12);
		
		mid12->out.push_back(end);
		
		
		int cost;
		auto djikstra = g.djikstraPath(root, end, &cost);
		assert_ex(cost == 3);
		assert_ex(djikstra.size() == 4);
		assert_ex(djikstra[0] == root);
		assert_ex(djikstra[1] == mid2);
		assert_ex(djikstra[2] == mid12);
		assert_ex(djikstra[3] == end);
		
		path.resize(djikstra.size());
		std::transform(djikstra.begin(), djikstra.end(), path.begin(), [](auto ptr)
		{
			return ptr;
		});
		
		g.updateNodes();
		}
		auto path2 = g.djikstraPath(g.roots[0], wend.lock());
		assert_ex(path2.size() == path.size());
		for (int i = 0; i < path.size(); ++i)
		{
			assert_ex(path[i].lock() == path2[i]);
		}
	}
	
	
	{
		const int count = 100;
		const int rCount = count*count/10;
		Graph<> g;
		std::vector<typename Node<>::ptr_t> nodes(count);
		
		for (int i = 0; i < count; ++i)
		{
			nodes[i] = Node<>::Create();
			
		}
		for (int i = 1; i < count; ++i)
		{
			nodes[i-1]->out.push_back(nodes[i]);
			
		}
		g.addRoot(nodes[0]);
		g.updateNodes();
		assert_ex(g.nodes.size() == count);
		
		
		
		for (auto i = 0; i < rCount; ++i)
		{
			int x = rand() % count;
			int y = rand() % count;
			if (x == y)
			{
				--i;
				continue;
			}
			
			nodes[x]->out.push_back(nodes[y]);
		}
		
		int cost;
		auto path = g.djikstraPath(nodes[0], nodes[count-1], &cost);
		dout << "Cost: " << cost << "\n";
		
		
		std::function<int(typename Node<>::ptr_t, std::map<typename Node<>::ptr_t, int>&)> checker;
		
		checker = [&](auto ptr, auto& checked) -> int
		{
			checked.insert({ptr, -1});
			int best = INT_MAX;
			
			for (auto& childEdge : ptr->out)
			{
				auto child = childEdge.out.lock();
				
				if (child == nodes[count-1])
				{
					checked[child] = 0;
					checked[ptr] = 1;
					return 1;
				}
				
				if (checked.count(child) <= 0)
				{
					auto val = checker(child, checked);
					if (val+1 < best && val >= 0)
					{
						best = val+1;
					}
				}
				else
				{
					if (checked[child]+1 < best && checked[child] >= 0)
					{
						best = checked[child]+1;
					}
				}
			}
			
			
			if (best == INT_MAX)
			{
				best = -1;
			}
			
			checked[ptr] = best;
			
			return best;
		};
		
		std::map<typename Node<>::ptr_t, int> nodeMap;
		
		int realCost = checker(nodes[0], nodeMap);
		dout << "Real Cost: " << realCost << "\n";
		assert_ex(realCost == cost);
		
		typedef typename Node<>::ptr_t Node_ptr;
		
		/*std::map<Node_ptr, std::map<Node_ptr, Node_ptr>> paths;
		
		for (auto node : g.nodes)
		{
			paths[node] = g.djikstraPaths(node);
			assert_ex(paths[node].size() == g.nodes.size());
		}*/
		
		
		
		
		
		
		
		
		
		
		std::set<typename Node<>::ptr_t> subsetNodes;
		
		subsetNodes.insert(nodes[0]);
		subsetNodes.insert(nodes[count-1]);
		while (subsetNodes.size() < count/10)
		{
			auto i = rand() % count;
			subsetNodes.insert(nodes[i]);
		}
		
		
		/*auto subset = g.subset(subsetNodes.begin(), subsetNodes.end());
		
		dout << "subset.nodes.size(): " << subset.nodes.size() << "\n";
		dout << "subsetNodes.size(): " << subsetNodes.size() << "\n";
		
		assert_ex(subset.nodes.size() == subsetNodes.size());*/
	}
	
	{
		Graph<> g;
		auto r = g.createRoot();
		auto tmp = r;
		typename Node<>::ptr_t h = NULL;
		size_t lastSize = 1;
		assert_ex(g.nodes.size() == 1);
		for (int i = 0; i < 100; ++i)
		{
			lastSize = g.nodes.size();
			auto n = Node<>::Create();
			size_t tmpLast = tmp->out.size();
			tmp->out.push_back(n);
			assert_ex(tmp->out.size() == tmpLast+1);
			assert_ex(tmp->out.back().out.lock() == n);
			g.updateNodes();
			assert_ex(g.nodes.size() == lastSize+1);
			tmp = n;
			if (i == 50)
			{
				h = tmp;
			}
		}
		
		std::vector<Node<>::ptr_t> vec = {r, h, tmp};
		auto paths = g.djikstraPaths(vec.begin(), vec.end());
		assert_ex(paths.count(r) > 0);
		assert_ex(paths.count(h) > 0);
		assert_ex(paths.count(tmp) > 0);
		dout << "Paths found\n";
		
		
		auto checkPath = [](auto& paths, auto start, auto end)
		{
			assert_ex(paths.count(start) > 0);
			std::list<Node<>::ptr_t> path;
			Node<>::ptr_t n = end;
			while (n != start)
			{
				path.push_front(n);
				if (paths.at(start).count(n) <= 0)
				{
					dout << "Missing for " << n << "\n";
					dout << "Size: " << paths.at(start).size() << "\n";
				}
				assert_ex(paths.at(start).count(n) > 0);
				n = paths.at(start).at(n);
			}
			path.push_front(n);
			
		};
		
		checkPath(paths, r, h);
		checkPath(paths, r, tmp);
		checkPath(paths, h, tmp);
		
		dout << "Paths check out\n";
		
		
		auto sub = g.subset(vec.begin(), vec.end());
		dout << sub.nodes.size() << "\n";
		assert_ex(sub.roots.size() == 1);
		assert_ex(sub.roots[0] != g.roots[0]);
		assert_ex(sub.roots[0]->out.size() == 1);
		assert_ex(sub.roots[0]->out.back().out.lock());
		assert_ex(sub.roots[0]->out.back().out.lock() != h);
		assert_ex(sub.roots[0]->out.back().out.lock()->out.size() == 1);
		assert_ex(sub.roots[0]->out.back().out.lock()->out.back().out.lock());
		assert_ex(sub.roots[0]->out.back().out.lock()->out.back().out.lock() != tmp);
		assert_ex(sub.roots[0]->out.back().out.lock()->out.back().out.lock()->out.size() == 0);
		
		assert_ex(sub.roots[0]->out.back().out.lock()->out.back().out.lock() != sub.roots[0]);
		
		assert_ex(sub.roots[0]->out.back().out.lock()->out.back().out.lock() != sub.roots[0]->out.back().out.lock());
		
		
		assert_ex(sub.nodes.size() == 3);
	}
	
	return true;
}