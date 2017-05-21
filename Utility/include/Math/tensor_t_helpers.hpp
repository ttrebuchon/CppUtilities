#pragma once

namespace Util
{
namespace Math
{
namespace _Helpers
{
namespace _tensor_t
{
	template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index, int Args>
	struct MultiIndexRetType
	{
		static_assert(Dims >= Args, "Too many indexes for tensor type");
		typedef typename MultiIndexRetType<Obj, Dims-1, Elem, Index, Args-1>::type type;
	};
	
	template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index>
	struct MultiIndexRetType<Obj, Dims, Elem, Index, 0>
	{
		typedef Obj<Dims, Elem, Index> type;
	};
	
	template <template <int, typename...> typename Obj, typename Elem, typename Index>
	struct MultiIndexRetType<Obj, 0, Elem, Index, 0>
	{
		typedef Elem type;
	};











	constexpr int transposeDims(int dims)
	{
		return (dims == 1) ? 2 : dims;
	}
}
}
}
}