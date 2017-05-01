#pragma once

namespace Util
{
namespace Math
{
	
	template <int Dims, typename Elem, typename Index>
	class Matrix;
	
	template <int Dims, typename Elem, typename Index>
	class _MatrixBase_
	{
		private:
		
		protected:
		
		
		
		public:
		Index size[Dims];
		
		_MatrixBase_() : size()
		{
			
		}
		
		
		virtual std::string toString() const = 0;
		
		template <typename Num>
		Matrix<Dims, Elem, Index>* operator*(const Num n)
		{
			return mul(n);
		}
		
		virtual Matrix<Dims, Elem, Index>* mul(const double) = 0;
		
		virtual Matrix<Dims, Elem, Index>* operator+(const Matrix<Dims, Elem, Index>& mat)
		{
			return add(mat);
		}
		
		virtual Matrix<Dims, Elem, Index>* add(const Matrix<Dims, Elem, Index>&) = 0;
		
		virtual Matrix<Dims, Elem, Index>* operator-(const Matrix<Dims, Elem, Index>& mat)
		{
			return sub(mat);
		}
		
		virtual Matrix<Dims, Elem, Index>* sub(const Matrix<Dims, Elem, Index>&) = 0;
		
		
		virtual Matrix<Dims, Elem, Index>* clone() const = 0;
		
		
		
	};
	
	
	namespace _Helpers
	{
	
	
	template <int N, typename T, typename ...Args>
	struct TupleBuilder
	{
		typedef typename TupleBuilder<N-1, T, T, Args...>::value value;
	};
	
	template <typename T, typename ...Args>
	struct TupleBuilder<0, T, Args...>
	{
		typedef std::tuple<Args...> value;
	};
	
	}
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index = int>
	class Matrix : public _MatrixBase_<Dims, Elem, Index>
	{
		private:
		
		protected:
		
		public:
		Matrix() : _MatrixBase_<Dims, Elem, Index>() { }
		virtual ~Matrix() { }
		
		virtual Matrix<Dims-1, Elem, Index>* operator[](Index i) = 0;
		
		virtual Matrix<Dims-1, Elem, Index>* at(Index i)
		{
			return (*this)[i];
		}
		
		virtual Matrix<Dims, Elem, Index>* T() const = 0;
		virtual Matrix<Dims, Elem, Index>* submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const = 0;
		
	};
	
	template <typename Elem, typename Index>
	class Matrix<1, Elem, Index> : public _MatrixBase_<1, Elem, Index>
	{
		private:
		
		protected:
		
		public:
		Matrix() : _MatrixBase_<1, Elem, Index>() {}
		virtual ~Matrix() { }
		
		virtual Elem operator[](Index i) = 0;
		
		virtual Elem at(Index i)
		{
			return (*this)[i];
		}
		
		virtual Matrix<2, Elem, Index>* T() const = 0;
		virtual Matrix<1, Elem, Index>* submatrix(std::tuple<Index>) const = 0;
		
	};
}
}

#include "FuncMatrix.h"

#include "matrix_t.h"