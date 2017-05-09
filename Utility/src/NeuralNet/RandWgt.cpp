#include <NeuralNet/RandWgt.h>

#include <random>

namespace Util
{
namespace NeuralNet
{
namespace Internal
{
	
	class _GenRandWgt
	{
		public:
		
		static std::uniform_real_distribution<> dist;
		
		static std::default_random_engine gen;
	};
	
	std::uniform_real_distribution<> _GenRandWgt::dist(0, 1);
	
	std::default_random_engine _GenRandWgt::gen;
	
	
	
	
	long double RandWgt::Get()
	{
		return _GenRandWgt::dist(_GenRandWgt::gen);
	}
}
}
}