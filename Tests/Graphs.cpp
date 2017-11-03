#include "Tests_Helpers.h"

#include <memory>
#include <QUtils/Graphs/v2/Graph.h>

using namespace QUtils::Graphs;

template <class T>
using RawPtr = T*;

DEF_TEST(Graphs)
{
	{
		Graph<double> g;
		g.addRoot(4);
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
	}
	
	return true;
}