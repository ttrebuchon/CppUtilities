#pragma once

#include "../Synapse.h"

namespace Util
{
namespace NeuralNet
{
namespace Synapses
{
	
	/*Can hold only a positive weight or zero
	This constraint check is performed during propagation*/
	template <typename T>
	class PositiveSynapse : public Synapse<T>
	{
		private:
		
		protected:
		Neuron<T>* in;
		Neuron<T>* out;
		T wgt;
		T lastVal;
		
		public:
		PositiveSynapse(Neuron<T>* up, Neuron<T>* down, T wgt);
		PositiveSynapse(Neuron<T>* up, Neuron<T>* down);
		
		virtual void propagate(T value) const override;
		
	};
	
}
}
}
#include "PositiveSynapse.hpp"