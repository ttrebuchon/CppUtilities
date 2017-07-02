#pragma once
#include <mutex>
#include <type_traits>
#include <QUtils/Types/OperatorForwarding.h>


namespace QUtils
{
namespace Multi
{
	
	template <class T>
	class Mutexed : public Types::IndexerForward<typename std::decay<T>::type>
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
		
	};
	
	
	
}
}

#include "Mutexed.hpp"