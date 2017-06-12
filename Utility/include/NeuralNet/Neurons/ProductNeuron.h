#pragma once

#include "../Neuron.h"

namespace Util
{
namespace NeuralNet
{
namespace Neurons
{
	template <typename T>
	class ProductNeuron : public Neuron<T>
	{
		private:
		protected:
		
		public:
		ProductNeuron(T init);
		ProductNeuron() : ProductNeuron(static_cast<T>(1)) {}
		virtual ~ProductNeuron();
		
		
		
		
		virtual void reset(T init) override;
		
		virtual void propagate(T val) override;
		
		virtual void backPropagate(T err, const T& learningRate) override;
		
		template <typename G>
		friend class Synapse;
		
	};
}
}
}
#include "ProductNeuron.hpp"