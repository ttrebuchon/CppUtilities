#include "Link.h"

namespace QUtils
{
namespace Markov
{
namespace Markov_Int
{
	template <typename T>
	void BaseLink<T>::addNext(BaseLink<T>* l, Configuration conf)
	{
		if (nexts.count(conf) <= 0)
		{
			nexts[conf] = Option<T>();
		}
		
		if (nexts[conf].choices.count(l) <= 0)
		{
			nexts[conf].choices[l] = 0;
		}
		
		if (combined.count(l) <= 0)
		{
			combined[l] = 0;
		}
		
		nexts[conf].choices[l]++;
		nexts[conf].count++;
		combined[l]++;
		totCount++;
	}
	
}
}
}