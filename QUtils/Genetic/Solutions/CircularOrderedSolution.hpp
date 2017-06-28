#pragma once

#include "CircularOrderedSolution.h"
#include <iostream>

namespace QUtils
{
namespace Genetic
{
	
	template <class T>
	void CircularOrderedSolution<T>::shift(int n)
	{
		const int size = this->order.size();
		std::vector<T> nVec(size);
		nVec.assign(&this->order[n], &this->order[size]);
		nVec.resize(size);
		for (int i = 0; i < n; i++)
		{
			nVec[i+(size-n)] = this->order[i];
		}
		this->order = nVec;
	}
	
	
	
	
	
	
	template <class T>
	CircularOrderedSolution<T>::CircularOrderedSolution(const unsigned int size, const T lowerBound, const T upperBound) : OrderedSolution<T>(size, lowerBound, upperBound)
	{
		
	}
	
	
	template <class T>
	CircularOrderedSolution<T>::CircularOrderedSolution(const unsigned int size, const T lowerBound) : OrderedSolution<T>(size, lowerBound)
	{
		
	}
	
	template <class T>
	CircularOrderedSolution<T>::CircularOrderedSolution(const unsigned int size) : OrderedSolution<T>(size)
	{
		
	}
	
	
	
	
	
	template <class T>
	std::shared_ptr<Solution<std::vector<T>, T>> CircularOrderedSolution<T>::clone() const
	{
		auto ptr = std::make_shared<CircularOrderedSolution<T>>(this->size());
		int index = 0;
		for (auto t : this->order)
		{
			ptr->at(index++) = t;
		}
		return ptr;
	}
	
	
	template <class T>
	void CircularOrderedSolution<T>::modified()
	{
		if (lowest == NULL)
		{
			lowest =  std::make_shared<T>(this->order[0]);
			for (auto& t : this->order)
			{
				if (t < *lowest)
				{
					lowest = std::make_shared<T>(t);
				}
			}
		}
		
		auto pos = std::find(this->order.begin(), this->order.end(), *lowest);
		auto offset = pos - this->order.begin();
		if (offset > 0)
		{
			this->shift(offset);
		}
	}
}
}