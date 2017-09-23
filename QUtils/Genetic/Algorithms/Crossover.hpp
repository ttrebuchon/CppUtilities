#pragma once

#include "Crossover.h"
#include <QUtils/Exception/NullPointer.h>

namespace QUtils
{
namespace Genetic
{
	template <typename T>
	CrossoverAlgorithm<T>::CrossoverAlgorithm(const std::shared_ptr<Population<T>> pop) : Algorithm<T>(pop), mutations(true), sequenceLength(-1), mutateProbability(0.25)
	{
	}
	
	
	
	
	
	template <typename T>
	void CrossoverAlgorithm<T>::go(const unsigned int generations)
	{
		NULLPTRCHECK(this->population);
		
		if (sequenceLength < 0)
		{
			if (this->population->size() <= 0)
			{
				//TODO
				throw std::exception();
			}
			sequenceLength = this->population->at(0)->size()/3;
			if (sequenceLength <= 0)
			{
				sequenceLength = 1;
			}
		}
		
		
		const auto popSize = this->population->size();
		const int solutionSize = this->population->at(0)->size();
		int endIndex;
		int seqStart;
		
		for (int i = 0; i < generations; i++)
		{
			
			this->population->sort();
			endIndex = popSize-1;
			for (int i = 1; i < endIndex; i++)
			{
				auto& s1 = this->population->at(i-1);
				NULLPTRCHECK(s1);
				auto& s2 = this->population->at(i);
				NULLPTRCHECK(s2);
				auto child = std::dynamic_pointer_cast<T>(s1->clone());
				NULLPTRCHECK(child);
				seqStart = rand() % solutionSize;
				for (int i = 0; i < sequenceLength; i++)
				{
					//auto overwritten = child->at((seqStart + i) % solutionSize);
					
					auto nVal = s2->at((seqStart + i) % solutionSize);
					
					child->set((seqStart + i) % solutionSize, nVal);
					
					/*for (auto j = 0; j < solutionSize; j++)
					{
						if (child->at(j) == nVal)
						{
							child->at(j) = overwritten;
						}
					}
					
					child->at((seqStart + i) % solutionSize) = nVal;*/
				}
				
				this->population->at(endIndex) = child;
				if (static_cast<double>(rand())/RAND_MAX > mutateProbability)
				{
					if (mutateOverride == NULL)
					{
						child->mutate(1);
					}
					else
					{
						mutateOverride(*child);
					}
				}
				child->modified();
				endIndex--;
			}
			this->population->newGeneration();
		}
	}
	
	template <typename T>
	std::shared_ptr<const T> CrossoverAlgorithm<T>::best() const
	{
		this->population->sort();
		return this->population->at(0);
	}
	
	
}
}