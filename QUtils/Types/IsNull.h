#pragma once

#include <memory>

namespace QUtils
{
namespace Types
{
	namespace Helpers
	{
		template <class T>
		struct IsNull
		{
			inline static bool call(T t)
			{
				return false;
			}
		};
		
		template <class T>
		struct IsNull<T*>
		{
			inline static bool call(T* t)
			{
				return (t == nullptr);
			}
		};
		
		template <class T>
		struct IsNull<std::shared_ptr<T>>
		{
			inline static bool call(std::shared_ptr<T> t)
			{
				return (t == nullptr);
			}
		};
	}
	
	template <class T>
	inline bool IsNull(T t)
	{
		return Helpers::IsNull<T>::call(t);
	}
}
}
	