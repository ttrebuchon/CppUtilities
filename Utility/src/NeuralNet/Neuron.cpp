#include <NeuralNet/Neuron.h>

namespace Util
{
namespace NeuralNet
{
	
	
	
	
	
	std::vector<Neuron*> Neuron::getAllDown() const
	{
		auto neuronPresent = [] (std::vector<Neuron*> v, const Neuron* n) -> bool
		{
			auto it = std::find(v.begin(), v.end(), n);
			return (it != v.end());
		};
		
		std::vector<Neuron*> allNeurons;
		
		for (auto syn : this->out)
		{
			if (syn == NULL)
			    continue;
			for (auto n : syn->get_out()->getAllDown())
			{
				if (n == NULL)
				    continue;
				if (!neuronPresent(allNeurons, n))
				{
					allNeurons.push_back(n);
				}
			}
		}
		
		if (!neuronPresent(allNeurons, this))
		{
			allNeurons.push_back((Neuron*) this);
		}
		
		return allNeurons;
	}
}
}