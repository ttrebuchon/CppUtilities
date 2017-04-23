#ifndef INCLUDED_UTIL_NODE_H
#define INCLUDED_UTIL_NODE_H

#include "NearestNeighborTree.h"

namespace Util
{
	namespace NN_Internal
	{
		using std::tuple;
		using std::function;
	template <typename Elem, typename ...Dims>
	class Node
	{
		private:
		Elem* elem;
		tuple<function<Dims(Elem*)>...>* funcs;
		
		Node* left;
		Node* right;
		int _size;
		
		template <int N>
		void balance();
		#define PROB 0.1
		
		template <int N>
		void tryBalance();
		
		
		std::vector<Elem*> flatten();
		
		public:
		
		Node(Elem*, tuple<function<Dims(Elem*)>...>*);
		
		template <int N>
		Node* insert(Node*);
		
		int size();
		
		template <int N>
		int traverse(Elem*, int n, std::vector<Elem*>*, function<double(Elem*, Elem*)>* dist);
		
		
	};
	
	}
	
}

#include "Node.hpp"

#endif