#pragma once

#include "File.h"

namespace QUtils { namespace Dbc {
	
	namespace UniqueKey_Helper
	{
		template <class Arr_t, int N, class T, class... Index>
		struct FillArray
		{
			static void call(Arr_t* arr, const T val, const Index... index)
			{
				arr[N] = val;
				FillArray<Arr_t, N+1, Index...>::call(arr, index...);
			}
		};
		
		template <class Arr_t, int N, class T>
		struct FillArray<Arr_t, N, T>
		{
			static void call(Arr_t* arr, const T val)
			{
				arr[N] = val;
			}
		};
	}
	
	/*template <class... Index>
	bool DbcFile::uniqueKey(const Index... index) const
	{
		constexpr size_t count = sizeof...(Index);
		size_t* arr = new size_t[count];
		UniqueKey_Helper::FillArray<size_t, 0, Index...>::call(arr, index...);
		bool b = this->uniqueKey(arr, count);
		delete[] arr;
		return b;
	}*/
}
}