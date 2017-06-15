#pragma once


#include "Neuron.h"
#include <QUtils/Exception/NotImplemented.h>
#include <algorithm>
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
	void Neuron<T>::addDown(Neuron<T>* n, T wgt)
	{
		auto syn = new Synapse<T>(this, n, wgt);
		this->out.push_back(syn);
		n->addUp(syn);
	}
	
	template <typename T>
	void Neuron<T>::addDown(Neuron<T>* n)
	{
		addDown(n, static_cast<T>(Internal::RandWgt::Get()));
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
	void Neuron<T>::addUp(Neuron<T>* n, T wgt)
	{
		auto syn = new Synapse<T>(n, this, wgt);
		this->in.push_back(syn);
		n->addDown(syn);
	}
	
	template <typename T>
	void Neuron<T>::addUp(Neuron<T>* n)
	{
		auto syn = new Synapse<T>(n, this);
		this->in.push_back(syn);
		n->addDown(syn);
	}
	
	template <typename T>
	Synapse<T>* Neuron<T>::removeUp(Synapse<T>* syn)
	{
		auto loc = std::find(in.begin(), in.end(), syn);
		if (loc != in.end())
		{
			auto s = *loc;
			in.erase(loc);
			return s;
		}
		return NULL;
	}
	
	template <typename T>
	Synapse<T>* Neuron<T>::removeDown(Synapse<T>* syn)
	{
		auto loc = std::find(out.begin(), out.end(), syn);
		if (loc != out.end())
		{
			auto s = *loc;
			out.erase(loc);
			return s;
		}
		return NULL;
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
			allNeurons.push_back(syn->get_out());
		}
		
		if (neuronPresent(allNeurons, this))
		{
			throw NotImp();
			//TODO: Handle circular net
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
	void Neuron<T>::backPropagate(T delta_out_sum, const T& learningRate)
	{
		T delta_sum = this->act_D(this->hidden)*delta_out_sum;
		for (auto syn : this->in)
		{
			syn->backPropagate(delta_sum, learningRate);
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
	void OutputNeuron<T>::backPropagate(T err, const T& learningRate)
	{
		auto delta_sum = this->act_D(this->hidden)*err;
		
		for (auto syn : this->in)
		{
			syn->backPropagate(delta_sum, learningRate);
		}
	}
	
	
	
	
	
	
	template <typename T>
	InputNeuron<T>::InputNeuron(T init) : Neuron<T>(init, [](T t) -> T { return t; }, [](T) -> T { return 1; })
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
	void InputNeuron<T>::backPropagate(T err, const T& learningRate)
	{
		//Intentionally blank
	}
}
}