#pragma once
#include "Algorithm.h"

namespace QUtils
{
namespace Genetic
{
	template <typename T>
	Algorithm<T>::Algorithm(const std::shared_ptr<Population<T>> pop) : _generation(0), population(pop), generation(_generation)
	{
		
	}
}
}