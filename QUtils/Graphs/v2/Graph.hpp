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
		template <Cost_t(*CostFunc)(Node_t, Node_t), Children_t(*ChildFunc)(Node_t)>
		struct Type
		{
			std::map<Node_t, Cost_t> costs;
			std::map<Node_t, Node_t> paths;
			Node_t start, end;
			
			std::priority_queue<std::tuple<Node_t, Node_t, Cost_t>> q;
			
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
					
					for (auto c : ChildFunc(std::get<1>(n)))
					{
						if (Types::IsNull(c))
						{
							continue;
						}
						q.emplace(std::get<1>(n), c, cost + CostFunc(std::get<1>(n), c));
					}
				}
				
			}
		};
		
		
	};
		
		
		template <class T>
		struct IntIfVoid
		{
			typedef T type;
		};
		
		template <>
		struct IntIfVoid<void>
		{
			typedef int type;
		};
		
	
	template <class Node_t, class Wgt_t>
	struct CostGetter
	{
		static Wgt_t call(Node_t n1, Node_t n2)
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
		static int call(Node_t, Node_t)
		{
			return 1;
		}
	};
	
	template <class Node_t>
	std::vector<Node_t> getChildren(Node_t parent)
	{
		std::vector<Node_t> children(parent->out.size());
		std::transform(parent->out.begin(), parent->out.end(), children.begin(), [](auto& edge)
		{
			return edge.out.lock();
		});
		return children;
	}
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	std::vector<std::shared_ptr<Node_t<T, Wgt_t>>> Graph_Base<T, Wgt_t, Node_t>::djikstraPath(Node_ptr start, Node_ptr end) const
	{
		typedef typename IntIfVoid<Wgt_t>::type Cost_t;
		typedef DjikstraPath_t<Node_ptr, Cost_t, std::vector<Node_ptr>> OuterDjikstra;
		typedef typename OuterDjikstra::template Type<CostGetter<Node_ptr, Wgt_t>::call, getChildren> Djikstra;
		
		
		
		
		Djikstra pather(start, end);
		pather.go();
		
		Cost_t cost = pather.costs.at(end);
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
	
	
	
	}
}
}