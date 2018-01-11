#pragma once

#include "Crossover.h"
#include <QUtils/Exception/NullPointer.h>
#include "AppropSize.hpp"

namespace QUtils
{
namespace Genetic
{
	template <typename T>
	CrossoverAlgorithm<T>::CrossoverAlgorithm(const std::shared_ptr<Population<T>> pop) : Algorithm<T>(pop), lastFit(-1), noProgressCount(0), mutations(true), sequenceLength(-1), mutateProbability(0.25)
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
			const auto unitSize = Helpers::UnitSize<decltype(this->population->at(0))>::size;
			//const auto unitSize = sizeof(decltype(this->population->at(0)->at(0)));
			const auto unitsPer10KB = 10000*sizeof(char)/unitSize;
			sequenceLength = this->population->at(0)->size()/3;
			
			if (sequenceLength > unitsPer10KB)
			{
				sequenceLength = unitsPer10KB;
			}
			
			if (sequenceLength <= 0)
			{
				sequenceLength = 1;
			}
		}
		
		
		const int solutionSize = this->population->at(0)->size();
		int endIndex;
		int seqStart;
		
		for (int i = 0; i < generations; i++)
		{
			
			this->population->sort();
			//Don't use a precalculated constant,
			//to account for populations where their size can change
			endIndex = this->population->size()-1;
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
					
					auto nVal = s2->at((seqStart + i) % s2->size());
					
					child->set((seqStart + i) % child->size(), nVal);
					
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
				if (mutations)
				{
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
				}
				child->modified();
				endIndex--;
			}
			this->population->newGeneration();
			if (mutations)
			{
			Metric bestFit = (*this->population->fitness())(*this->best());
			if (bestFit + lastFit != 0)
			{
				if (lastFit == 0)
				{
					lastFit = bestFit;
				}
				else if (100*((bestFit - lastFit))/((bestFit + lastFit)/2) >= 0.1)
				{
					noProgressCount = 0;
					lastFit = bestFit;
				}
				else
				{
					++noProgressCount;
				}
			}
			
			if (noProgressCount >= 5)
			{
				auto base = this->population->at(0);
				NULLPTRCHECK(base);
				auto child = std::dynamic_pointer_cast<T>(base->clone());
				NULLPTRCHECK(child);
				for (int i = 0; i < child->size() / 20; ++i)
				{
					if (mutateOverride == NULL)
					{
						auto csize = child->size();
						auto mag = ((noProgressCount*csize) / 1000);
						if (mag <= 0)
						{
							mag = 1;
						}
						if (mag > csize)
						{
							mag = csize;
						}
						child->mutate(mag);
					}
					else
					{
						mutateOverride(*child);
					}
				}
				this->population->addOrReplace(child);
				this->population->newGeneration();
			}
			}
			
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