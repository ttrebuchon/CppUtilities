#pragma once
#include "Combinatorial.h"

namespace QUtils
{
namespace Combinatorial
{
	template <typename T>
	std::vector<std::vector<T>> vChooseN(const std::vector<T>& v, int N)
	{
		std::vector<std::vector<T>> C;
		
		if (N == 1)
		{
			for (T t : v)
			{
				C.push_back({t});
			}
			return C;
		}
		for (auto i = 0; i < v.size(); i++)
		{
			std::vector<T> vc = v;
			vc.erase(std::find(vc.begin(), vc.end(), vc[i]));
			auto tmp = vChooseN(vc, N-1);
			for (auto& group : tmp)
			{
				group.push_back(v[i]);
				C.push_back(group);
			}
		}
		return C;
	}
}
}