#pragma once
#include "tensor_t.h"
#include "Matrix.h"
#include "FuncMatrix.h"

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

	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>::tensor_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f)
		: tensor_t<Dims, Elem, Index>::Shared(std::make_shared<FuncMatrix<Dims, Elem, Index>>(f))
	{

	}

	template <int Dims, typename Elem, typename Index>
	template <typename... Size>
	tensor_t<Dims, Elem, Index>::tensor_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f, Size... sizes)
		: tensor_t<Dims, Elem, Index>::Shared(std::make_shared<FuncMatrix<Dims, Elem, Index>>(
			f, sizes...
		))
	{
		
	}
	
	
	
	
	
	
	//Assignment Operators
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator=(const Elem e)
	{
		auto tmp = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto...) { return e; });
		for (auto i = 0; i < Dims; i++)
		{
			if (*this == NULL)
			{
				tmp->setSize(i, -1);
			}
			else
			{
				tmp->setSize(i, this->size(i));
			}
		}
		(typename tensor_t<Dims, Elem, Index>::Shared&)*this = tmp;
		return *this;
		/*for (Index i = 0; i < this->size(0); i++)
		{
			ptr()(i) = e;
		}
		return ptr();*/
	}

	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>& tensor_t<Dims, Elem, Index>::operator=(
		const typename tensor_t<Dims, Elem, Index>::Shared ptr
	)
	{
		(Shared&)(*this) = ptr;
		return (*this);
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






	template <int Dims, typename Elem, typename Index>
	template <typename Elem2>
	bool tensor_t<Dims, Elem, Index>::operator==(const tensor_t<Dims, Elem2, Index> t) const
	{
		if (this->size(0) != t.size(0))
		{
			return false;
		}
		
		bool same = true;
		for (auto i = 0; i < this->size(0) && same; i++)
		{
			same = (obj()[(Index)i] == t[(Index)i]);
		}
		return same;
	}
	
	
	
	
	
	
	//Member Functions
	template <int Dims, typename Elem, typename Index>
	Index tensor_t<Dims, Elem, Index>::size(const int dim) const
	{
		return ptr()->size[dim];
	}

	template <int Dims, typename Elem, typename Index>
	void tensor_t<Dims, Elem, Index>::setSize(const int dim, const Index size)
	{
		ptr()->setSize(dim, size);
	}
	
	template <int Dims, typename Elem, typename Index>
	std::string tensor_t<Dims, Elem, Index>::toString() const
	{
		return ptr()->toString();
	}

	template <int Dims, typename Elem, typename Index>
	std::string tensor_t<Dims, Elem, Index>::imp() const
	{
		return ptr()->imp();
	}

	template <int Dims, typename Elem, typename Index>
	template <int Dims2>
	tensor_t<Dims+Dims2-2, Elem, Index> tensor_t<Dims, Elem, Index>::contract(
					const tensor_t<Dims2, Elem, Index> t
	)
	{
		return ptr()->contract(t);
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