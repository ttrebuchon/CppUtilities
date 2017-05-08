#include <NeuralNet/Net.h>


namespace Util
{
namespace NeuralNet
{
	Net::Net(int inputSize, int outputSize, std::function<long double(long double)> actFunc, std::function<long double(long double)> actDerivFunc) : input_n(inputSize), output_n(outputSize), trainingIn(), trainingOut(), act(actFunc), actDeriv(actDerivFunc)
	{
		
	}
	
	Net::~Net()
	{
		auto neuronPresent = [] (std::vector<Neuron*> v, Neuron* n) -> bool
		{
			auto it = std::find(v.begin(), v.end(), n);
			return (it != v.end());
		};
		
		std::vector<Neuron*> allNeurons;
		for (auto in : input_n)
		{
			if (in == NULL)
			    continue;
			
			for (auto n : in->getAllDown())
			{
				if (!neuronPresent(allNeurons, n))
				{
					allNeurons.push_back(n);
				}
			}
		}
		
		while (allNeurons.size() > 0)
		{
			delete allNeurons.back();
			allNeurons.pop_back();
		}
	}
	
	
}
}