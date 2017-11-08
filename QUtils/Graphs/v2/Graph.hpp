#pragma once
#include "Graph.h"
#include <list>
#include <vector>
#include <memory>
#include <set>
#include <queue>
#include <QUtils/Types/IsNull.h>

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
						q.emplace(start, c, CostFunc(start, c));
					}
				}
				
				while (!q.empty())
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
	
	
	
	}
	
	
	
	
	
	
	
	
	
	
}
}