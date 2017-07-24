#pragma once

#include "Mutexed.h"


namespace QUtils
{
namespace Multi
{
	
	template <class T>
	template <class ...Args>
	Mutexed<T>::Mutexed(Args... args) : Internal::MutexedClass<T>(this), Types::AllOperatorForward<typename Mutexed<T>::type>(NULL), mut(), t(args...)
	{
		this->Types::AllOperatorForward<type>::set(&t);
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
	
	namespace Internal
	{
		template <class T>
		template <class Ret, class... Args>
		Ret IsMutexedClass<T, true>::run(Ret(T::*func)(Args...), Args... args)
		{
			ptr->lock();
			Ret r = (ptr->t.*func)(args...);
			ptr->unlock();
			return r;
		}
		
		template <class T>
		template <class... Args>
		void IsMutexedClass<T, true>::run(void(T::*func)(Args...), Args... args)
		{
			ptr->lock();
			(ptr->t.*func)(args...);
			ptr->unlock();
		}
		
	}
	
	
	
}
}