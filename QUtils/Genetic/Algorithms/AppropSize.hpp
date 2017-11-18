#pragma once

#include <type_traits>
#include <memory>

namespace QUtils
{
namespace Genetic
{
namespace Helpers
{
	template <class T>
	struct UnitSize
	{
		private:
		typedef decltype(std::declval<T>().get()) STL;
		
		public:
		constexpr static size_t size = sizeof(typename STL::value_type);
	};
	
	template <class T>
	struct UnitSize<T&> : public UnitSize<T>
	{ };
	
	template <class T>
	struct UnitSize<const T> : public UnitSize<T>
	{ };
	
	template <class T>
	struct UnitSize<volatile T> : public UnitSize<T>
	{ };
	
	template <class T>
	struct UnitSize<std::shared_ptr<T>> : public UnitSize<T>
	{ };
}
}
}