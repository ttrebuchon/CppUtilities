#include "Tests_Helpers.h"

#include <memory>
#include <cmath>
#include <QUtils/Graphs/v2/Graph.h>

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
		
		dout << "Value: " << end->value.second << "\n";
		
	}
	
	return true;
}