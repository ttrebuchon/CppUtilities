#pragma once
#include "tensor_t.h"
#include "Matrix.h"
#include "FuncMatrix.h"

#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Exception/NullPointer.h>


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
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	struct CheckSizes {
	static bool checkSizes(std::initializer_list<tensor_t<Dims-1, Elem, Index>> list)
	{
		auto s = (*list.begin()).size(0);
		for (auto item : list)
		{
			s = item.size(0);
			if (s != -1)
			{
				break;
			}
		}
		if (s == -1)
		{
			return true;
		}
		for (auto item : list)
		{
			if (item.size(0) != s)
			{
				if (item.size(0) == -1)
				{
					item.setSize(0, s);
				}
				else
				{
					return false;
				}
			}
		}
		return true;
	}
	};
	
	template <typename Elem, typename Index>
	struct CheckSizes<1, Elem, Index> {
	static bool checkSizes(std::initializer_list<Elem> list)
	{
		return true;
	}
	};
	
	//Constructors and Destructors
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index>::tensor_t(std::initializer_list<typename tensor_t<Dims, Elem, Index>::type> list) : tensor_t<Dims, Elem, Index>::Shared(std::make_shared<DataMatrix<Dims, Elem, Index>>())
	{
		setSize(0, list.size());
		if (!CheckSizes<Dims, Elem, Index>::checkSizes(list))
		{
			throw MatrixInvalidSizeException();
		}
		
		Index i = 0;
		for (auto item : list)
		{
			obj()(i++) = item;
		}
	}
	
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
			else if (this->size(i) != 0)
			{
				tmp->setSize(i, this->size(i));
			}
			else
			{
				tmp->setSize(i, 1);
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
		return ptr()->Size(dim);
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
	Elem tensor_t<Dims, Elem, Index>::det() const
	{
		return ptr()->det();
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<2, Elem, Index> tensor_t<Dims, Elem, Index>::inv() const
	{
		static_assert(Dims == 2 || Dims == 1, "Can only find inverses of matrices and vectors");
		return ptr()->inv();
	}

	template <int Dims, typename Elem, typename Index>
	template <int Dims2>
	tensor_t<Dims+Dims2-2, Elem, Index> tensor_t<Dims, Elem, Index>::contract(
					const tensor_t<Dims2, Elem, Index> t
	)
	{
		return ptr()->contract(t);
	}
	
	template <int Dims, typename Elem, typename Index>
	template <typename... Args>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::submatrix(Args... args) const
	{
		return submatrix(std::make_tuple(args...));
	}
	
	template <int Dims, typename Elem, typename Index>
	template <typename... Args>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::submatrix(std::tuple<Args...> args) const
	{
		static_assert(sizeof...(Args) == Dims, "Incorrect number of arguments to submatrix()");
		
		return ptr()->submatrix(args);
	}
	
	template <int Dims, typename Elem, typename Index> tensor_t<_Helpers::_tensor_t::transposeDims(Dims), Elem, Index> tensor_t<Dims, Elem, Index>::T() const
	{
		return ptr()->T();
	}
	
	template <int Dims, typename Elem, typename Index>
	template <typename... Args>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::block(Args... args) const
	{
		return ptr()->block(args...);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> tensor_t<Dims, Elem, Index>::toDataTensor() const
	{
		return ptr()->toDataTensor();
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