#ifndef INCLUDED_UTIL_MARKOV_CHAIN_H
#define INCLUDED_UTIL_MARKOV_CHAIN_H

#include "Link.h"
#include <QUtils/Exception/Exception.h>

#include <cstdlib>
#include <iostream>




namespace QUtils
{
namespace Markov
{
	QUTILS_CUSTOM_EXCEPTION(MarkovInfiniteLoopException, No way to end the chain);
	
	namespace Markov_Int
	{
	
	
	template <typename T>
	struct Chain
	{
		
		
		std::vector<Link<T>*> links;
		
		
		std::vector<T>* bind()
		{
			auto v = new std::vector<T>();
			
			for (auto link : links)
			{
				v->push_back(link->item);
			}
			return v;
		}
		
		void generate(BaseLink<T>* begin)
		{
			links = std::vector<Link<T>*>();
			BaseLink<T>* link = begin;
			
			Configuration conf;
			conf.position = 0;
			while (link->type != "end")
			{
				int select = (((double)rand())/RAND_MAX)*link->totCount;
				if (select == link->totCount)
				{
					select--;
				}
				
				int index = 0;
				for (auto KV : link->combined)
				{
					index += link->combined[KV.first];
					if (index > select)
					{
						link = KV.first;
						break;
					}
				}
				if (link->totCount <= 0)
				{
					//throw MarkovInfiniteLoopException();
				}
				
				
				if (link->type != "end")
				{
					links.push_back((Link<T>*)link);
				}
			}
		}
	};
	
	
	
	
	}
	
	
}
}


#endif