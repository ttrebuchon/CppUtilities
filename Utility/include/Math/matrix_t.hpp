#pragma once


namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index>
	__Base_matrix_t_<Dims, Elem, Index>& __Base_matrix_t_<Dims, Elem, Index>::operator=(ptr_t* _ptr)
	{
		if (this->ptr != NULL)
		{
			delete this->ptr;
		}
		this->ptr = _ptr;
		return *this;
	}
	
	template <int Dims, typename Elem, typename Index>
	__Base_matrix_t_<Dims, Elem, Index>& __Base_matrix_t_<Dims, Elem, Index>::operator=(const __Base_matrix_t_& m)
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
	
	
	
}
}