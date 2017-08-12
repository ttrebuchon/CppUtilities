#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

namespace QUtils
{
namespace Output
{
	template <class T>
	std::string HexObject(T* ptr)
	{
		std::stringstream ss;
		ss << std::hex;
		char* arr = (char*)ptr;
		for (int i = 0; i < sizeof(T); ++i)
		{
			ss << std::setw(2) << std::setfill('0') << (int)(arr[i]);
		}
		return ss.str();
	}
}
}