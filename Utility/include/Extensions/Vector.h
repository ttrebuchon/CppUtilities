#pragma once

#include <vector>

namespace std
{
	template <typename T>
	std::vector<T>& operator<<(std::vector<T>& v, T t)
	{
		v.push_back(t);
		return v;
	}
	/*
	template <typename T>
	std::vector<T>& operator<<(std::vector<T>& v, T& t)
	{
		v.push_back(t);
		return v;
	}*/
	
	template <typename T>
	std::vector<T>& operator>>(T t, std::vector<T>& v)
	{
		v.insert(v.begin(), t);
		return v;
	}
	/*
	template <typename T>
	std::vector<T>& operator>>(T& t, std::vector<T>& v)
	{
		v.push_front(t);
		return v;
	}*/
	
}