#include <QUtils/Graphs/EdgeCollection.h>
#include <QUtils/Exception/Exception.h>

namespace QUtils { namespace Graphs {

QUTILS_CUSTOM_EXCEPTION(EdgeCollectionException,);

namespace EdgeCollection_Internal
{
	
	struct compare_weak {
	bool operator()(const std::weak_ptr<Edge>& ptr1, const std::weak_ptr<Edge>& ptr2)
	{
		return ptr1.lock() < ptr2.lock();
	}
	};
	
	template <template <class> class Ptr_t>
	Base<Ptr_t>::Base(const size_t reserve) : edges()
	{
		edges.reserve(reserve);
	}
	
	template <template <class> class Ptr_t>
	Base<Ptr_t>::Base() : edges()
	{
		
	}
	
	template <template <class> class Ptr_t>
	const Ptr_t<Edge>& Base<Ptr_t>::operator[](const size_t index) const
	{
		return edges[index];
	}
	
	template <template <class> class Ptr_t>
	const Ptr_t<Edge>& Base<Ptr_t>::at(const size_t index) const
	{
		return edges.at(index);
	}
	
	template <template <class> class Ptr_t>
	size_t Base<Ptr_t>::size() const
	{
		return edges.size();
	}
	
	template <>
	void Base<std::shared_ptr>::push(const std::shared_ptr<Edge> edge)
	{
		auto it = std::upper_bound(edges.cbegin(), edges.cend(), edge);
		
		if (NULL == edge)
		{
			throw EdgeCollectionException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Cannot push a NULL edge into a collection");
		}
		else if (it != edges.cend())
		{
			if (*it == edge)
			{
				throw EdgeCollectionException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Tried to push duplicate edge into collection");
			}
		}
		
		edges.insert(it, edge);
	}
	
	template <>
	void Base<std::weak_ptr>::push(const std::weak_ptr<Edge> edge)
	{
		compare_weak comp;
		auto it = std::upper_bound(edges.cbegin(), edges.cend(), edge, comp);
		
		
		{
			auto shared_edge = edge.lock();
			if (NULL == shared_edge)
			{
				throw EdgeCollectionException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Cannot push a NULL edge into a collection");
			}
			else if (it != edges.cend())
			{
				if (it->lock() == shared_edge)
				{
					throw EdgeCollectionException().Line(__LINE__).File(__FILE__).Function(__func__).Msg("Tried to push duplicate edge into collection");
				}
			}
		}
		
		edges.insert(it, edge);
	}
	
	template <template <class> class Ptr_t>
	void Base<Ptr_t>::reserve(const size_t size)
	{
		edges.reserve(size);
	}
	
	
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::iterator Base<Ptr_t>::begin() noexcept
	{
		return edges.begin();
	}
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::iterator Base<Ptr_t>::end() noexcept
	{
		return edges.end();
	}
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::const_iterator Base<Ptr_t>::begin() const noexcept
	{
		return edges.begin();
	}
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::const_iterator Base<Ptr_t>::end() const noexcept
	{
		return edges.end();
	}
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::const_iterator Base<Ptr_t>::cbegin() const noexcept
	{
		return edges.cbegin();
	}
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::const_iterator Base<Ptr_t>::cend() const noexcept
	{
		return edges.cend();
	}
	
	
	template <template <class> class Ptr_t>
	typename Base<Ptr_t>::iterator Base<Ptr_t>::erase(const_iterator it)
	{
		return edges.erase(it);
	}
	
	template <template <class> class Ptr_t>
	Ptr_t<Edge> Base<Ptr_t>::replaceAt(const size_t index, Ptr_t<Edge> ptr)
	{
		throw std::exception();
	}
	
	template <template <class> class Ptr_t>
	Ptr_t<Edge> Base<Ptr_t>::replaceAt(const_iterator it, Ptr_t<Edge> ptr)
	{
		throw std::exception();
	}
	
	
	
	
	
	
	
	
	template class Base<std::shared_ptr>;
	template class Base<std::weak_ptr>;
}
	
	
	
	
	
}
}