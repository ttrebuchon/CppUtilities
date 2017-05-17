#pragma once

#include <Exception/Exception.h>

namespace Util
{
namespace Math
{
	
	UTIL_CUSTOM_EXCEPTION(MatrixInvalidSizeException, );

	struct Matrix_Counter
	{
		static int alive;
	};
	
	
	
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
			for (auto i = 0; i < Dims; i++)
			{
				size[i] = -1;
			}
			Matrix_Counter::alive++;
		}

		virtual ~_MatrixBase_() { Matrix_Counter::alive--; }
		
		virtual std::string imp() const = 0;
		
		
		template <typename Num>
		Matrix<Dims, Elem, Index>* operator*(const Num n)
		{
			return mul(n);
		}
		
		virtual Matrix<Dims, Elem, Index>* operator+(const Matrix<Dims, Elem, Index>& mat)
		{
			return add(mat);
		}
		
		virtual Matrix<Dims, Elem, Index>* operator-(const Matrix<Dims, Elem, Index>& mat)
		{
			return sub(mat);
		}
		
		virtual int rank() const
		{
			return Dims;
		}
		
		
		
		virtual std::string toString() const = 0;
		
		virtual Matrix<Dims, Elem, Index>* mul(const double) = 0;
		
		virtual Matrix<Dims, Elem, Index>* mul(const Matrix<Dims, Elem, Index>&) = 0;
		
		virtual Matrix<Dims, Elem, Index>* mul(const Matrix<Dims, Elem, Index>* m)
		{
			return mul(*m);
		}
		
		virtual Matrix<Dims, Elem, Index>* add(const Matrix<Dims, Elem, Index>&) = 0;
		
		virtual Matrix<Dims, Elem, Index>* add(const Matrix<Dims, Elem, Index>* m)
		{
			return add(*m);
		}
		
		virtual Matrix<Dims, Elem, Index>* sub(const Matrix<Dims, Elem, Index>&) = 0;
		
		virtual Matrix<Dims, Elem, Index>* sub(const Matrix<Dims, Elem, Index>* m)
		{
			return sub(*m);
		}
		
		virtual Elem det() const = 0;
		
		virtual Matrix<Dims, Elem, Index>* clone() const = 0;
		
		
		
		template <int otherDims, typename otherElem, typename otherIndex>
		friend class _MatrixBase_;
		
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
		
		virtual std::string toString() const override;
		
		virtual Matrix<Dims-1, Elem, Index>* operator[](Index i) const = 0;
		
		virtual Matrix<Dims-1, Elem, Index>* at(Index i) const
		{
			return (*this)[i];
		}
		
		virtual Matrix<Dims, Elem, Index>* T() const = 0;
		virtual Matrix<Dims, Elem, Index>* submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const = 0;
		
		template <int Dims2>
		Matrix<Dims+Dims2-2, Elem, Index>* contract(Matrix<Dims2, Elem, Index>*);
		#undef minor
		virtual Elem minor(typename _Helpers::TupleBuilder<Dims, Index>::value) const;
		
		virtual Elem det() const override;
		
		template <int Dims2>
		void append(Matrix<Dims2, Elem, Index>*);
		
	};
	
	template <typename Elem, typename Index>
	class Matrix<1, Elem, Index> : public _MatrixBase_<1, Elem, Index>
	{
		private:
		
		protected:
		
		public:
		Matrix() : _MatrixBase_<1, Elem, Index>() {}
		virtual ~Matrix() { }
		
		virtual std::string toString() const override;
		
		virtual Elem operator[](Index i) const = 0;
		
		virtual Elem at(Index i) const
		{
			return (*this)[i];
		}
		
		virtual Matrix<2, Elem, Index>* T() const = 0;
		virtual Matrix<1, Elem, Index>* submatrix(std::tuple<Index>) const = 0;
		
		virtual Elem det() const override;
		
		virtual void append(Elem value) = 0;
		
	};
	
	template <int Dims1, int Dims2, typename Elem, typename Index, template <int, typename, typename> typename T, template <int, typename, typename> typename H>
	Matrix<Dims1+Dims2-2, Elem, Index>* MatrixContract(T<Dims1, Elem, Index>*, H<Dims2, Elem, Index>*);
}
}
#include "Matrix.hpp"
#include "FuncMatrix.h"
#include "DataMatrix.h"

#include "matrix_t.h"
