#pragma once

#include "RandWgt.h"
#include <string>

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
		T lastVal;
		
		public:
		Synapse(Neuron<T>* up, Neuron<T>* down, T wgt);
		Synapse(Neuron<T>* up, Neuron<T>* down);
		
		virtual ~Synapse();
		
		virtual Neuron<T>* get_out() const;
		virtual Neuron<T>* get_in() const;
		
		virtual void remove();
		virtual void propagate(T value) const;
		virtual void backPropagate(T delta_sum, const T& learningRate);
		
		T lastValue() const { return lastVal; }
		
		virtual std::string toString() const;
		
	};
	
}
}
#include "Synapse.hpp"