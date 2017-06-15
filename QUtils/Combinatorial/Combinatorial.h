#pragma once
#include <vector>

namespace Util
{
namespace Combinatorial
{
	template <typename T>
	std::vector<std::vector<T>> vChooseN(const std::vector<T>&, int N);
}
}

#include "Combinatorial.hpp"