#pragma once

#include "Synapse.h"

#include <vector>
#include <functional>

namespace QUtils
{
namespace NeuralNet
{
	template <typename T>
	class Neuron
	{
		private:
		protected:
		std::vector<Synapse<T>*> in;
		std::vector<Synapse<T>*> out;
		
		std::function<T(T)> act;
		std::function<T(T)> act_D;
		
		T value;
		T hidden;
		bool set;
		
		int received;
		
		public:
		Neuron(T init, std::function<T(T)> act, std::function<T(T)> act_D);
		Neuron(std::function<T(T)> act, std::function<T(T)> act_D) : Neuron(0, act, act_D) {}
		virtual ~Neuron();
		
		virtual void addDown(Neuron<T>*, T wgt);
		virtual void addDown(Neuron<T>*);
		virtual void addDown(Synapse<T>*);
		virtual void addUp(Synapse<T>*);
		virtual void addUp(Neuron<T>*, T wgt);
		virtual void addUp(Neuron<T>*);
		
		virtual Synapse<T>* removeUp(Synapse<T>*);
		virtual Synapse<T>* removeDown(Synapse<T>*);
		virtual std::vector<Synapse<T>*> getOuts() const { return out; }
		virtual std::vector<Synapse<T>*> getIns() const { return in; }
		
		std::vector<Neuron<T>*> getAllDown() const;
		
		virtual void reset(T init);
		
		virtual void propagate(T val);
		
		virtual void backPropagate(T err, const T& learningRate);
		
		template <typename G>
		friend class Synapse;
		
	};
	
	template <typename T>
	class OutputNeuron : public Neuron<T>
	{
		private:
		
		protected:
		
		public:
		OutputNeuron(T init, std::function<T(T)>, std::function<T(T)>);
		OutputNeuron(std::function<T(T)> act, std::function<T(T)> act_D) : OutputNeuron(0, act, act_D) {}
		
		const std::vector<Synapse<T>*>& incoming() const;
		
		virtual const T get() const;
		virtual void backPropagate(T err, const T& learningRate) override;
		
	};
	
	template <typename T>
	class InputNeuron : public Neuron<T>
	{
		private:
		
		protected:
		
		public:
		InputNeuron(T init);
		InputNeuron() : InputNeuron(0) {}
		
		
		virtual void set(T value);
		virtual void propagate();
		virtual void backPropagate(T err, const T& learningRate) override;
	};
	
}
}
#include "Neuron.hpp"