#pragma once

#include "RandWgt.h"

namespace Util
{
namespace NeuralNet
{
	class Neuron;
	
	
	class Synapse
	{
		private:
		
		protected:
		Neuron* in;
		Neuron* out;
		long double wgt;
		
		public:
		Synapse(Neuron* up, Neuron* down, long double wgt);
		Synapse(Neuron* up, Neuron* down);
		
		Neuron* get_out() const;
		
	};
	
}
}