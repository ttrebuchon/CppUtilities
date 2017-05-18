#pragma once


#include "Net.h"
#include <Exception/NotImplemented.h>
#include <algorithm>

#ifdef DEBUG

#include <assert.h>
#define sanity_d(x) assert(x)

#else

#define sanity_d(x)

#endif

namespace Util
{
namespace NeuralNet
{
	template <typename T>
	Net<T>::Net(int inputSize, int outputSize, Activation_t actFunc, Activation_t actDerivFunc, T lowBound, T highBound) : inSize(inputSize), outSize(outputSize), training(), input_n(inputSize), output_n(outputSize), activation(actFunc), activation_D(actDerivFunc), bounds()
	{
		this->bounds.min = lowBound;
		this->bounds.max = highBound;


		for (auto i = 0; i < inSize; i++)
		{
			input_n[i] = new InputNeuron<T>(activation, activation_D);
		}
		
		for (auto i = 0; i < outSize; i++)
		{
			output_n[i] = new OutputNeuron<T>([&] (T x) -> T {
				if (x < bounds.min)
				{
					return bounds.min;
				}
				if ( x > bounds.max)
				{
					return bounds.max;
				}
				return x;
			}, 
			[] (T x) -> T {
				return 1;
			});
		}

		

	}
	
	template <typename T>
	Net<T>::~Net()
	{
		auto neuronPresent = [] (std::vector<Neuron<T>*> v, Neuron<T>* n) -> bool
		{
			auto it = std::find(v.begin(), v.end(), n);
			return (it != v.end());
		};
		
		std::vector<Neuron<T>*> allNeurons;
		for (auto in : input_n)
		{
			if (in == NULL)
			    continue;
			
			for (auto n : in->getAllDown())
			{
				if (!neuronPresent(allNeurons, n))
				{
					allNeurons.push_back(n);
				}
			}
		}
		
		while (allNeurons.size() > 0)
		{
			delete allNeurons.back();
			allNeurons.pop_back();
		}
	}
	
	template <typename T>
	void Net<T>::reset(T init)
	{
		for (auto in : input_n)
		{
			in->reset(init);
		}
	}
	
	
	template <typename T>
	void Net<T>::grow(int layers, double multiplier)
	{
		std::vector<Neuron<T>*> currentLayer;
		for (auto outN : output_n)
		{
			for (auto syn : outN->incoming())
			{
				auto N = syn->get_in();
				syn->remove();
				delete syn;
				currentLayer.push_back(N);
			}
		}
		
		if (currentLayer.size() == 0)
		{
			for (auto inN : input_n)
			{
				currentLayer.push_back(inN);
			}
		}
		
		for (int L = 0; L < layers; L++)
		{
			std::vector<Neuron<T>*> newLayer;
			while (newLayer.size() < multiplier*currentLayer.size())
			{
				newLayer.push_back(new Neuron<T>(activation, activation_D));
			}
			
			for (auto current : currentLayer)
			{
				for (auto next : newLayer)
				{
					auto syn = new Synapse<T>(current, next);
					current->addDown(syn);
					next->addUp(syn);
				}
			}
			currentLayer = newLayer;
		}
		
		for (auto out : output_n)
		{
			for (auto current : currentLayer)
			{
				auto syn = new Synapse<T>(current, out);
					current->addDown(syn);
					out->addUp(syn);
			}
			sanity_d(out->incoming().size() > 0);
		}
	}
	
	
	
	template <typename T>
	template <typename List>
	void Net<T>::addData(List input, List output)
	{
		std::vector<T> in_v(inSize);
		std::vector<T> out_v(outSize);
		
		for (auto i = 0; i < inSize; i++)
		{
			in_v[i] = input[i];
		}
		for (auto i = 0; i < outSize; i++)
		{
			out_v[i] = output[i];
		}
		
		InOut in(std::make_shared<Math::DataMatrix<1, T>>(in_v));
		sanity_d(in_v.size() == inSize);
		sanity_d(in.size()[0] == inSize);
		
		InOut out(std::make_shared<Math::DataMatrix<1, T>>(out_v));
		sanity_d(out_v.size() == outSize);
		sanity_d(out.size()[0] == outSize);
		
		training.push_back(std::make_tuple(in, out));
	}
	
	template <typename T>
	void Net<T>::train(int cycles)
	{
		register auto tSize = training.size();
		while (cycles-- > 0)
		{
			auto& data = training[cycles % tSize];
			
			auto result = go(std::get<0>(data));
			
			auto err = std::get<1>(data) - result;
			auto i = 0;
			for (auto out : output_n)
			{
				out->backPropagate(err[i++]);
			}
		}
		
	}
	
	template <typename T>
	template <typename List>
	Math::matrix_t<1, T> Net<T>::go(List input)
	{
		reset();
		for (int i = 0; i < inSize; i++)
		{
			input_n[i]->set(input[i]);
		}
		
		for (auto N : input_n)
		{
			N->propagate();
		}
		
		std::vector<T> results;
		for (auto out : output_n)
		{
			results.push_back(out->get());
		}
		return Math::matrix_t<1, T>(std::make_shared<Math::DataMatrix<1, T>>(results));
		
	}
	
	
}
}