#pragma once

#include "FuncMatrix.h"

namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index>
	FuncMatrix<Dims, Elem, Index>::FuncMatrix(Func f) : Matrix<Dims, Elem, Index>(), def(f)
	{
		
	};
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims-1, Elem, Index>* FuncMatrix<Dims, Elem, Index>::operator[](Index i)
	{
		return new FuncMatrix<Dims-1, Elem, Index>(([=](auto ...args) -> Elem { return def(i, args...); }));
	}
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	FuncMatrix<1, Elem, Index>::FuncMatrix(std::function<Elem(Index)> f) : Matrix<1, Elem, Index>(), def(f)
	{
		
	}
	
	template <typename Elem, typename Index>
	Elem FuncMatrix<1, Elem, Index>::operator[](Index i)
	{
		return def(i);
	}
		
	
	
	
	
}
}