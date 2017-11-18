#pragma once

#include "MapSolution.h"

namespace QUtils
{
namespace Genetic
{
	
	
	template <class Key, class T>
	MapSolution<Key, T>::MapSolution(const std::map<Key, T> values) : Solution<std::map<Key, T>, T>(), values(values)
	{
		
	}
	
	
	template <class Key, class T>
	T& MapSolution<Key, T>::at(const Key i)
	{
		return values.at(i);
	}
	
	template <class Key, class T>
	const T& MapSolution<Key, T>::at(const Key i) const
	{
		return values.at(i);
	}
	
	template <class Key, class T>
	unsigned int MapSolution<Key, T>::size() const
	{
		return values.size();
	}
	
	template <class Key, class T>
	void MapSolution<Key, T>::randomize()
	{
		std::vector<Key> keys;
		
		for (const auto& pair : values)
		{
			keys.push_back(pair.first);
		}
		
		std::random_shuffle(keys.begin(), keys.end());
		auto it = keys.begin();
		for (auto& pair : values)
		{
			std::swap(pair.second, values.at(*it));
			++it;
		}
	}
	
	template <class Key, class T>
	void MapSolution<Key, T>::mutate(const int magnitude)
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
		
		auto it1 = values.begin();
		for (int i = 0; i < index1; ++i)
		{
			++it1;
		}
		
		auto it2 = values.begin();
		for (int i = 0; i < index2; ++i)
		{
			++it2;
		}
		
		std::swap(values.at(it1->first), values.at(it2->first));
		
		}
		
	}
	
	template <class Key, class T>
	std::map<Key, T> MapSolution<Key, T>::get() const
	{
		return values;
	}
	
	template <class Key, class T>
	std::shared_ptr<Solution<std::map<Key, T>, T>> MapSolution<Key, T>::clone() const
	{
		auto ptr = std::make_shared<MapSolution<Key, T>>(values);
		return ptr;
	}
	
	
	template <class Key, class T>
	void MapSolution<Key, T>::modified()
	{
		
	}
	
	template <class Key, class T>
	T& MapSolution<Key, T>::set(const int index, const T t)
	{
		auto it = values.begin();
		for (auto i = 0; i < index; ++i)
		{
			++it;
		}
		return this->set(it->first, t);
	}
	
	template <class Key, class T>
	T& MapSolution<Key, T>::set(const Key index, const T t)
	{
		return (values.at(index) = t);
	}
	
	template <class Key, class T>
	T& MapSolution<Key, T>::atIndex(size_t index)
	{
		auto it = values.begin();
		while (index-- > 0)
		{
			++it;
		}
		return it->second;
	}
}
}