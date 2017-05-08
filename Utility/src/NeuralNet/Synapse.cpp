#include <NeuralNet/Synapse.h>


namespace Util
{
namespace NeuralNet
{
	Synapse::Synapse(Neuron* up, Neuron* down, long double wgt) : in(up), out(down), wgt(wgt)
	{
		
	}
	
	Synapse::Synapse(Neuron* up, Neuron* down) : Synapse(up, down, Internal::RandWgt::Get())
	{ }
	
	
	
	
	Neuron* Synapse::get_out() const
	{
		return out;
	}
	
}
}