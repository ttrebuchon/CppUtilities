#ifndef INCLUDED_NEAREST_NEIGHBOR_TREE_H
#define INCLUDED_NEAREST_NEIGHBOR_TREE_H


#include <tuple>
#include <vector>
#include <functional>
#include <unordered_set>


//using std::tuple;
//using std::function;
//using std::vector;

#include "Node.h"

namespace QUtils
{
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	class NearestNeighbor
	{
		private:
		
		template <typename D, typename ...Ds>
		void ProcFuncs(std::function<D(Elem*)>, std::function<Ds(Elem*)>...);
		
		protected:
		
		typedef NN_Internal::Node<Elem, Dim1, Dims...> Node;
		
		std::tuple<std::function<Dim1(Elem*)>, std::function<Dims(Elem*)>...> funcs;
		
		Node* root;
		std::unordered_set<Node*> nodes;
		
		public:
		
		
		std::function<double(Elem*, Elem*)> dist;
		NearestNeighbor(std::function<Dim1(Elem*)>, std::function<Dims(Elem*)>...);
		
		void insert(Elem*);
		
		int size();
		
		std::vector<Elem*> traverse(Elem*, int n);
		
		void erase(Elem*);
		
		
	};
	
	
	
}

#include "NearestNeighborTree.hpp"

#endif