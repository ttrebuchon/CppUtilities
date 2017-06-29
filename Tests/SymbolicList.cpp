#include "../Tests_Helpers.h"

#include <QUtils/SymbolicList/SymbolicList.h>

template <class T>
struct Node
{
	T entity;
	Node<T>* next;
	Node<T>* prev;
	
	Node() : entity(), next(), prev()
	{}
	
	template <class F>
	Node(F t, Node<T>* prev, Node<T>* next) : entity(t), next(next), prev(prev)
	{}
	
	Node(T t, Node<T>* prev) : entity(t), next(), prev(prev)
	{}
};

template <class T>
class LinkedList
{
	Node<T>* head;
	Node<T>* tail;
	unsigned int _count;
	int currentIndex;
	Node<T>* current;
	
	public:
	LinkedList(const unsigned int size) : head(NULL), tail(NULL), _count(size), currentIndex(0), current(NULL)
	{
		if (size > 0)
		{
			std::vector<Node<T>*> nodes(size);
			for (int i = 0; i < size; i++)
			{
				nodes[i] = new Node<T>();
				if (i > 0)
				{
					nodes[i]->prev = nodes[i-1];
					nodes[i-1]->next = nodes[i];
				}
			}
			head = nodes.front();
			tail = nodes.back();
			current = head;
		}
	}
	
	
	LinkedList() : LinkedList(0)
	{}
	
	
	int count() const
	{
		return _count;
	}
	
	T& operator[](const int index)
	{
		return at(index);
	}
	
	T& at(const int index)
	{
		while (currentIndex < index)
		{
			current = current->next;
			currentIndex++;
		}
		while (currentIndex > index)
		{
			current = current->prev;
			currentIndex--;
		}
		
		return current->entity;
	}
	
	template <class F>
	T& add(F f)
	{
		auto n = new Node<T>(f, tail);
		if (_count == 0)
		{
			head = n;
			current = head;
		}
		else
		{
			tail->next = n;
		}
		tail = n;
		_count++;
		return tail->entity;
	}
	
};

using namespace QUtils;
using namespace SymbolicList;

bool Test_SymbolicList()
{
	auto v = new std::vector<int>(4);
	PointerSymList<int, std::vector<int>> list(v, [](auto& c, auto index) -> int& { return c[index]; }, [](const auto& v) {return v.size();});
	
	v->at(1) = 2;
	assert_ex(list[1] == 2);
	list[0] = 1;
	assert_ex(list[0] == 1);
	assert_ex(v->at(0) == 1);
	assert_ex(list.size() == 4);
	
	std::vector<int> v2 = {1, 2, 3, 4, 5};
	IteratorSymList<int, std::vector<int>::iterator> list2(v2);
	assert_ex(list2[1] == 2);
	
	
	
	
	LinkedList<int> LL;
	LL.add(4);
	LL.add(6);
	assert_ex(LL.count() == 2);
	assert_ex(LL[0] == 4);
	assert_ex(LL[1] == 6);
	
	return true;
}