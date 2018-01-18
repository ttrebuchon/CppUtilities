#ifndef INCLUDED_UTIL_NODE_H
#define INCLUDED_UTIL_NODE_H

#include "NearestNeighborTree.h"

namespace QUtils
{
	namespace NN_Internal
	{
		using std::tuple;
		using std::function;
	template <typename Elem, typename ...Dims>
	class Node
	{
		private:
		std::tuple<Dims...> attrs;
		Elem* elem;
		tuple<function<Dims(Elem*)>...>* funcs;
		
		Node* left;
		Node* right;
		int _size;
		
		template <int N>
		void balance();
		#define PROB 0.1
		
		template <int N>
		inline void tryBalance();
		
		
		std::vector<Elem*> flatten();
		
		public:
		
		Node(Elem*, tuple<function<Dims(Elem*)>...>*);
		
		template <int N>
		Node* insert(Node*);
		
		int size();
		
		template <int N>
		int traverse(Elem*, const std::tuple<Dims...>& attrs, int n, std::vector<Node*>*, const function<double(Elem*, Elem*)>& dist);
		
		template <class, class, class...>
		friend class NearestNeighbor;
	};
	
	}
	
}

#include "Node.hpp"

#endif