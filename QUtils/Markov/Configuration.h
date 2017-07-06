#ifndef INCLUDED_MARKOV_CONFIGURATION_H
#define INCLUDED_MARKOV_CONFIGURATION_H


namespace QUtils
{
namespace Markov
{
namespace Markov_Int
{
	struct Configuration
	{
		int position = 0;
		//TODO Add additional chain configuration metrics
		
		bool operator<(const Configuration c) const
		{
			return (position < c.position);
			//TODO
		}
		
		
	};
	
}
}
}


#endif