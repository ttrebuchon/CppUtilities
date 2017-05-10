#pragma once


#include "Neuron.h"
#include <Exception/NotImplemented.h>
#include <iostream>
namespace Util
{
namespace NeuralNet
{
	
	template <typename T>
	Neuron<T>::Neuron(T init, std::function<T(T)> act, std::function<T(T)> act_D) : in(), out(), act(act), act_D(act_D), value(init), hidden(init), set(false), received(0)
	{
		
	}
	
	template <typename T>
	Neuron<T>::~Neuron()
	{
		//TODO
	}
	
	template <typename T>
	void Neuron<T>::addDown(Neuron<T>* n, long double wgt)
	{
		auto syn = new Synapse<T>(this, n, wgt);
		this->out.push_back(syn);
		n->addUp(syn);
	}
	
	template <typename T>
	void Neuron<T>::addDown(Synapse<T>* syn)
	{
		this->out.push_back(syn);
	}
	
	template <typename T>
	void Neuron<T>::addUp(Synapse<T>* syn)
	{
		this->in.push_back(syn);
	}
	
	template <typename T>
	void Neuron<T>::removeUp(Synapse<T>* syn)
	{
		throw NotImp();
	}
	
	template <typename T>
	void Neuron<T>::removeDown(Synapse<T>* syn)
	{
		throw NotImp();
	}
	
	template <typename T>
	std::vector<Neuron<T>*> Neuron<T>::getAllDown() const
	{
		auto neuronPresent = [] (std::vector<Neuron<T>*> v, const Neuron<T>* n) -> bool
		{
			auto it = std::find(v.begin(), v.end(), n);
			return (it != v.end());
		};
		
		std::vector<Neuron<T>*> allNeurons;
		
		for (auto syn : this->out)
		{
			if (syn == NULL)
			    continue;
			for (auto n : syn->get_out()->getAllDown())
			{
				if (n == NULL)
				    continue;
				if (!neuronPresent(allNeurons, n))
				{
					allNeurons.push_back(n);
				}
			}
		}
		
		if (!neuronPresent(allNeurons, this))
		{
			allNeurons.push_back((Neuron*) this);
		}
		
		return allNeurons;
	}
	
	template <typename T>
	void Neuron<T>::reset(T init)
	{
		if (!set)
		{
			return;
		}
		
		set = false;
		received = 0;
		
		this->value = this->hidden = init;
		
		for (auto syn : this->out)
		{
			syn->get_out()->reset(init);
		}
	}
	
	template <typename T>
	void Neuron<T>::propagate(T val)
	{
		set = true;
		hidden = hidden + val;
		received++;
		if (received == in.size())
		{
			this->value = act(hidden);
			for (auto next : this->out)
			{
				next->propagate(this->value);
			}
		}
	}
	
	template <typename T>
	void Neuron<T>::backPropagate(T delta_out_sum)
	{
		auto delta_sum = this->act_D(this->hidden)*delta_out_sum;
		for (auto syn : this->in)
		{
			syn->backPropagate(delta_sum);
		}
	}
	
	
	
	
	
	
	
	
	
	
	template <typename T>
	OutputNeuron<T>::OutputNeuron(T init, std::function<T(T)> act, std::function<T(T)> act_D) : Neuron<T>(init, act, act_D)
	{
		
	}
	
	template <typename T>
	const std::vector<Synapse<T>*>& OutputNeuron<T>::incoming() const
	{
		return this->in;
	}
	
	template <typename T>
	const T OutputNeuron<T>::get() const
	{
		return this->value;
	}
	
	template <typename T>
	void OutputNeuron<T>::backPropagate(T err)
	{
		auto delta_sum = this->act_D(this->hidden)*err;
		
		for (auto syn : this->in)
		{
			syn->backPropagate(delta_sum);
		}
	}
	
	
	
	
	
	
	template <typename T>
	InputNeuron<T>::InputNeuron(T init, std::function<T(T)> act, std::function<T(T)> act_D) : Neuron<T>(init, act, act_D)
	{
		
	}
	
	template <typename T>
	void InputNeuron<T>::set(T value)
	{
		this->value = value;
		Neuron<T>::set = true;
	}
	
	template <typename T>
	void InputNeuron<T>::propagate()
	{
		for (auto syn : this->out)
		{
			syn->propagate(this->value);
		}
	}
	
	template <typename T>
	void InputNeuron<T>::backPropagate(T err)
	{
		//Intentionally blank
	}
}
}