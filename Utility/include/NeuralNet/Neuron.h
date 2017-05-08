#pragma once

#include "Synapse.h"

#include <Math/Matrix.h>
#include <vector>

namespace Util
{
namespace NeuralNet
{
	class Neuron
	{
		private:
		
		protected:
		std::vector<Synapse*> in;
		std::vector<Synapse*> out;
		
		Math::matrix_t<1, long double> value;
		Math::matrix_t<1, long double> hidden;
		
		public:
		
		virtual ~Neuron();
		
		virtual void AddDown(Neuron*, long double wgt);
		
		std::vector<Neuron*> getAllDown() const;
		
		
	};
	
	class OutputNeuron : public Neuron
	{
		private:
		
		protected:
		
		public:
		
	};
	
	class InputNeuron : public Neuron
	{
		private:
		
		protected:
		
		public:
		
	};
	
}
}