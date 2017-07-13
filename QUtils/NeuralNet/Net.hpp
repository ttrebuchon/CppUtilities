#pragma once


#include "Net.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Combinatorial/Combinatorial.h>
#include <algorithm>

#ifdef DEBUG

#include <assert.h>
#define sanity_d(x) assert(x)

#else

#define sanity_d(x)

#endif

namespace QUtils
{
namespace NeuralNet
{
	template <typename T>
	Net<T>::Net(int inputSize, int outputSize, T learningRate, Activation_t actFunc, Activation_t actDerivFunc, T lowBound, T highBound) : inSize(inputSize), outSize(outputSize), training(), input_n(inputSize), output_n(outputSize), activation(actFunc), activation_D(actDerivFunc), learningRate(learningRate), bounds()
	{
		this->bounds.min = lowBound;
		this->bounds.max = highBound;


		for (auto i = 0; i < inSize; i++)
		{
			input_n[i] = new InputNeuron<T>();
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
		auto allNeurons = this->all();
		std::vector<Synapse<T>*> allSyns;
		for (auto n : allNeurons)
		{
			auto syns = n->getOuts();
			for (auto syn : syns)
			{
				allSyns.push_back(syn);
			}
		}
		for (auto syn : allSyns)
		{
			syn->remove();
		}
		
		while (allNeurons.size() > 0)
		{
			delete allNeurons.back();
			allNeurons.pop_back();
		}
		while (allSyns.size() > 0)
		{
			delete allSyns.back();
			allSyns.pop_back();
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
	void Net<T>::grow(int layers, double multiplier, LayerType type)
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
			
			
			switch (type)
			{
			case FullyConnected:
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
				break;
			case OneToOne:
				while (newLayer.size() < currentLayer.size())
				{
					newLayer.push_back(new Neuron<T>(activation, activation_D));
				}
				for (auto i = 0; i < newLayer.size(); i++)
				{
					auto syn = new Synapse<T>(currentLayer[i], newLayer[i]);
					currentLayer[i]->addDown(syn);
					newLayer[i]->addUp(syn);
				}
				break;
			case Unique: {
				while (newLayer.size() < multiplier*currentLayer.size())
				{
					newLayer.push_back(new Neuron<T>(activation, activation_D));
				}
				std::vector<std::vector<Neuron<T>*>> combos;
				
				auto genCombinations = [] (auto v, int count) -> std::vector<decltype(v)> {
					std::vector<decltype(v)> r(count);
					int index = 0;
					for (int gSize = 1; gSize <= v.size(); gSize++)
					{
						for (auto& g : Combinatorial::vChooseN(v, gSize))
						{
							r[index++] = g;
							if (index == count)
							{
								return r;
							}
						}
						
						
						
					}
					return r;
				};
				combos = genCombinations(currentLayer, newLayer.size());
				
				for (auto i = 0; i < combos.size(); i++)
				{
					auto& group = combos[i];
					for (auto n : group)
					{
						auto syn = new Synapse<T>(n, newLayer[i]);
						n->addDown(syn);
						newLayer[i]->addUp(syn);
					}
				}
				}
				break;
			
			
			
			default:
			throw NotImp();
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
		std::vector<T> in(inSize);
		std::vector<T> out(outSize);
		
		for (auto i = 0; i < inSize; i++)
		{
			in[i] = input[i];
		}
		for (auto i = 0; i < outSize; i++)
		{
			out[i] = output[i];
		}
		
		sanity_d(in.size() == inSize);
		
		sanity_d(out.size() == outSize);
		
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
			
			
			InOut err(result.size());
			auto exper = std::get<1>(data);
			for (auto i = 0; i < result.size(); i++)
			{
				err[i] = exper[i] - result[i];
			}
			
			
			
			auto i = 0;
			for (auto out : output_n)
			{
				out->backPropagate(err[i++], learningRate);
			}
		}
		
	}
	
	template <typename T>
	template <typename List>
	std::vector<T> Net<T>::go(List input)
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
		return results;
		
	}
	
	
	template <typename T>
	void Net<T>::setOutputActivation(Activation_t act, Activation_t deriv)
	{
		for (auto neuron : output_n)
		{
			neuron->setFuncs(act, deriv);
		}
	}
	
	template <typename T>
	std::vector<InputNeuron<T>*> Net<T>::inputLayer() const
	{
		return input_n;
	}
	
	template <typename T>
	std::vector<OutputNeuron<T>*> Net<T>::outputLayer() const
	{
		return output_n;
	}
	
	template <typename T>
	std::vector<Neuron<T>*> Net<T>::all() const
	{
		auto neuronPresent = [] (std::vector<Neuron<T>*>& v, Neuron<T>* n) -> bool
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
			allNeurons.push_back(in);
		}
		
		return allNeurons;
	}
	
	template <typename T>
	std::string Net<T>::toString() const
	{
		auto all = this->all();
		
		std::vector<Synapse<T>*> links;
		for (auto n : all)
		{
			for (auto syn : n->getOuts())
			{
				links.push_back(syn);
			}
		}
		
		std::string str;
		if (links.size() > 0)
		{
			str += links[0]->toString();
			for (auto i = 1; i < links.size(); i++)
			{
				str += "\n" + links[i]->toString();
			}
		}
		return str;
	}
	
	
}
}