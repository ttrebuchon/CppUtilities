#include "../Tests_Helpers.h"

#include <QUtils/Graphs/DependencyGraph.h>


DEF_TEST(Graphs_DependencyGraph)
{
	using namespace QUtils::Graphs;
	
	
	//DependencyGraph<> graph1;
	DependencyGraph<int> graph2;
	
	//graph1.push_back();
	graph2.push_back(5);
	return true;
	
}