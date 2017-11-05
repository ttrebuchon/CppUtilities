#pragma once
#include "Node.h"
#include <QUtils/Types/TypeSequence.h>
#include <vector>
#include <memory>
#include <set>

namespace QUtils { namespace Graphs {
	
	namespace Internal {
		
	template <class T, class Wgt_t, template <class...> class Node_t>
	class Graph_Base
	{
		private:
		typedef std::shared_ptr<Node_t<T, Wgt_t>> Node_ptr;
		
		protected:
		std::set<Node_ptr> _nodes;
		std::vector<Node_ptr> _roots;
		
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
				root->getDescendants(_nodes);
			}
		}
		
		std::vector<Node_ptr> djikstraPath(Node_ptr, Node_ptr) const;
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
	};
	
	
}
}

#include "Graph.hpp"