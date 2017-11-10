#pragma once
#include "Graph.h"
#include <list>
#include <vector>
#include <memory>
#include <set>
#include <queue>
#include <QUtils/Types/IsNull.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace Graphs {
	
	namespace Internal {
		
	template <class Node_t, class Cost_t, class Children_t>
	struct DjikstraPath_t
	{
		template <Cost_t(*CostFunc)(const Node_t&, const Node_t&), Children_t(*ChildFunc)(const Node_t&)>
		struct Type
		{
			std::map<Node_t, Cost_t> costs;
			std::map<Node_t, Node_t> paths;
			Node_t start, end;
			
			
			typedef std::tuple<Node_t, Node_t, Cost_t> QValue_t;
			
			struct Compare
			{
				std::greater<Cost_t> obj;
				bool operator()(const QValue_t& v1, const QValue_t& v2)
				{
					return obj(std::get<2>(v1), std::get<2>(v2));
				}
			};
			
			
			
			
			std::priority_queue<QValue_t, std::vector<QValue_t>, Compare> q;
			
			Type(Node_t start, Node_t end) : costs(), paths(), start(start), end(end), q()
			{
				
			}
			
			
			void go()
			{
				for (auto c : ChildFunc(start))
				{
					if (!Types::IsNull(c))
					{
						if (costs.count(c) <= 0)
						{
							q.emplace(start, c, CostFunc(start, c));
						}
					}
				}
				
				while (!q.empty() && paths.count(end) <= 0)
				{
					auto n = q.top();
					q.pop();
					if (costs.count(std::get<1>(n)) > 0)
					{
						continue;
					}
					
					auto cost = std::get<2>(n);
					costs[std::get<1>(n)] = cost;
					paths[std::get<1>(n)] = std::get<0>(n);
					if (std::get<1>(n) == end)
					{
						break;
					}
					
					auto childs = ChildFunc(std::get<1>(n));
					
					for (const auto& c : childs)
					{
						if (!Types::IsNull(c))
						{
							q.emplace(std::get<1>(n), c, cost + CostFunc(std::get<1>(n), c));
						}
					}
				}
				
			}
		};
		
	};
		
		
		
		
		
		
		
	template <class Node_t, class Cost_t, class Children_t>
	struct DjikstraMapper_t
	{
		template <Cost_t(*CostFunc)(const Node_t&, const Node_t&), Children_t(*ChildFunc)(const Node_t&)>
		struct Type
		{
			std::map<Node_t, std::map<Node_t, Cost_t>> costs;
			std::map<Node_t, std::map<Node_t, Node_t>> paths;
			std::set<Node_t> nodes;
			
			
			typedef std::tuple<Node_t, Node_t, Cost_t> QValue_t;
			
			struct Compare
			{
				std::greater<Cost_t> obj;
				bool operator()(const QValue_t& v1, const QValue_t& v2)
				{
					return obj(std::get<2>(v1), std::get<2>(v2));
				}
			};
			
			
			
			
			typedef std::priority_queue<QValue_t, std::vector<QValue_t>, Compare> Queue_t;
			
			Type(std::set<Node_t> nodes) : costs(), paths(), nodes(nodes)
			{
				
			}
			//Work on current target(s)
			void go(Node_t start)
			{
				Queue_t q;
				
				for (auto c : ChildFunc(start))
				{
					if (!Types::IsNull(c))
					{
						if (costs[start].count(c) <= 0)
						{
							q.emplace(start, c, CostFunc(start, c));
						}
					}
				}
				
				auto pathsRemaining = [](auto& paths, auto& nodes, auto& start)
				{
					for (auto n : nodes)
					{
						if (paths[start].count(n) <= 0)
						{
							return true;
						}
					}
					return false;
				};
				
				while (pathsRemaining(paths, nodes, start) && !q.empty())
				{
					auto n = q.top();
					q.pop();
					if (paths[start].count(std::get<1>(n)) > 0)
					{
						continue;
					}
					
					auto cost = std::get<2>(n);
					
					costs[start][std::get<1>(n)] = cost;
					paths[start][std::get<1>(n)] = std::get<0>(n);
					
					
					auto childs = ChildFunc(std::get<1>(n));
					
					for (const auto& c : childs)
					{
						if (!Types::IsNull(c))
						{
							
							q.emplace(std::get<1>(n), c, cost + CostFunc(std::get<1>(n), c));
						}
					}
					
				}
			}
			
			//Fully map paths
			void full()
			{
				for (auto node : nodes)
				{
					this->go(node);
				}
			}
		};
		
		
	};
		
		
		
		
	
	template <class Node_t, class Wgt_t>
	struct CostGetter
	{
		static Wgt_t call(const Node_t& n1, const Node_t& n2)
		{
			for (auto& e : n1->out)
			{
				if (e.out.lock() == n2)
				{
					return e.value;
				}
			}
			
			throw std::exception();
		}
	};
	
	template <class Node_t>
	struct CostGetter<Node_t, void>
	{
		static int call(const Node_t&, const Node_t&)
		{
			return 1;
		}
	};
	
	template <class Node_t>
	std::vector<Node_t> getChildren(const Node_t& parent)
	{
		std::vector<Node_t> children(parent->out.size());
		std::transform(parent->out.begin(), parent->out.end(), children.begin(), [](auto& edge)
		{
			return edge.out.lock();
		});
		return children;
	}
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	std::vector<std::shared_ptr<Node_t<T, Wgt_t>>> Graph_Base<T, Wgt_t, Node_t>::djikstraPath(Node_ptr start, Node_ptr end, Cost_t* costPtr) const
	{
		typedef DjikstraPath_t<Node_ptr, Cost_t, std::vector<Node_ptr>> OuterDjikstra;
		typedef typename OuterDjikstra::template Type<CostGetter<Node_ptr, Wgt_t>::call, getChildren> Djikstra;
		
		
		
		
		Djikstra pather(start, end);
		pather.go();
		
		if (costPtr != NULL)
		{
			*costPtr = pather.costs.at(end);
		}
		std::vector<Node_ptr> path;
		std::list<Node_ptr> list;
		Node_ptr tmp = end;
		
		while (tmp != start)
		{
			list.push_front(tmp);
			tmp = pather.paths.at(tmp);
		}
		list.push_front(start);
		
		return std::vector<Node_ptr>(list.begin(), list.end());
	}
	
	
	
	
	
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	std::map<std::shared_ptr<Node_t<T, Wgt_t>>, std::shared_ptr<Node_t<T, Wgt_t>>> Graph_Base<T, Wgt_t, Node_t>::djikstraPaths(Node_ptr start) const
	{
		typedef DjikstraPath_t<Node_ptr, Cost_t, std::vector<Node_ptr>> OuterDjikstra;
		typedef typename OuterDjikstra::template Type<CostGetter<Node_ptr, Wgt_t>::call, getChildren> Djikstra;
		
		
		Djikstra pather(start, NULL);
		pather.go();
		
		return pather.paths;
	}
	
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	std::map<std::shared_ptr<Node_t<T, Wgt_t>>, std::shared_ptr<Node_t<T, Wgt_t>>> Graph_Base<T, Wgt_t, Node_t>::djikstraPaths(Node_ptr start, std::map<Node_ptr, Cost_t>& costs) const
	{
		typedef DjikstraPath_t<Node_ptr, Cost_t, std::vector<Node_ptr>> OuterDjikstra;
		typedef typename OuterDjikstra::template Type<CostGetter<Node_ptr, Wgt_t>::call, getChildren> Djikstra;
		
		
		Djikstra pather(start, NULL);
		pather.go();
		
		costs = pather.costs;
		return pather.paths;
	}
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	auto Graph_Base<T, Wgt_t, Node_t>::djikstraPaths(std::set<Node_ptr> nodes, std::map<Node_ptr, std::map<Node_ptr, Cost_t>>& costs) const
	->
	std::map<Node_ptr, std::map<Node_ptr, Node_ptr>>
	{
		typedef DjikstraMapper_t<Node_ptr, Cost_t, std::vector<Node_ptr>> OuterDjikstra;
		typedef typename OuterDjikstra::template Type<CostGetter<Node_ptr, Wgt_t>::call, getChildren> Djikstra;
		
		Djikstra mapper(nodes);
		mapper.full();
		
		costs = mapper.costs;
		return mapper.paths;
	}
	
	
	
	
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	void Graph_Base<T, Wgt_t, Node_t>::subset(Graph_Base<T, Wgt_t, Node_t>& g, std::vector<Node_ptr>& vec) const
	{
		std::map<Node_ptr, Node_ptr> equivs;
		for (auto node : vec)
		{
			equivs[node] = std::make_shared<Node_t<T, Wgt_t>>(*node);
			equivs[node]->out.clear();
			equivs[node]->in.clear();
		}
		for (auto root : roots)
		{
			if (std::find(vec.begin(), vec.end(), root) != vec.end())
			{
				g._roots.push_back(equivs[root]);
			}
		}
		
		std::map<Node_ptr, std::map<Node_ptr, Cost_t>> costs;
		
		
		auto paths = this->djikstraPaths(vec.begin(), vec.end(), costs);
		
		
		std::map<Node_ptr, std::map<Node_ptr, Cost_t>> conns;
		
		std::function<void(Node_ptr, Node_ptr)> buildPath;
		
		buildPath = [&buildPath, &conns, &paths, &costs](auto start, auto end)
		{
			Cost_t cost;
			if (conns[start].count(end) > 0)
			{
				return;
			}
			
			if (start == end)
			{
				return;
			}
			
			Node_ptr n = end;
			Node_ptr tmp;
			while (n != start)
			{
				if (paths.count(n) > 0 && n != end)
				{
					if (conns[n].count(end) <= 0)
					{
						if (costs.at(n).count(end) <= 0)
						{
							return;
						}
						conns[n][end] = costs.at(n).at(end);
					}
					buildPath(start, n);
					return;
				}
				if (paths.at(start).count(n) <= 0)
				{
					return;
				}
				
				tmp = paths.at(start).at(n);
				
				n = tmp;
			}
			cost = costs.at(n).at(end);
			conns[n][end] = cost;
		};
		
		for (auto n : vec)
		{
			for (auto n2 : vec)
			{
				if (n == n2)
				{
					continue;
				}
				
				buildPath(n, n2);
			}
		}
		
		for (auto n : vec)
		{
			for (const auto& p : conns[n])
			{
				equivs[n]->out.push_back(equivs[p.first]);
			}
		}
		
		
		g.updateNodes();
	}
	
	
	}
	
	
	
	
	
	
	
	
	
	
}
}