#include "Func.h"
#include <cstdlib>

namespace Util
{
	template <typename Result, typename ...Args>
	Func<Result, Args...>::Func(ptr_type ptr) : ptr(ptr)
	{
		
	}
	
	template <typename Result, typename ...Args>
	Func<Result, Args...>::Func() : Func(NULL)
	{
		
	}
	
	template <typename Result, typename ...Args>
	Result Func<Result, Args...>::operator()(Args... args)
	{
		if (ptr == NULL)
		{
			//TODO
			//throw exception
		}
		return exec(args...);
	}
	

	template <typename Result, typename ...Args>
	Result Func<Result, Args...>::exec(Args... args)
	{
		return (*this->ptr)(args...);
	}
	
	
	
	template <typename Base, typename Result, typename ...Args>
	MemberFunc<Base, Result, Args...>::MemberFunc(Base* obj, ptr_type ptr) : ptr(ptr), obj(obj)
	{
		
	}
	
	
	
	
	template <typename Base, typename Result, typename ...Args>
	Result MemberFunc<Base, Result, Args...>::exec(Args... args)
	{
		return (obj->*(this->ptr))(args...);
	}
}