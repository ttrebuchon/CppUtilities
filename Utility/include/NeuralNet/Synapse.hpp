#pragma once


#include "Synapse.h"
#include <sstream>

namespace Util
{
namespace NeuralNet
{
	template <typename T>
	Synapse<T>::Synapse(Neuron<T>* up, Neuron<T>* down, T wgt) : in(up), out(down), wgt(wgt), lastVal(wgt) //lastVal is initialized to wgt in the case that T does not have a default constructor
	{
		
	}
	
	template <typename T>
	Synapse<T>::Synapse(Neuron<T>* up, Neuron<T>* down) : Synapse<T>(up, down, static_cast<T>(Internal::RandWgt::Get()))
	{ }
	
	
	template <typename T>
	Synapse<T>::~Synapse()
	{
		//TODO
	}
	
	
	
	template <typename T>
	Neuron<T>* Synapse<T>::get_out() const
	{
		return out;
	}
	
	template <typename T>
	Neuron<T>* Synapse<T>::get_in() const
	{
		return in;
	}
	
	template <typename T>
	void Synapse<T>::remove()
	{
		in->removeDown(this);
		out->removeUp(this);
		in = nullptr;
		out = nullptr;
	}
	
	template <typename T>
	void Synapse<T>::propagate(T value) const
	{
		((Synapse<T>*)this)->lastVal = value*wgt;
		out->propagate(this->lastVal);
	}
	
	template <typename T>
	void Synapse<T>::backPropagate(T delta_sum)
	{
		T delta_wgt = delta_sum*in->value;
		
		T next_delta = ((T)wgt)*delta_sum;
		wgt = wgt + delta_wgt;
		in->backPropagate(next_delta);
	}
	
	template <typename T>
	std::string Synapse<T>::toString() const
	{
		std::stringstream ss;
		ss << in << " -> " << wgt << " -> " << out;
		return ss.str();
	}
	
}
}