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
		Index size[Dims];
		
		
		public:
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
		
	};
}
}

#include "FuncMatrix.h"

#include "matrix_t.h"