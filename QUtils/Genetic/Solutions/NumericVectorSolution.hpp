#pragma once

#include "NumericVectorSolution.h"

namespace QUtils
{
namespace Genetic
{
	template <class T>
	NumericVectorSolution<T>::NumericVectorSolution(const unsigned int size) : Solution<std::vector<T>, T>(), values(size)
	{
		
	}
	
	
	template <class T>
	NumericVectorSolution<T>::NumericVectorSolution(const std::vector<T> values) : Solution<std::vector<T>, T>(), values(values)
	{
		
	}
	
	
	template <class T>
	T& NumericVectorSolution<T>::at(const size_t i)
	{
		return values[i];
	}
	
	template <class T>
	const T& NumericVectorSolution<T>::at(const size_t i) const
	{
		return values[i];
	}
	
	template <class T>
	unsigned int NumericVectorSolution<T>::size() const
	{
		return values.size();
	}
	
	template <class T>
	void NumericVectorSolution<T>::randomize()
	{
		std::random_shuffle(values.begin(), values.end());
	}
	
	template <class T>
	void NumericVectorSolution<T>::mutate(const int magnitude)
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
		
		std::swap(values[index1], values[index2]);
		
		}
		
	}
	
	template <class T>
	std::vector<T> NumericVectorSolution<T>::get() const
	{
		return values;
	}
	
	template <class T>
	std::shared_ptr<Solution<std::vector<T>, T>> NumericVectorSolution<T>::clone() const
	{
		auto ptr = std::make_shared<NumericVectorSolution<T>>(values);
		return ptr;
	}
	
	
	template <class T>
	void NumericVectorSolution<T>::modified()
	{
		
	}
	
	template <class T>
	T& NumericVectorSolution<T>::set(const int index, const T t)
	{
		return (values.at(index) = t);
	}
}
}