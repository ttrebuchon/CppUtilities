#pragma once
#include "Node.h"
#include <QUtils/Types/TypeSequence.h>
#include <vector>
#include <memory>
#include <set>
#include <map>

namespace QUtils { namespace Graphs {
	
	namespace Internal {
	
	
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
	
	template <class T, class Wgt_t, template <class...> class Node_t>
	class Graph_Base
	{
		private:
		typedef std::shared_ptr<Node_t<T, Wgt_t>> Node_ptr;
		
		protected:
		std::set<Node_ptr> _nodes;
		std::vector<Node_ptr> _roots;
		
		
		
		
		
		
		
		
		void subset(Graph_Base<T, Wgt_t, Node_t>& g, std::vector<Node_ptr>& vec) const;
		
		public:
		const std::vector<Node_ptr>& roots;
		const std::set<Node_ptr>& nodes;
		
		Graph_Base() : _nodes(), _roots(), roots(_roots), nodes(_nodes)
		{}
		
		Node_ptr addRoot(const Node_ptr n)
		{
			if (n)
			{
				if (std::find(_roots.begin(), _roots.end(), n) == _roots.end())
				{
					_roots.push_back(n);
				}
				_nodes.insert(n);
				auto descendants = n->getDescendants();
				_nodes.insert(descendants.begin(), descendants.end());
			}
			return n;
		}
		
		inline void removeRoot(const Node_ptr n)
		{
			auto it = std::find(_roots.begin(), _roots.end(), n);
			_roots.erase(it);
			_nodes.erase(n);
		}
		
		inline Node_ptr createRoot()
		{
			return addRoot(std::make_shared<Node_t<T, Wgt_t>>());
		}
		
		
		auto begin() -> decltype(nodes.begin())
		{
			return nodes.begin();
		}
		
		auto end() -> decltype(nodes.end())
		{
			return nodes.end();
		}
		
		auto begin() const -> decltype(nodes.begin())
		{
			return nodes.begin();
		}
		
		auto end() const -> decltype(nodes.end())
		{
			return nodes.end();
		}
		
		template <class F>
		std::set<Node_ptr> where(const F f) const
		{
			std::set<Node_ptr> res;
			auto it = nodes.begin();
			while ((it = std::find_if(it, nodes.end(), f)) != nodes.end())
			{
				res.insert(*it);
				++it;
			}
			return res;
		}
		
		void updateNodes()
		{
			for (auto root : roots)
			{
				_nodes.insert(root);
				root->getDescendants(_nodes);
			}
		}
		
		inline void addNode(Node_ptr n)
		{
			if (n)
			{
				_nodes.insert(n);
			}
		}
		
		private:
		
		typedef typename IntIfVoid<Wgt_t>::type Cost_t;
		
		public:
		
		
		std::vector<Node_ptr> djikstraPath(Node_ptr, Node_ptr, Cost_t* cost = NULL) const;
		
		std::map<Node_ptr, Node_ptr> djikstraPaths(Node_ptr) const;
		
		std::map<Node_ptr, Node_ptr> djikstraPaths(Node_ptr, std::map<Node_ptr, Cost_t>& costs) const;
		
		template <class It>
		std::map<Node_ptr, std::map<Node_ptr, Node_ptr>> djikstraPaths(It start, It end, std::map<Node_ptr, std::map<Node_ptr, Cost_t>>& costs) const
		{
			std::set<Node_ptr> nodes(start, end);
			if (nodes.count(NULL) > 0)
			{
				nodes.erase(NULL);
			}
			return djikstraPaths(nodes, costs);
		}
		
		template <class It>
		inline std::map<Node_ptr, std::map<Node_ptr, Node_ptr>> djikstraPaths(It start, It end) const
		{
			std::map<Node_ptr, std::map<Node_ptr, Cost_t>> costs;
			return djikstraPaths(start, end, costs);
		}
		
		std::map<Node_ptr, std::map<Node_ptr, Node_ptr>> djikstraPaths(std::set<Node_ptr> nodes, std::map<Node_ptr, std::map<Node_ptr, Cost_t>>& costs) const;
		
		
	};
	
	}
	
	template <class T = void, class Wgt_t = void, template <class...> class _Node_t = Node>
	class Graph : public Internal::Graph_Base<T, Wgt_t, _Node_t>
	{
		public:
		typedef _Node_t<T, Wgt_t> Node_t;
		
		private:
		typedef std::shared_ptr<Node_t> Node_ptr;
		
		typedef Internal::Graph_Base<T, Wgt_t, _Node_t> Base;
		
		protected:
		
		public:
		
		using Base::addRoot;
		using Base::createRoot;
		
		Graph() : Base()
		{}
		
		inline Node_ptr createRoot(const T t)
		{
			return Base::addRoot(std::make_shared<Node_t>(t));
		}
		
		template <class It>
		Graph subset(It start, It end) const
		{
			Graph g;
			std::vector<Node_ptr> vec(start, end);
			Base::subset(g, vec);
			return g;
		}
		
	};
	
	
	template <class Wgt_t, template <class...> class _Node_t>
	class Graph<void, Wgt_t, _Node_t> : public Internal::Graph_Base<void, Wgt_t, _Node_t>
	{
		public:
		typedef _Node_t<void, Wgt_t> Node_t;
		
		private:
		typedef std::shared_ptr<Node_t> Node_ptr;
		
		typedef Internal::Graph_Base<void, Wgt_t, _Node_t> Base;
		
		protected:
		
		public:
		
		using Base::addRoot;
		using Base::createRoot;
		
		Graph() : Base()
		{}
		
		template <class It>
		Graph subset(It start, It end) const
		{
			Graph g;
			std::vector<Node_ptr> vec(start, end);
			Base::subset(g, vec);
			return g;
		}
	};
	
	
}
}

#include "Graph.hpp"