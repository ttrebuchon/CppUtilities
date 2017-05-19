#pragma once

#include <type_traits>

namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index>
	__Base_matrix_t_<Dims, Elem, Index>& __Base_matrix_t_<Dims, Elem, Index>::operator=(ptr_t _ptr)
	{
		this->ptr = _ptr;
		return *this;
	}
	
	template <int Dims, typename Elem, typename Index>
	__Base_matrix_t_<Dims, Elem, Index>& __Base_matrix_t_<Dims, Elem, Index>::operator=(const __Base_matrix_t_& m)
	{
		if (m.ptr != NULL)
		{
			ptr = ptr_t(m.ptr->clone());
		}
		else
		{
			ptr = NULL;
		}
		return *this;
	}

	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> __Base_matrix_t_<Dims, Elem, Index>::operator+(const __Base_matrix_t_<Dims, Elem, Index>& mat)
	{
		return make_matrix_t(ptr->add(mat.ptr));
	}

	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> __Base_matrix_t_<Dims, Elem, Index>::operator-(const __Base_matrix_t_<Dims, Elem, Index>& mat)
	{
		return make_matrix_t(ptr->sub(mat.ptr));
	}
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> __Base_matrix_t_<Dims, Elem, Index>::operator*(const __Base_matrix_t_<Dims, Elem, Index>& mat)
	{
		return make_matrix_t(ptr->mul(mat.ptr));
	}
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> __Base_matrix_t_<Dims, Elem, Index>::operator*(const double n)
	{
		return make_matrix_t(ptr->mul(n));
	}
	
	
	
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index>& matrix_t<Dims, Elem, Index>::operator=(Matrix<Dims, Elem, Index>* ptr)
	{
		assert(ptr != NULL);
		try
		{
			this->ptr = ptr->get_ptr();
		}
		catch (std::bad_weak_ptr)
		{
			this->ptr = std::shared_ptr<Matrix<Dims, Elem, Index>>(ptr);
		}
		return *this;
	}
	
	
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims-1, Elem, Index> matrix_t<Dims, Elem, Index>::operator[](Index i)
	{
		return matrix_t<Dims-1, Elem, Index>((*this->ptr)[i]);
	}
	
	template <int Dims, typename Elem, typename Index>
	template <typename ...Args>
	typename _Helpers::t_RefReturnHelper<matrix_t, Dims, Elem, Index, sizeof...(Args)+1>::type matrix_t<Dims, Elem, Index>::operator()(Index arg1, Args... args)
	{
		static_assert(std::is_same<decltype(this->ptr->operator()(arg1, args...)), typename _Helpers::t_RefReturnHelper<Matrix, Dims, Elem, Index, sizeof...(Args)+1>::type&>::value, "Matrix_t.hpp: operator() inconsistency");
		static_assert(std::is_same<decltype(make_matrix_t(this->ptr->operator()(arg1, args...))), typename _Helpers::t_RefReturnHelper<matrix_t, Dims, Elem, Index, sizeof...(Args)+1>::type>::value, "Matrix_t.hpp: operator() inconsistency");
		return make_matrix_t(this->ptr->operator()(arg1, args...));
	}
	
	template <int Dims, typename Elem, typename Index>
	matrix_t<Dims, Elem, Index> matrix_t<Dims, Elem, Index>::T() const
	{
		return matrix_t(this->ptr->T());
	}

	template <int Dims, typename Elem, typename Index>
	template <typename ...Args>
	matrix_t<Dims, Elem, Index> matrix_t<Dims, Elem, Index>::submatrix(Args... args) const
	{
		return matrix_t(this->ptr->submatrix(std::make_tuple(args...)));
	}

	template <int Dims, typename Elem, typename Index>
	template <int Dims2>
	matrix_t<Dims+Dims2-2, Elem, Index> matrix_t<Dims, Elem, Index>::contract(matrix_t<Dims2, Elem, Index> m)
	{
		return matrix_t<Dims+Dims2-2, Elem, Index>(this->ptr->contract(m.ptr));
	}

	template <int Dims, typename Elem, typename Index>
	Elem matrix_t<Dims, Elem, Index>::set(Elem value, auto ...index)
	{
		return this->ptr->set(value, index...);
	}
	
	template <int Dims, typename Elem, typename Index>	
	template <int Dims2>
	void matrix_t<Dims, Elem, Index>::append(matrix_t<Dims2, Elem, Index> m)
	{
		this->ptr->append(m.ptr);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	matrix_t<1, Elem, Index>& matrix_t<1, Elem, Index>::operator=(Matrix<1, Elem, Index>* ptr)
	{
		assert(ptr != NULL);
		try
		{
			this->ptr = ptr->get_ptr();
		}
		catch (std::bad_weak_ptr)
		{
			this->ptr = std::shared_ptr<Matrix<1, Elem, Index>>(ptr);
		}
		return *this;
	}
	
	template <typename Elem, typename Index>
	Elem matrix_t<1, Elem, Index>::operator[](Index i)
	{
		return (*this->ptr)[i];
	}
	
	template <typename Elem, typename Index>
	typename _Helpers::t_RefReturnHelper<matrix_t, 1, Elem, Index, 1>::type matrix_t<1, Elem, Index>::operator()(Index i)
	{
		static_assert(std::is_same<decltype((*this->ptr)(i)), typename _Helpers::t_RefReturnHelper<matrix_t, 1, Elem, Index, 1>::type>::value, "Type error!");
		return (*this->ptr)(i);
	}
	
	template <typename Elem, typename Index>
	Elem matrix_t<1, Elem, Index>::set(Elem value, Index index)
	{
		return this->ptr->set(value, index);
	}
	
	template <typename Elem, typename Index>
	void matrix_t<1, Elem, Index>::append(Elem value)
	{
		this->ptr->append(value);
	}
	
}
}