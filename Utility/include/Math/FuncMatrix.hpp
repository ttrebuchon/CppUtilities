#pragma once

#include "FuncMatrix.h"
#include <iostream>

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
	
	template <int Dims, typename Elem, typename Index>
	std::string FuncMatrix<Dims, Elem, Index>::toString() const
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::mul(const double)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::add(const Matrix<Dims, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::sub(const Matrix<Dims, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::clone() const
	{
		return new FuncMatrix(*this);
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
	
	
	template <typename Elem, typename Index>
	std::string FuncMatrix<1, Elem, Index>::toString() const
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::mul(const double)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::add(const Matrix<1, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::sub(const Matrix<1, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::clone() const
	{
		return new FuncMatrix(*this);
	}
	
	
	
	
	
}
}