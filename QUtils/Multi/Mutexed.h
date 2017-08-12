#pragma once
#include <mutex>
#include <type_traits>
#include <QUtils/Types/OperatorForwarding.h>



namespace QUtils
{
namespace Multi
{
	template <class T>
	class Mutexed;
	
	namespace Internal
	{
		template <class T, bool V>
		class IsMutexedClass
		{
			public:
			IsMutexedClass(Mutexed<T>*) {}
		};
		
		template <class T>
		class IsMutexedClass<T, true>
		{
			private:
			Mutexed<T>* ptr;
			public:
			
			IsMutexedClass(Mutexed<T>* ptr) : ptr(ptr) {}
			
			template <class Ret, class... Args>
			Ret run(Ret(T::*)(Args...), Args...);
			
			template <class... Args>
			void run(void(T::*)(Args...), Args...);
		};
		
		template <class T>
		class MutexedClass : public IsMutexedClass<T, std::is_class<typename std::decay<T>::type>::value>
		{
			public:
			MutexedClass(Mutexed<T>* ptr) : IsMutexedClass<T, std::is_class<typename std::decay<T>::type>::value>(ptr)
			{}
		};
	}
	
	
	template <class T>
	class Mutexed : public Internal::MutexedClass<T>, public Types::AllOperatorForward<typename std::decay<T>::type>
	{
		private:
		
		protected:
		typedef typename std::decay<T>::type type;
		std::mutex mut;
		type t;
		
		
		
		public:
		template <class ...Args>
		Mutexed(Args... args);
		
		
		type& operator*();
		type* operator->();
		const type& operator*() const;
		const type* operator->() const;
		
		bool try_lock();
		void lock();
		void unlock();
		
		Mutexed<T>& operator=(const type t)
		{
			auto ptr = (*this).operator->();
			*ptr = t;
			return *this;
		}
		
		operator T()
		{
			T value = **this;
			return value;
		}
		
		template <class G, bool B>
		friend class Internal::IsMutexedClass;
	};
	
	
	
	
	
}
}

#include "Mutexed.hpp"