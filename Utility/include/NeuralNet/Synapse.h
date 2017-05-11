#pragma once

#include "RandWgt.h"

namespace Util
{
namespace NeuralNet
{
	template <typename T>
	class Neuron;
	
	template <typename T>
	class Synapse
	{
		private:
		
		protected:
		Neuron<T>* in;
		Neuron<T>* out;
		T wgt;
		
		public:
		Synapse(Neuron<T>* up, Neuron<T>* down, T wgt);
		Synapse(Neuron<T>* up, Neuron<T>* down);
		
		Neuron<T>* get_out() const;
		Neuron<T>* get_in() const;
		
		void remove();
		void propagate(T value) const;
		void backPropagate(T delta_sum);
		
	};
	
}
}
#include "Synapse.hpp"