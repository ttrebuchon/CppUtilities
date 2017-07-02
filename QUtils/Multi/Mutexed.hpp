#pragma once

#include "Mutexed.h"


namespace QUtils
{
namespace Multi
{
	template <class T>
	template <class ...Args>
	Mutexed<T>::Mutexed(Args... args) : Types::IndexerForward<typename Mutexed<T>::type>(NULL), mut(), t(args...)
	{
		this->Types::IndexerForward<type>::ptr = &t;
	}
	
	template <class T>
	typename Mutexed<T>::type& Mutexed<T>::operator*()
	{
		if (this->try_lock())
		{
			this->unlock();
			//TODO
			throw std::exception();
		}
		return t;
	}
	
	template <class T>
	typename Mutexed<T>::type* Mutexed<T>::operator->()
	{
		if (this->try_lock())
		{
			this->unlock();
			//TODO
			throw std::exception();
		}
		return &t;
	}
	
	template <class T>
	const typename Mutexed<T>::type& Mutexed<T>::operator*() const
	{
		if (this->try_lock())
		{
			this->unlock();
			//TODO
			throw std::exception();
		}
		return t;
	}
	
	template <class T>
	const typename Mutexed<T>::type* Mutexed<T>::operator->() const
	{
		if (this->try_lock())
		{
			this->unlock();
			//TODO
			throw std::exception();
		}
		return &t;
	}
	
	template <class T>
	bool Mutexed<T>::try_lock()
	{
		return this->mut.try_lock();
	}
	
	template <class T>
	void Mutexed<T>::lock()
	{
		return this->mut.lock();
	}
	
	template <class T>
	void Mutexed<T>::unlock()
	{
		return this->mut.unlock();
	}
}
}