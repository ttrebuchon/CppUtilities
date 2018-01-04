#pragma once
#include <list>

namespace QUtils
{
namespace Combinatorial
{
	auto permutations(auto args1, auto args2)
	{
		
		typedef decltype(*args1.begin()) T;
		typedef decltype(*args2.begin()) G;
		std::list<std::pair<T, G>> perms;
		
		for (const T& t : args1)
		{
			for (const G& g : args2)
			{
				perms.emplace_back(t, g);
			}
		}
		
		return perms;
	}
}
}