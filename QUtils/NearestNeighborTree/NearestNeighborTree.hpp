#ifndef INCLUDED_NEAREST_NEIGHBOR_TREE_HPP
#define INCLUDED_NEAREST_NEIGHBOR_TREE_HPP


#include "NearestNeighborTree.h"

namespace QUtils
{
	template <typename Elem, typename Dim1, typename ...Dims>
	NearestNeighbor<Elem, Dim1, Dims...>::NearestNeighbor(std::function<Dim1(Elem*)> f1, std::function<Dims(Elem*)>... fs) : root(NULL)
	{
		ProcFuncs(f1, fs...);
	}
	
	
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	template <typename D, typename ...Ds>
	void NearestNeighbor<Elem, Dim1, Dims...>::ProcFuncs(std::function<D(Elem*)> f, std::function<Ds(Elem*)>... fs)
	{
		funcs = std::make_tuple(f, fs...);
	}
	
	
	template <typename Elem, typename Dim1, typename ...Dims>
	void NearestNeighbor<Elem, Dim1, Dims...>::insert(Elem* e)
	{
		Node* n = new Node(e, &funcs);
		if (root == NULL)
		{
			root = n;
		}
		else
		{
			root = root->template insert<0>(n);
		}
	}
	
	template <typename Elem, typename Dim1, typename ...Dims>
	int NearestNeighbor<Elem, Dim1, Dims...>::size()
	{
		if (root == NULL)
		{
			return 0;
		}
		return root->size();
	}
	
	template <typename Elem, typename Dim1, typename ...Dims>
	std::vector<Elem*> NearestNeighbor<Elem, Dim1, Dims...>::traverse(Elem* e, int n)
	{
		std::vector<Elem*> results;
		
		root->template traverse<0>(e, n, &results, &dist);
		
		return results;
	}
}

#endif