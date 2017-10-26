#pragma once

#include <memory>
#include <vector>

namespace QUtils { namespace Graphs {
	
class Edge;
class Node;
	
namespace EdgeCollection_Internal
{
	template <template <class> class Ptr_t>
	class Base
	{
		private:
		typedef Ptr_t<Edge> Edge_ptr;
		
		protected:
		std::vector<Ptr_t<Edge>> edges;
		
		public:
		Base(const size_t reserved);
		Base();
		
		
		const Ptr_t<Edge>& operator[](const size_t) const;
		const Ptr_t<Edge>& at(const size_t) const;
		size_t size() const;
		void push(const Ptr_t<Edge>);
		void reserve(const size_t);
		
		typedef typename std::vector<Ptr_t<Edge>>::iterator iterator;
		
		typedef typename std::vector<Ptr_t<Edge>>::const_iterator const_iterator;
		
		iterator begin() noexcept;
		iterator end() noexcept;
		const_iterator begin() const noexcept;
		const_iterator end() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;
		
		
		iterator erase(const_iterator it);
		Edge_ptr replaceAt(const size_t, Edge_ptr);
		Edge_ptr replaceAt(const_iterator, Edge_ptr);
		
		std::vector<std::shared_ptr<Node>> getNodes() const;
		bool hasChild(const Edge_ptr) const;
		
		
		
		inline Edge_ptr replace(const size_t index, Edge_ptr ptr) { return replaceAt(index, ptr); }
		inline Edge_ptr replace(const_iterator it, Edge_ptr ptr) { return replaceAt(it, ptr); }
		
		
		inline const std::vector<Ptr_t<Edge>> get() const
		{ return edges; }
	};
	
	template <>
	void Base<std::shared_ptr>::push(const std::shared_ptr<Edge> edge);
	
	template <>
	void Base<std::weak_ptr>::push(const std::weak_ptr<Edge> edge);
	
	
	
	extern template class Base<std::shared_ptr>;
	
	extern template class Base<std::weak_ptr>;
}
	
	
	typedef EdgeCollection_Internal::Base<std::shared_ptr> EdgeCollection;
	
	typedef EdgeCollection_Internal::Base<std::weak_ptr> WeakEdgeCollection;
	
	
	
	
}
}