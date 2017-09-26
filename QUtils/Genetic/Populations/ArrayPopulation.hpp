#pragma once

#include "ArrayPopulation.h"
#include <map>
#include <QUtils/Exception/NullPointer.h>


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
			fitVals[this->at(i)] = (*this->_fitness)(*this->at(i));
		}
		
		
		
		auto compFunc = [&] (auto a, auto b) -> bool
		{
			return (fitVals[a] > fitVals[b]);
		};
		
		std::sort(array, array+size, compFunc);
		
		
	}
	
	
	template <class T>
	void ArrayPopulation<T>::newGeneration()
	{
		
	}
	
	template <class T>
	void ArrayPopulation<T>::addOrReplace(std::shared_ptr<T> sol)
	{
		NULLPTRCHECK(sol);
		this->sort();
		array[count-1] = sol;
	}
}
}