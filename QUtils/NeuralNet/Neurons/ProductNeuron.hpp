#pragma once


#include "ProductNeuron.h"
#include <QUtils/Exception/NotImplemented.h>
#include <algorithm>
namespace Util
{
namespace NeuralNet
{
namespace Neurons
{
	
	template <typename T>
	ProductNeuron<T>::ProductNeuron(T init) : Neuron<T>(init, [](T v) { return v; }, [](T) -> T { return static_cast<T>(1); })
	{
		
	}
	
	template <typename T>
	ProductNeuron<T>::~ProductNeuron()
	{
		//TODO
	}
	
	
	
	
	
	template <typename T>
	void ProductNeuron<T>::reset(T init)
	{
		Neuron<T>::reset(init);
		if (init == 0)
		{
			this->value = this->hidden = 1;
		}
		
	}
	
	
	template <typename T>
	void ProductNeuron<T>::propagate(T val)
	{
		this->set = true;
		this->hidden = this->hidden*val;
		this->received++;
		if (this->received == this->in.size())
		{
			this->value = this->hidden;
			for (auto next : this->out)
			{
				next->propagate(this->value);
			}
		}
	}
	
	template <typename T>
	void ProductNeuron<T>::backPropagate(T delta_out_sum, const T& learningRate)
	{
		for (auto syn : this->in)
		{
			syn->backPropagate((syn->lastValue() != 0 ? this->value/syn->lastValue() : 0)*delta_out_sum, learningRate);
		}
	}
	
}
}
}