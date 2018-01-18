#ifndef INCLUDED_UTIL_NODE_HPP
#define INCLUDED_UTIL_NODE_HPP


#include "Node.h"
#include <QUtils/Types/IntegerSequence.h>

namespace QUtils
{
namespace NN_Internal
{
	namespace detail
	{
		template <class Seq>
		struct AttrEval;
		
		template <int... I>
		struct AttrEval<Types::Sequence<I...>>
		{
			template <class Elem, class... Dims>
			static void call(std::tuple<Dims...>& attrs, auto& funcs, Elem* e)
			{
				attrs = std::tuple<Dims...>((std::get<I>(funcs))(e)...);
			}
		};
	}
	
	
	template <typename Elem, typename ...Dims>
	Node<Elem, Dims...>::Node(Elem* e, tuple<function<Dims(Elem*)>...>* funcs) : attrs(), elem(e), funcs(funcs), left(NULL), right(NULL), _size(1)
	{
		typedef typename Types::SequenceGen<sizeof...(Dims)-1>::type Seq;
		detail::AttrEval<Seq>::call(attrs, *funcs, e);
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	Node<Elem, Dims...>* Node<Elem, Dims...>::insert(Node<Elem, Dims...>* n)
	{
		auto v1 = std::get<N>(attrs);//(*funcs)(elem);
		auto v2 = std::get<N>(n->attrs);//(*funcs)(n->elem);
		
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
	inline void Node<Elem, Dims...>::tryBalance()
	{
		if (((double)rand())/RAND_MAX*100 < PROB*100)
		{
			balance<N>();
		}
	}
	
	template <typename Elem, typename ...Dims>
	template <int N>
	int Node<Elem, Dims...>::traverse(Elem* e, const std::tuple<Dims...>& attrs, int n, std::vector<Node<Elem, Dims...>*>* vec, const function<double(Elem*, Elem*)>& dist)
	{
		tryBalance<N>();
		
		auto first = left;
		auto second = right;
		
		auto v1 = std::get<N>(this->attrs);//(*funcs)(elem);
		auto v2 = std::get<N>(attrs);
		
		if (v2 > v1)
		{
			first = right;
			second = left;
		}
		
		int found = 0;
		
		if (first != NULL)
		{
			found += first->template traverse<(N+1)%(sizeof...(Dims))>(e, attrs, n, vec, dist);
		}
		
		double d = 0;
		int ind = -1;
		for (int i = 0; i < vec->size(); i++)
		{
			auto tmp = dist((*vec)[i]->elem, e);
			if (tmp > d)
			{
				d = tmp;
				ind = i;
			}
		}
		
		if (vec->size() < n)
		{
			vec->push_back(this);
			found++;
		}
		else if (d > dist(elem, e))
		{
			(*vec)[ind] = this;
			found++;
		}
		
		
		d = 0;
		ind = -1;
		for (int i = 0; i < vec->size(); i++)
		{
			auto tmp = dist((*vec)[i]->elem, e);
			if (tmp > d)
			{
				d = tmp;
				ind = i;
			}
		}
		
		
		
		if (second != NULL)
		if (((v2-v1)*(v2-v1) < d*d) || (vec->size() < n))
		{
			found += second->template traverse<(N+1)%(sizeof...(Dims))>(e, attrs, n, vec, dist);
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