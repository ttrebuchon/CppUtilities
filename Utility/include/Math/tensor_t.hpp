#pragma once
#include "tensor_t.h"
#include "Matrix.h"

#include <Exception/NotImplemented.h>
#include <Exception/NullPointer.h>


namespace Util
{
namespace Math
{
	//Internal Functions
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::ptr()
	{
		if (*this == NULL)
		{
			throw NullPtrEx();
		}
		return *this;
	}
	
	template <int Dims, typename Elem, typename Index>
	const tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::ptr() const
	{
		if (*this == NULL)
		{
			throw NullPtrEx();
		}
		return *this;
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::obj()
	{
		if (*this == NULL)
		{
			throw NullPtrEx();
		}
		return *(this->get());
	}
	
	template <int Dims, typename Elem, typename Index>
	const Matrix<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::obj() const
	{
		if (*this == NULL)
		{
			throw NullPtrEx();
		}
		return *(this->get());
	}
	
	
	
	
	
	
	//Constructors and Destructors
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>::~tensor_t()
	{
		
	}
	
	
	
	
	
	
	//Assignment Operators
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator=(const Elem e)
	{
		for (Index i = 0; i < this->size(0); i++)
		{
			ptr()(i) = e;
		}
		return ptr();
	}
	
	
	
	
	
	
	//Arithmetic Operators
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator+(const tensor_t t) const
	{
		return ptr()->add(t);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator-(const tensor_t t) const
	{
		return ptr()->sub(t);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator*(const tensor_t t) const
	{
		return ptr()->mul(t);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator/(const tensor_t t) const
	{
		return ptr()->div(t);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator*(const Elem e) const
	{
		return ptr()->mul(e);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::operator/(const Elem e) const
	{
		return ptr()->div(e);
	}
	
	
	
	
	
	
	//Arithmetic Assignment Operators
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator+=(const tensor_t t)
	{
		ptr() = ptr() + t;
		return ptr();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator-=(const tensor_t t)
	{
		ptr() = ptr() - t;
		return ptr();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator*=(const tensor_t t)
	{
		ptr() = ptr() * t;
		return ptr();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator/=(const tensor_t t)
	{
		ptr() = ptr() / t;
		return ptr();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator*=(const Elem e)
	{
		ptr() = ptr() * e;
		return ptr();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator/=(const Elem e)
	{
		ptr() = ptr() / e;
		return ptr();
	}
	
	
	
	
	
	
	//Member Functions
	template <int Dims, typename Elem, typename Index>
	Index tensor_t<Dims, Elem, Index>::size(const int dim) const
	{
		return ptr()->size[dim];
	}
	
	template <int Dims, typename Elem, typename Index>
	std::string tensor_t<Dims, Elem, Index>::toString() const
	{
		return ptr()->toString();
	}
	
	
	
	
	
	
	//Accessors
	template <int Dims, typename Elem, typename Index>
	typename tensor_t<Dims, Elem, Index>::type&
	tensor_t<Dims, Elem, Index>::operator()(const Index i)
	{
		return obj()(i);
	}
	
	template <int Dims, typename Elem, typename Index>
	template <class... Args>
	typename tensor_t<Dims, Elem, Index>::template RetType<sizeof...(Args)>& tensor_t<Dims, Elem, Index>::operator()(const Args... args)
	{
		return obj()(args...);
	}
	
	template <int Dims, typename Elem, typename Index>
	const typename tensor_t<Dims, Elem, Index>::type&
	tensor_t<Dims, Elem, Index>::operator()(const Index i) const
	{
		return obj()(i);
	}
	
	template <int Dims, typename Elem, typename Index>
	template <class... Args>
	const typename tensor_t<Dims, Elem, Index>::template RetType<sizeof...(Args)>& tensor_t<Dims, Elem, Index>::operator()(const Args... args) const
	{
		return obj()(args...);
	}
	
	template <int Dims, typename Elem, typename Index>
	typename tensor_t<Dims, Elem, Index>::type
	tensor_t<Dims, Elem, Index>::operator[](const Index i) const
	{
		return obj()[i];
	}
}
}