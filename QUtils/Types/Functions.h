#pragma once

#include "Void_t.h"

namespace QUtils
{
namespace Types
{
	
	namespace Helpers
	{
		template <class Func, class... Args>
		struct CallerTypesHolder
		{};
		
		
		
		template <class Holder, class = void>
		struct CanCallWith : public std::false_type
		{
			typedef std::false_type type;
		};
		
		template <class Func, class... Args>
		struct CanCallWith<CallerTypesHolder<Func, Args...>, void_t<decltype(std::declval<Func>()((std::declval<Args>())...))>> : public std::true_type
		{
			typedef decltype(std::declval<Func>()((std::declval<Args>())...)) ReturnType;
			typedef std::true_type type;
		};
		
		template <class Func, class BoolType, class... Args>
		struct CallWithOptional_Helper
		{
			typedef decltype(std::declval<Func>()((std::declval<Args>())...)) ReturnType;
			static ReturnType call(Func f, Args... args)
			{
				return f(args...);
			}
		};
		
		template <class Func, class... Args>
		struct CallWithOptional_Helper<Func, std::false_type, Args...>
		{
			typedef decltype(std::declval<Func>()()) ReturnType;
			static ReturnType call(Func f, Args... args)
			{
				return f();
			}
		};
		
	}
	
	
	template <class Func, class... Args>
	struct CallWithOptional
	{
		//private:
		typedef typename Helpers::CanCallWith<Helpers::CallerTypesHolder<Func, Args...>>::type ValueType;
		typedef Helpers::CallWithOptional_Helper<Func, ValueType, Args...> HelperClass;
		
		public:
		typedef typename HelperClass::ReturnType ReturnType;
		
		static ReturnType call(Func f, Args... args)
		{
			return HelperClass::call(f, args...);
		}
	};
}
}