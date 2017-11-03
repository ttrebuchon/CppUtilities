#pragma once
#include "Node.h"
#include <QUtils/Types/TypeSequence.h>
#include <vector>
#include <memory>
#include <set>

namespace QUtils { namespace Graphs {
	
	namespace Internal {
		
	template <class T, template <class...> class Node_t>
	class Graph_Base
	{
		private:
		typedef std::shared_ptr<Node_t<T>> Node_ptr;
		
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
				_roots.push_back(n);
				_nodes.insert(n);
			}
			return n;
		}
		
		inline void removeRoot(const Node_ptr n)
		{
			auto it = std::find(_roots.begin(), _roots.end(), n);
			_roots.erase(it);
			_nodes.erase(n);
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
	};
	
	}
	
	template <class T = void, template <class...> class Node_t = Node>
	class Graph : public Internal::Graph_Base<T, Node_t>
	{
		private:
		typedef std::shared_ptr<Node_t<T>> Node_ptr;
		
		typedef Internal::Graph_Base<T, Node_t> Base;
		
		protected:
		
		public:
		
		using Base::addRoot;
		
		Graph() : Base()
		{}
		
		inline Node_ptr addRoot(const T t)
		{
			return Base::addRoot(std::make_shared<Node_t<T>>(t));
		}
		
	};
	
	
	template <template <class...> class Node_t>
	class Graph<void, Node_t> : public Internal::Graph_Base<void, Node_t>
	{
		private:
		typedef std::shared_ptr<Node_t<void>> Node_ptr;
		
		typedef Internal::Graph_Base<void, Node_t> Base;
		
		protected:
		
		public:
		
		using Base::addRoot;
		
		Graph() : Base()
		{}
		
		inline Node_ptr addRoot()
		{
			return Base::addRoot(std::make_shared<Node_t<void>>());
		}
	};
	
	
}
}