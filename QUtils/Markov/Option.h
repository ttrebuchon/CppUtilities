#ifndef INCLUDED_UTIL_MARKOV_OPTION_H
#define INCLUDED_UTIL_MARKOV_OPTION_H


#include <map>
namespace QUtils
{
namespace Markov
{
namespace Markov_Int
{
	template <typename T>
	struct BaseLink;
	
	
	template <typename T>
	struct Option
	{
		int count;
		std::map<BaseLink<T>*, int> choices;
	};
	
}
}
}



#endif