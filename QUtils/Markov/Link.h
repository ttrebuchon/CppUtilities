#ifndef INCLUDED_UTIL_MARKOV_LINK_H
#define INCLUDED_UTIL_MARKOV_LINK_H

#include <vector>
#include <tuple>
#include <map>
#include <string>

#include "Configuration.h"
#include "Option.h"

namespace QUtils
{
namespace Markov
{
	namespace Markov_Int
	{
	using std::vector;
	template <typename T>
	struct BaseLink
	{
		std::string type;
		
		BaseLink() : type("base"), nexts(), combined(), totCount(0)
		{ }
		
		std::map<Configuration, Option<T>> nexts;
		
		std::map<BaseLink<T>*, int> combined;
		int totCount;
		
		
		void addNext(BaseLink<T>*, Configuration);
		
		BaseLink<T>* GetNext(Configuration);
	};
	
	template <typename T>
	struct Link : BaseLink <T>
	{
		T item;
		
		Link(T t) : BaseLink<T>(), item(t)
		{
			this->type = "link";
		}
	};
	
	template <typename T>
	struct BeginLink : BaseLink<T>
	{
		BeginLink() : BaseLink<T>()
		{
			this->type = "begin";
		}
	};
	
	template <typename T>
	struct EndLink : BaseLink<T>
	{
		EndLink() : BaseLink<T>()
		{
			this->type = "end";
		}
	};
	
	
	
	}
}
}

#include "Link.hpp"

#endif