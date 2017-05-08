#pragma once

#include "Neuron.h"

#include <vector>
#include <functional>

namespace Util
{
namespace NeuralNet
{
	class Net
	{
		private:
		
		protected:
		std::vector<InputNeuron*> input_n;
		std::vector<OutputNeuron*> output_n;
		
		std::vector<Math::matrix_t<1, long double>> trainingIn;
		std::vector<Math::matrix_t<1, long double>> trainingOut;
		
		std::function<long double(long double)> act;
		std::function<long double(long double)> actDeriv;
		
		public:
		Net(int inputSize, int outputSize, 
		std::function<long double(long double)> actFunc = [](long double x)
		{
			return ((x < 0) ? (-1*x*x) : (x * x));
		},
		std::function<long double(long double)> actDerivFunc = [](long double x)
		{
			return ((x < 0) ? (-2*x) : (2*x));
		});
		
		virtual ~Net();
		
		
		void grow(int duplicateThreshold = 2);
		
		long double train();
		
		void addTrainData(Math::matrix_t<1, long double> in, Math::matrix_t<1, long double> out);
		
	};
	
}
}