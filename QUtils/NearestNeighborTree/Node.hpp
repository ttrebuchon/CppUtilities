#ifndef INCLUDED_UTIL_NODE_HPP
#define INCLUDED_UTIL_NODE_HPP


#include "Node.h"

namespace Util
{
namespace NN_Internal
{
	template <typename Elem, typename ...Dims>
	Node<Elem, Dims...>::Node(Elem* e, tuple<function<Dims(Elem*)>...>* funcs) : elem(e), funcs(funcs), left(NULL), right(NULL), _size(1)
	{
		
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	Node<Elem, Dims...>* Node<Elem, Dims...>::insert(Node<Elem, Dims...>* n)
	{
		auto v1 = std::get<N>(*funcs)(elem);
		auto v2 = std::get<N>(*funcs)(n->elem);
		
		auto child = &right;
		
		if (v1 >= v2)
		{
			child = &left;
		}
		
		if (*child == NULL)
		{
			*child = n;
		}
		else
		{
			*child = (*child)->template insert<(N+1)%(sizeof...(Dims))>(n);
		}
		
		_size = 1 + (left != NULL ? left->size() : 0) + (right != NULL ? right->size() : 0);
		
		
		tryBalance<N>();
		
		return this;
		
	}
	
	template <typename Elem, typename ...Dims>
	int Node<Elem, Dims...>::size()
	{
		return _size;
		int n = 1;
		if (left != NULL)
		{
			n += left->size();
		}
		if (right != NULL)
		{
			n += right->size();
		}
		
		return n;
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	void Node<Elem, Dims...>::balance()
	{
		//TODO: In case I decide to implement a reliable enough method
		
		
		//Fix size
		_size = 1 + (left != NULL ? left->size() : 0) + (right != NULL ? right->size() : 0);
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	void Node<Elem, Dims...>::tryBalance()
	{
		if (((double)rand())/RAND_MAX*100 < PROB*100)
		{
			balance<N>();
		}
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	int Node<Elem, Dims...>::traverse(Elem* e, int n, std::vector<Elem*>* vec, function<double(Elem*, Elem*)>* dist)
	{
		tryBalance<N>();
		
		auto first = left;
		auto second = right;
		
		auto v1 = std::get<N>(*funcs)(elem);
		auto v2 = std::get<N>(*funcs)(e);
		
		if (v2 > v1)
		{
			first = right;
			second = left;
		}
		
		int found = 0;
		
		if (first != NULL)
		{
			found += first->template traverse<(N+1)%(sizeof...(Dims))>(e, n, vec, dist);
		}
		
		double d = 0;
		int ind = -1;
		for (int i = 0; i < vec->size(); i++)
		{
			auto tmp = (*dist)((*vec)[i], e);
			if (tmp > d)
			{
				d = tmp;
				ind = i;
			}
		}
		
		if (vec->size() < n)
		{
			vec->push_back(elem);
			found++;
		}
		else if (d > (*dist)(elem, e))
		{
			(*vec)[ind] = elem;
			found++;
		}
		
		
		d = 0;
		ind = -1;
		for (int i = 0; i < vec->size(); i++)
		{
			auto tmp = (*dist)((*vec)[i], e);
			if (tmp > d)
			{
				d = tmp;
				ind = i;
			}
		}
		
		
		
		if (second != NULL)
		if (((v2-v1)*(v2-v1) < d*d) || (vec->size() < n))
		{
			found += second->template traverse<(N+1)%(sizeof...(Dims))>(e, n, vec, dist);
		}
		
		return found;
		
	}
	
	
	template <typename Elem, typename ...Dims>
	std::vector<Elem*> Node<Elem, Dims...>::flatten()
	{
		std::vector<Elem*> nodes;
		if (left != NULL)
		{
			nodes = left->flatten();
			nodes.push_back(left->elem);
			delete left;
			left = NULL;
		}
		if (right != NULL)
		{
			for (Elem* e : right->flatten())
			{
				nodes.push_back(e);
			}
			nodes.push_back(right->elem);
			delete right;
			right = NULL;
		}
		return nodes;
	}
	
	
}
}




#endif