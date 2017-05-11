#pragma once

#include "Neuron.h"

#include <vector>
#include <functional>
#include <cmath>
#include <iostream>

namespace Util
{
namespace NeuralNet
{
	template <typename T>
	class Net
	{
		private:
		typedef std::function<T(T)> Activation_t;
		
		typedef Math::matrix_t<1, T> InOut;
		int inSize;
		int outSize;
		
		protected:
		
		std::vector<std::tuple<InOut, InOut>> training;
		
		std::vector<InputNeuron<T>*> input_n;
		std::vector<OutputNeuron<T>*> output_n;
		
		Activation_t activation;
		Activation_t activation_D;
		
		virtual void reset(T init);
		virtual void reset() { reset(0); }
		
		
		public:
		Net(int inputSize, int outputSize, 
		std::function<T(T)> actFunc = [](T x) -> T
		{
			return ((T)1)/(1 + exp(x*(T)-1));
		},
		std::function<T(T)> actDerivFunc = [](T x) -> T
		{
			return ((T)1)/(1 + exp(x*(T)-1))*(1 - ((T)1)/(1 + exp(x*(T)-1)));
		});
		
		virtual ~Net();
		
		
		void grow(int newLayers, int multiplier = 1);
		
		template <typename List = std::vector<T>>
		void addData(List input, List output);
		void train(int cycles = 100);
		
		template <typename List = std::vector<T>>
		Math::matrix_t<1, T> go(List input);
	};
	
}
}

#include "Net.hpp"