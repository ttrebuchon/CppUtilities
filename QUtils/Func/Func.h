#ifndef INCLUDED_UTIL_FUNC_H
#define INCLUDED_UTIL_FUNC_H

#include <type_traits>

namespace QUtils
{
	
	template <typename Result, typename ...Args>
	class Func
	{
		private:
		
		typedef Result(*ptr_type)(Args...);
		
		
		ptr_type ptr;
		protected:
		
		
		
		virtual Result exec(Args...);
		
		public:
		
		Func(ptr_type ptr);
		Func();
		
		Result operator()(Args...);
		
		bool isNull()
		{
			return (ptr == nullptr);
		}
		
	};
	
	template <typename Base, typename Result, typename ...Args>
	class MemberFunc : public Func<Result, Args...>
	{
		private:
		typedef Result(Base::*ptr_type)(Args...);
		ptr_type ptr;
		Base* obj;
		
		
		protected:
		
		Result exec(Args...) override;
		
		public:
		
		MemberFunc(Base* b, ptr_type ptr);
		
	};
}


#include "Func.hpp"
#endif