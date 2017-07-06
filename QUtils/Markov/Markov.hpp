
#include "Markov.h"
#include "Configuration.h"
#include <QUtils/Exception/Exception.h>

UTIL_CUSTOM_EXCEPTION(UnsetEqualsFunc, equals needs to be set!);

namespace QUtils
{
namespace Markov
{
	template <typename T>
	Markov<T>::Markov() : beginning(new Markov_Int::BeginLink<T>()), ending(new Markov_Int::EndLink<T>())
	{
		
	}
	
	template <typename T>
	Markov<T>::~Markov()
	{
		while (links.size() > 0)
		{
			auto l = links.back();
			links.pop_back();
			delete l;
		}
		
		while (training.size() > 0)
		{
			auto c = training.back();
			training.pop_back();
			delete c;
		}
	}
	
	
	
	template <typename T>
	template <typename Iter>
	void Markov<T>::AddTrainChain(Iter list)
	{
		std::vector<T> items;
		for (T t : list)
		{
			items.push_back(t);
		}
		
		
		std::vector<Markov_Int::BaseLink<T>*> links;
		links.push_back(beginning);
		Markov_Int::Link<T>* cLink = NULL;
		if (equals == NULL)
		{
			throw UnsetEqualsFunc();
		}
		for (T t : items)
		{
			for (Markov_Int::Link<T>* link : this->links)
			{
				if (equals(link->item, t))
				{
					cLink = link;
					break;
				}
			}
			if (cLink == NULL)
			{
				cLink = new Markov_Int::Link<T>(t);
				this->links.push_back(cLink);
			}
			links.push_back(cLink);
			cLink = NULL;
		}
		
		links.push_back(ending);
		
		for (int i = 0; i < links.size() - 1; i++)
		{
			auto link = links[i];
			Markov_Int::Configuration config;
			config.position = i;
			//TODO Set additional config info
			
			
			link->addNext(links[i+1], config);
		}
		
	}
	
	template <typename T>
	std::vector<T>* Markov<T>::GenerateChain()
	{
		auto chain = new Markov_Int::Chain<T>();
		chain->generate(beginning);
		auto list = chain->bind();
		delete chain;
		return list;
	}
	
	
}
}