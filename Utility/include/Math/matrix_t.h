#pragma once

#include "Matrix.h"
#include <iostream>
#include "FuncArgHelper.h"

namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index = int>
	class matrix_t;
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(Matrix<Dims, Elem, Index>*);
	
	
	template <int Dims, typename Elem, typename Index>
	class __Base_matrix_t_
	{
		private:
		
		protected:
		
		typedef Matrix<Dims, Elem, Index> ptr_t;
		
		Matrix<Dims, Elem, Index>* ptr = NULL;
		
		public:
		explicit __Base_matrix_t_(Matrix<Dims, Elem, Index>* ptr) : ptr(ptr) { }
		__Base_matrix_t_(const __Base_matrix_t_& m) : ptr(m.ptr->clone()) { }
		virtual ~__Base_matrix_t_() { delete ptr; }
		
		
		__Base_matrix_t_& operator=(ptr_t* _ptr)
		{
			if (this->ptr != NULL)
			{
				delete this->ptr;
			}
			this->ptr = _ptr;
			return *this;
		}
		
		__Base_matrix_t_& operator=(const __Base_matrix_t_& m)
		{
			if (ptr != NULL)
			{
				delete ptr;
			}
			if (m.ptr != NULL)
			{
				ptr = m.ptr->clone();
			}
			else
			{
				ptr = NULL;
			}
			return *this;
		}
		
		std::string toString() const
		{
			return ptr->toString();
		}
		
		
		matrix_t<Dims, Elem, Index> operator+(const __Base_matrix_t_<Dims, Elem, Index>& mat)
		{
			return /*__Base_matrix_t_*/make_matrix_t(ptr->add(mat.ptr));
		}
		
		matrix_t<Dims, Elem, Index> operator-(const __Base_matrix_t_<Dims, Elem, Index>& mat)
		{
			return /*__Base_matrix_t_*/make_matrix_t(ptr->sub(mat.ptr));
		}
		
		matrix_t<Dims, Elem, Index> operator*(const __Base_matrix_t_<Dims, Elem, Index>& mat)
		{
			return /*__Base_matrix_t_*/make_matrix_t(ptr->mul(mat.ptr));
		}
		
		matrix_t<Dims, Elem, Index> operator*(const double n)
		{
			return /*__Base_matrix_t_*/make_matrix_t(ptr->mul(n));
		}
		
		Index* size() const
		{
			return ptr->size;
		}
		
		Elem det() const
		{
			return ptr->det();
		}
		
		
	};
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	class matrix_t : public __Base_matrix_t_<Dims, Elem, Index>
	{
		
		//typedef typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type Func;
		
		
		public:
		matrix_t(typename matrix_t::ptr_t * ptr) : __Base_matrix_t_<Dims, Elem, Index>(ptr) { }
		
		
		matrix_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f
		) : __Base_matrix_t_<Dims, Elem, Index>(new FuncMatrix<Dims, Elem, Index>(f)) {}
		
		
		matrix_t(const matrix_t& m) : __Base_matrix_t_<Dims, Elem, Index>(m) { }
		virtual ~matrix_t() { }
		
		
		
		matrix_t<Dims-1, Elem, Index> operator[](Index i)
		{
			return matrix_t<Dims-1, Elem, Index>((*this->ptr)[i]);
		}
		
		
		matrix_t<Dims, Elem, Index> T() const
		{
			return matrix_t(this->ptr->T());
		}
		
		template <typename ...Args>
		matrix_t<Dims, Elem, Index> submatrix(Args... args) const
		{
			return matrix_t(this->ptr->submatrix(std::make_tuple(args...)));
		}
		
		template <int Dims2>
		matrix_t<Dims+Dims2-2, Elem, Index> contract(matrix_t<Dims2, Elem, Index> m)
		{
			return matrix_t<Dims+Dims2-2, Elem, Index>(this->ptr->contract(m.ptr));
		}
		
		Elem set(Elem value, auto ...index)
		{
			return this->ptr->set(value, index...);
		}
		
		template <int Dims2>
		void append(matrix_t<Dims2, Elem, Index> m)
		{
			this->ptr->append(m.ptr);
		}
		
		template <int D2, typename E2, typename I2> 
		friend class matrix_t;
		
	};
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class matrix_t<1, Elem, Index> : public __Base_matrix_t_<1, Elem, Index>
	{
		
		
		public:
		
		matrix_t(typename matrix_t::ptr_t * ptr) : __Base_matrix_t_<1, Elem, Index>(ptr) { }
		
		matrix_t(
		typename _Helpers::FuncArgHelper<1, Index, Elem>::type f
		) : __Base_matrix_t_<1, Elem, Index>(new FuncMatrix<1, Elem, Index>(f)) {}
		
		matrix_t(const matrix_t& m) : __Base_matrix_t_<1, Elem, Index>(m) { }
		
		virtual ~matrix_t() { }
		
		Elem operator[](Index i)
		{
			return (*this->ptr)[i];
		}
		
		Elem set(Elem value, Index index)
		{
			return this->ptr->set(value, index);
		}
		
		void append(Elem value)
		{
			this->ptr->append(value);
		}
		
		template <int D2, typename E2, typename I2> 
		friend class matrix_t;
		
	};
	
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(Matrix<Dims, Elem, Index>* ptr)
	{
		return matrix_t<Dims, Elem, Index>(ptr);
	}
	
}
}