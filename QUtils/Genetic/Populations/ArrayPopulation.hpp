#pragma once

#include "ArrayPopulation.h"


namespace QUtils
{
namespace Genetic
{
	
	template <class T>
	template <class F>
	ArrayPopulation<T>::ArrayPopulation(const F f, const unsigned int size) : Population<T>(f), array(new std::shared_ptr<T>[size]), count(size)
	{
		
	}
	
	template <class T>
	ArrayPopulation<T>::~ArrayPopulation()
	{
		delete[] array;
	}
	
	
	
	
	template <class T>
	std::shared_ptr<T>& ArrayPopulation<T>::at(const unsigned int index) const
	{
		return array[index];
	}
	
	template <class T>
	unsigned int ArrayPopulation<T>::size() const
	{
		return count;
	}
	
	
	template <class T>
	void ArrayPopulation<T>::sort()
	{
		auto size = this->size();
		
		std::map<std::shared_ptr<T>, double> fitVals;
		
		
		for (auto i = 0; i < size; i++)
		{
			fitVals[this->at(i)] = (*this->fitness)(*this->at(i));
		}
		
		
		
		auto compFunc = [&] (auto a, auto b) -> bool
		{
			return (fitVals[a] < fitVals[b]);
		};
		
		std::sort(array, array+size, compFunc);
		
		
	}
}
}