#ifndef INCLUDED_UTIL_MARKOV_H
#define INCLUDED_UTIL_MARKOV_H


#include <functional>
#include <vector>


#include "Link.h"
#include "Chain.h"

namespace Util
{
	template <typename T>
	class Markov
	{
		private:
		std::vector<Markov_Int::Link<T>*> links;
		
		std::vector<Markov_Int::Chain<T>*> training;
		
		Markov_Int::BeginLink<T>* beginning;
		Markov_Int::EndLink<T>* ending;
		
		protected:
		
		public:
		
		Markov();
		~Markov();
		
		std::function<bool(T, T)> equals;
		
		template <typename Iterable>
		void AddTrainChain(Iterable);
		
		std::vector<T>* GenerateChain();
		
	};
	
	
}

#include "Markov.hpp"


#endif