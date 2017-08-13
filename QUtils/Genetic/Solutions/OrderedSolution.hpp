#pragma once

#include "OrderedSolution.h"
#include <algorithm>

namespace QUtils
{
namespace Genetic
{
	template <class T>
	OrderedSolution<T>::OrderedSolution(const unsigned int size, const T lowerBound, const T upperBound) : Solution<std::vector<T>, T>(), order(size)
	{
		auto v = lowerBound;
		for (auto i = 0; i < size; i++)
		{
			order[i] = v++;
			if (v > upperBound)
			{
				v = lowerBound;
			}
		}
		
		this->randomize();
		this->modified();
	}
	
	
	template <class T>
	OrderedSolution<T>::OrderedSolution(const unsigned int size, const T lowerBound) : Solution<std::vector<T>, T>(), order(size)
	{
		auto v = lowerBound;
		for (auto i = 0; i < size; i++)
		{
			order[i] = v++;
		}
		
		this->randomize();
		this->modified();
	}
	
	template <class T>
	OrderedSolution<T>::OrderedSolution(const unsigned int size) : Solution<std::vector<T>, T>(), order(size)
	{
		
	}
	
	
	template <class T>
	T& OrderedSolution<T>::at(const unsigned int i)
	{
		return order[i];
	}
	
	template <class T>
	const T& OrderedSolution<T>::at(const unsigned int i) const
	{
		return order[i];
	}
	
	template <class T>
	unsigned int OrderedSolution<T>::size() const
	{
		return order.size();
	}
	
	template <class T>
	void OrderedSolution<T>::randomize()
	{
		std::random_shuffle(order.begin(), order.end());
	}
	
	template <class T>
	void OrderedSolution<T>::mutate(const int magnitude)
	{
		int shifts = magnitude;
		if (magnitude == -1)
		{
			shifts = 1;
		}
		
		
		if (size() <= 1)
		{
			return;
		}
		
		int index1, index2;
		for (int i = 0; i < shifts; i++)
		{
		
		index1 = rand() % size();
		
		while ((index2 = rand() % size()) == index1) ;
		
		std::swap(order[index1], order[index2]);
		
		}
		
	}
	
	template <class T>
	std::vector<T> OrderedSolution<T>::get() const
	{
		return order;
	}
	
	template <class T>
	std::shared_ptr<Solution<std::vector<T>, T>> OrderedSolution<T>::clone() const
	{
		auto ptr = std::make_shared<OrderedSolution<T>>(this->size());
		int index = 0;
		for (auto t : this->order)
		{
			ptr->at(index++) = t;
		}
		return ptr;
	}
	
	
	template <class T>
	void OrderedSolution<T>::modified()
	{
		
	}
	
	template <class T>
	T& OrderedSolution<T>::set(const int index, const T t)
	{
		auto it = std::find(this->order.begin(), this->order.end(), t);
		if (it == this->order.end())
		{
			//TODO
			throw std::exception();
		}
		
		auto offset = it - this->order.begin();
		
		this->order[offset] = this->order[index];
		this->order[index] = t;
		return this->order[index];
	}
	
}
}