#pragma once


#include "PositiveSynapse.h"

namespace Util
{
namespace NeuralNet
{
namespace Synapses
{
	template <typename T>
	PositiveSynapse<T>::PositiveSynapse(Neuron<T>* up, Neuron<T>* down, T wgt) : Synapse<T>(up, down, wgt)
	{
		
	}
	
	template <typename T>
	PositiveSynapse<T>::PositiveSynapse(Neuron<T>* up, Neuron<T>* down) : PositiveSynapse<T>(up, down, static_cast<T>(Internal::RandWgt::Get()))
	{ }
	
	
	
	template <typename T>
	void PositiveSynapse<T>::propagate(T value) const
	{
		if (this->wgt < 0)
		{
			((PositiveSynapse<T>*)this)->wgt = 0;
		}
		Synapse<T>::propagate(value);
		
	}
	
}
}
}