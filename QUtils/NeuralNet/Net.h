#pragma once

#include "Neuron.h"

#include <vector>
#include <functional>
#include <cmath>
#include <limits>

namespace QUtils
{
namespace NeuralNet
{
	
	enum LayerType
	{
		FullyConnected = 0,
		OneToOne = 1,
		Unique = 2,
		
		
	};
	
	
	template <typename T>
	struct Bounds
	{
		T min;
		T max;
	};

	template <typename T>
	class Net
	{
		private:
		typedef std::function<T(T)> Activation_t;
		
		typedef std::vector<T> InOut;
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
		T learningRate;
		Bounds<T> bounds;

		Net(int inputSize, int outputSize,
		T learningRate = 1, 
		std::function<T(T)> actFunc = [](T x) -> T
		{
			return ((T)1)/(1 + exp(x*(T)-1));
		},
		std::function<T(T)> actDerivFunc = [](T x) -> T
		{
			return ((T)1)/(1 + exp(x*(T)-1))*(1 - ((T)1)/(1 + exp(x*(T)-1)));
		},
		T lowBound = (std::numeric_limits<T>()).lowest(),
		T upBound = (std::numeric_limits<T>()).max());
		
		virtual ~Net();
		
		
		void grow(int newLayers, double multiplier = 1, LayerType = FullyConnected);
		
		template <typename List = std::vector<T>>
		void addData(List input, List output);
		void train(int cycles = 100);
		
		template <typename List = std::vector<T>>
		std::vector<T> go(List input);
		
		void setOutputActivation(Activation_t act, Activation_t deriv);
		
		std::vector<InputNeuron<T>*> inputLayer() const;
		
		std::vector<OutputNeuron<T>*> outputLayer() const;
		
		std::vector<Neuron<T>*> all() const;
		
		std::string toString() const;
	};
	
}
}

#include "Net.hpp"