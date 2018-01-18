#pragma once
#include <QUtils/BareMetal/size_t.h>

namespace QUtils { namespace Metal {
	
	
	template <class T>
	class List
	{
		private:
		
		protected:
		struct Node
		{
			Node *prev, *next;
			T item;
		};
		
		Node *first, *last;
		size_t _size;
		
		public:
		class iterator;
		
		List() : first(new Node), last(first), _size(0)
		{
			first->prev = nullptr;
			first->next = nullptr;
		}
		
		
		void push_back(const T t)
		{
			auto ptr = new Node{last, nullptr};
			last->next = ptr;
			last->item = t;
			last = ptr;
			++_size;
		}
		
		void push_front(const T t)
		{
			auto ptr = new Node{nullptr, first, t};
			first->prev = ptr;
			first = ptr;
			++_size;
		}
		
		bool empty() const
		{
			return (first == last);
		}
		
		inline size_t size() const
		{
			return _size;
		}
		
		
		
		
		iterator begin()
		{
			return iterator(first);
		}
		
		iterator end()
		{
			return iterator(last);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		class iterator
		{
			protected:
			Node* n;
			
			iterator(Node* n) : n(n)
			{}
			
			public:
			
			iterator() : iterator(nullptr)
			{}
			
			
			T& operator*()
			{
				return n->item;
			}
			
			
			iterator& operator++()
			{
				n = n->next;
				return *this;
			}
			
			iterator operator++(int)
			{
				Node* m = n;
				n = n->next;
				return iterator(m);
			}
			
			iterator& operator--()
			{
				n = n->prev;
				return *this;
			}
			
			iterator operator--(int)
			{
				Node* m = n;
				n = n->prev;
				return iterator(m);
			}
			
			inline bool operator==(const iterator it) const
			{
				return n == it.n;
			}
			
			inline bool operator!=(const iterator it) const
			{
				return n != it.n;
			}
			
			template <class>
			friend class List;
		};
		
		
		
		
		
		
		
		class reverse_iterator
		{
			protected:
			Node* n;
			
			reverse_iterator(Node* n) : n(n)
			{}
			
			public:
			
			reverse_iterator() : iterator(nullptr)
			{}
			
			
			T& operator*()
			{
				return n->item;
			}
			
			
			reverse_iterator& operator++()
			{
				n = n->prev;
				return *this;
			}
			
			reverse_iterator operator++(int)
			{
				Node* m = n;
				n = n->prev;
				return iterator(m);
			}
			
			reverse_iterator& operator--()
			{
				n = n->next;
				return *this;
			}
			
			reverse_iterator operator--(int)
			{
				Node* m = n;
				n = n->next;
				return iterator(m);
			}
			
			inline bool operator==(const reverse_iterator it) const
			{
				return n == it.n;
			}
			
			inline bool operator!=(const reverse_iterator it) const
			{
				return n != it.n;
			}
			
			template <class>
			friend class List;
		};
		
	};
	
	int metal_build_test();
	
}
}