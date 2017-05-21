#pragma once

#include "Matrix.h"
#include "FuncArgHelper.h"
#include <memory>
#include <type_traits>
#include <assert.h>
#include <iostream>

namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index = int>
	class matrix_t;
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(Matrix<Dims, Elem, Index>*);
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(Matrix<Dims, Elem, Index>&);
	
	template <typename Elem>
	Elem& make_matrix_t(Elem&);
	
	namespace _Helpers
	{
		template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index, int argCount>
		struct t_RefReturnHelper
		{
			typedef typename t_RefReturnHelper<Obj, Dims-1, Elem, Index, argCount-1>::type type;
		};
		
		template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index>
		struct t_RefReturnHelper<Obj, Dims, Elem, Index, 0>
		{
			typedef Obj<Dims, Elem, Index> type;
		};
		
		template <template <int, typename...> typename Obj, typename Elem, typename Index>
		struct t_RefReturnHelper<Obj, 0, Elem, Index, 0>
		{
			typedef Elem& type;
		};
	}
	
	
	template <int Dims, typename Elem, typename Index>
	class __Base_matrix_t_
	{
		private:
		
		protected:
		
		typedef Matrix<Dims, Elem, Index> mat_t;
		typedef std::shared_ptr<mat_t> ptr_t;
		
		ptr_t ptr = NULL;
		
		public:
		__Base_matrix_t_(ptr_t ptr) : ptr(ptr) { }
		__Base_matrix_t_(const __Base_matrix_t_& m) : ptr(m.ptr->clone()) { }
		virtual ~__Base_matrix_t_() { }
		
		
		__Base_matrix_t_& operator=(ptr_t _ptr);
		__Base_matrix_t_& operator=(const __Base_matrix_t_& m);
		
		std::string toString() const { return ptr->toString(); }
		
		
		matrix_t<Dims, Elem, Index> operator+(const __Base_matrix_t_<Dims, Elem, Index>& mat);
		matrix_t<Dims, Elem, Index> operator-(const __Base_matrix_t_<Dims, Elem, Index>& mat);
		matrix_t<Dims, Elem, Index> operator*(const __Base_matrix_t_<Dims, Elem, Index>& mat);
		matrix_t<Dims, Elem, Index> operator*(const double n);
		
		Index* size() const { return ptr->size; }
		Elem det() const { return ptr->det(); }
		
		
	};
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	class matrix_t : public __Base_matrix_t_<Dims, Elem, Index>
	{
		
		//typedef typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type Func;
		
		using __Base_matrix_t_<Dims, Elem, Index>::mat_t;
		using __Base_matrix_t_<Dims, Elem, Index>::ptr_t;
		
		
		public:
		matrix_t() : __Base_matrix_t_<Dims, Elem, Index>(nullptr) {}
		
		matrix_t(typename matrix_t::ptr_t ptr) : __Base_matrix_t_<Dims, Elem, Index>(ptr) { }
		
		matrix_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f
		) : __Base_matrix_t_<Dims, Elem, Index>(std::make_shared<FuncMatrix<Dims, Elem, Index>>(f)) {}
		
		matrix_t(const matrix_t& m) : __Base_matrix_t_<Dims, Elem, Index>(m) { }
		
		matrix_t(Matrix<Dims, Elem, Index>* ptr) : matrix_t()
		{
			this->operator=(ptr);
		}
		virtual ~matrix_t() { }
		
		
		
		
		//using __Base_matrix_t_<Dims, Elem, Index>::operator=;
		
		matrix_t<Dims, Elem, Index>& operator=(Matrix<Dims, Elem, Index>*);
		
		matrix_t<Dims, Elem, Index>& operator=(std::shared_ptr<Matrix<Dims, Elem, Index>> ptr)
		{
			this->ptr = ptr;
			return *this;
		}
		
		
		matrix_t<Dims-1, Elem, Index> operator[](Index i) const;
		template <typename ...Args>
		typename _Helpers::t_RefReturnHelper<matrix_t, Dims, Elem, Index, sizeof...(Args)+1>::type  operator()(Index arg1, Args... args);
		matrix_t<Dims, Elem, Index> T() const;
		
		template <typename ...Args>
		matrix_t<Dims, Elem, Index> submatrix(Args... args) const;
		
		template <int Dims2>
		matrix_t<Dims+Dims2-2, Elem, Index> contract(matrix_t<Dims2, Elem, Index> m);
		
		Elem set(Elem value, auto ...index);
		
		template <int Dims2>
		void append(matrix_t<Dims2, Elem, Index> m);
		matrix_t& setSize(const Index dim, const Index size);
		
		template <int D2, typename E2, typename I2> 
		friend class matrix_t;
		
	};
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class matrix_t<1, Elem, Index> : public __Base_matrix_t_<1, Elem, Index>
	{
		
		
		public:
		matrix_t() : __Base_matrix_t_<1, Elem, Index>(nullptr) {}
		
		matrix_t(typename matrix_t::ptr_t ptr) : __Base_matrix_t_<1, Elem, Index>(ptr) { }
		
		matrix_t(
		typename _Helpers::FuncArgHelper<1, Index, Elem>::type f
		) : __Base_matrix_t_<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>(f)) {}
		
		matrix_t(const matrix_t& m) : __Base_matrix_t_<1, Elem, Index>(m) { }
		
		virtual ~matrix_t() { }
		
		
		
		matrix_t<1, Elem, Index>& operator=(Matrix<1, Elem, Index>*);
		
		Elem operator[](Index i) const;
		typename _Helpers::t_RefReturnHelper<matrix_t, 1, Elem, Index, 1>::type operator()(Index i);
		
		static_assert(std::is_same<typename _Helpers::RefReturnHelper<matrix_t, 1, Elem, Index, 1>::type &, Elem&>::value, "Something wrong with RefReturnHelper!");
		
		Elem set(Elem value, Index index);
		
		void append(Elem value);
		matrix_t& setSize(const Index dim, const Index size);
		matrix_t& setSize(const Index s) { return setSize(0, s); }
		
		template <int D2, typename E2, typename I2> 
		friend class matrix_t;
		
	};
	
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(std::shared_ptr<Matrix<Dims, Elem, Index>> ptr)
	{
		return matrix_t<Dims, Elem, Index>(ptr);
	}
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> make_matrix_t(Matrix<Dims, Elem, Index>& refer)
	{
		return matrix_t<Dims, Elem, Index>(refer.get_ptr());
	}
	
	template <typename Elem>
	Elem& make_matrix_t(Elem& e)
	{
		return e;
	}
	
}
}

#include "matrix_t.hpp"