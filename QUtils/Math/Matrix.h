#pragma once

#include <QUtils/Exception/Exception.h>
#include <memory>
#include <assert.h>
#include <cstring>
#include <iostream>



namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index>
	class tensor_t;




	namespace _Helpers
	{
		template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index, int argCount>
		struct RefReturnHelper
		{
			typedef typename RefReturnHelper<Obj, Dims-1, Elem, Index, argCount-1>::type type;
		};
		
		template <template <int, typename...> typename Obj, int Dims, typename Elem, typename Index>
		struct RefReturnHelper<Obj, Dims, Elem, Index, 0>
		{
			typedef Obj<Dims, Elem, Index> type;
		};
		
		template <template <int, typename...> typename Obj, typename Elem, typename Index>
		struct RefReturnHelper<Obj, 0, Elem, Index, 0>
		{
			typedef Elem type;
		};
	}
	UTIL_CUSTOM_EXCEPTION(MatrixInvalidSizeException, );
	
	
	
	template <int Dims, typename Elem, typename Index>
	class Matrix;
	
	template <int Dims, typename Elem, typename Index>
	class _MatrixBase_
	{
		private:
		
		protected:
		
		typedef tensor_t<Dims, Elem, Index> tens_t;
		
		
		public:
		Index size[Dims];
		
		_MatrixBase_() : size()
		{
			for (auto i = 0; i < Dims; i++)
			{
				size[i] = -1;
			}
		}

		_MatrixBase_(const _MatrixBase_& m) : size()
		{
			std::memcpy(this->size, m.size, sizeof(decltype(size[0]))*Dims);
		}

		virtual ~_MatrixBase_() {  }
		
		virtual std::string imp() const = 0;
		
		
		template <typename Num>
		tens_t operator*(const Num n)
		{
			return mul(n);
		}
		
		virtual tens_t operator+(const tensor_t<Dims, Elem, Index> mat)
		{
			return add(mat);
		}
		
		virtual tens_t operator-(const tensor_t<Dims, Elem, Index> mat)
		{
			return sub(mat);
		}
		
		virtual void resize(const Index s) = 0;
		
		virtual void setSize(const Index dim, const Index s) = 0;
		
		
		
		virtual std::string toString() const = 0;
		
		virtual tens_t mul(const Elem) = 0;
		virtual tens_t div(const Elem) = 0;
		
		virtual tens_t mul(const tensor_t<Dims, Elem, Index>) = 0;
		
		virtual tens_t div(const tensor_t<Dims, Elem, Index>) = 0;
		
		
		
		
		/*virtual tens_t mul(const tens_t m)
		{
			return mul(*m);
		}*/
		
		virtual tens_t add(const tensor_t<Dims, Elem, Index>) = 0;
		
		/*virtual tens_t add(const tens_t m)
		{
			return add(*m);
		}*/
		
		virtual tens_t sub(const tensor_t<Dims, Elem, Index>) = 0;
		
		/*virtual tens_t sub(const tens_t m)
		{
			return sub(*m);
		}*/
		
		virtual Elem det() const = 0;
		
		virtual tens_t clone() const = 0;
		
		virtual Index Size(const int dim) const = 0;
		
		virtual tensor_t<2, Elem, Index> inv() const = 0;
		
		virtual tensor_t<Dims, Elem, Index> toDataTensor() const = 0;
		
		template <int newDims>
		tensor_t<newDims, Elem, Index> expand() const;
		
		
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
	class Matrix : public _MatrixBase_<Dims, Elem, Index>, 
	public std::enable_shared_from_this<Matrix<Dims, Elem, Index>>
	{
		private:
		
		protected:
		
		public:
		Matrix() : _MatrixBase_<Dims, Elem, Index>(), std::enable_shared_from_this<Matrix<Dims, Elem, Index>>() { }
		virtual ~Matrix() { }
		
		std::shared_ptr<Matrix<Dims, Elem, Index>> get_ptr()
		{
			try
			{
				return this->shared_from_this();
			}
			catch (std::bad_weak_ptr)
			{
				return std::shared_ptr<Matrix<Dims, Elem, Index>>(this);
			}
		}
		
		std::shared_ptr<const Matrix<Dims, Elem, Index>> get_ptr() const
		{
			return ((Matrix<Dims, Elem, Index>*)this)->get_ptr();
			/*try
			{
				return this->shared_from_this();
			}
			catch (std::bad_weak_ptr)
			{
				return std::shared_ptr<const Matrix<Dims, Elem, Index>>(this);
			}*/
			
		}
		
		virtual std::string toString() const override;
		
		virtual tensor_t<Dims-1, Elem, Index> operator[](Index i) const = 0;
		
		template <typename ...Args>
		typename _Helpers::RefReturnHelper<Matrix, Dims, Elem, Index, sizeof...(Args)+1>::type& operator()(Index i, Args... args)
		{
			static_assert(sizeof...(Args) > 0, "Error with Args in RefReturnHelper usage");
			return this->operator()(i).operator()(args...);
		}
		
		template <typename ...Args>
		const typename _Helpers::RefReturnHelper<Matrix, Dims, Elem, Index, sizeof...(Args)+1>::type& operator()(Index i, Args... args) const 
		{
			static_assert(sizeof...(Args) > 0, "Error with Args in RefReturnHelper usage");
			return this->operator()(i).operator()(args...);
		}
		
		virtual tensor_t<Dims-1, Elem, Index>& operator()(Index i) = 0;
		
		virtual const tensor_t<Dims-1, Elem, Index>& operator()(Index i) const = 0;
		
		virtual tensor_t<Dims-1, Elem, Index> at(Index i) const
		{
			return (*this)[i];
		}
		
		virtual tensor_t<Dims, Elem, Index> T() const = 0;
		virtual tensor_t<Dims, Elem, Index> submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const = 0;
		
		template <int Dims2>
		tensor_t<Dims+Dims2-2, Elem, Index> contract(tensor_t<Dims2, Elem, Index>);
		#undef minor
		virtual Elem minor(typename _Helpers::TupleBuilder<Dims, Index>::value) const;
		
		virtual Elem det() const override;
		
		template <int Dims2>
		void append(tensor_t<Dims2, Elem, Index>);
		
		void set(const Index i, const tensor_t<Dims-1, Elem, Index> ptr);
		
		virtual Index Size(const int dim) const override
		{
			if (dim == 0)
			{
				return this->size[0];
			}
			if (this->size[0] == 0)
			{
				return 0;
			}
			return this->operator[](0).size(dim-1);
		}
		
		virtual tensor_t<2, Elem, Index> inv() const = 0;
		
		template <typename... Args>
		tensor_t<Dims, Elem, Index> block(Args... args) const
		{
			static_assert(sizeof...(Args) == 2*Dims, "Incorrect number of arguments to block()");
			return this->block(std::make_tuple(args...));
		}
		
		
		virtual tensor_t<Dims, Elem, Index> block(typename _Helpers::TupleBuilder<2*Dims, Index>::value) const = 0;
		
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class Matrix<1, Elem, Index> : public _MatrixBase_<1, Elem, Index>, public std::enable_shared_from_this<Matrix<1, Elem, Index>>
	{
		private:
		
		protected:
		
		public:
		Matrix() : _MatrixBase_<1, Elem, Index>(), std::enable_shared_from_this<Matrix<1, Elem, Index>>() { }
		virtual ~Matrix() { }
		
		std::shared_ptr<Matrix<1, Elem, Index>> get_ptr()
		{
			try
			{
				return this->shared_from_this();
			}
			catch (std::bad_weak_ptr)
			{
				return std::shared_ptr<Matrix<1, Elem, Index>>(this);
			}
		}
		
		std::shared_ptr<const Matrix<1, Elem, Index>> get_ptr() const
		{
			return ((Matrix<1, Elem, Index>*)this)->get_ptr();
			/*try
			{
				return this->shared_from_this();
			}
			catch (std::bad_weak_ptr)
			{
				return std::shared_ptr<const Matrix<Dims, Elem, Index>>(this);
			}*/
			
		}
		
		/*virtual void setSize(const Index s) { _MatrixBase_<1, Elem, Index>::setSize((const Index)0, s); }*/
		
		virtual std::string toString() const override;
		
		virtual Elem operator[](Index i) const = 0;
		virtual Elem& operator()(Index i) = 0;
		virtual const Elem& operator()(Index i) const = 0;
		
		virtual Elem at(Index i) const
		{
			return (*this)[i];
		}
		
		virtual tensor_t<2, Elem, Index> T() const = 0;
		virtual tensor_t<1, Elem, Index> submatrix(std::tuple<Index>) const = 0;
		
		template <int Dims2>
		tensor_t<Dims2-1, Elem, Index> contract(tensor_t<Dims2, Elem, Index>);
		
		virtual Elem det() const override;
		
		virtual void append(Elem value) = 0;
		
		virtual Index Size(const int dim) const override
		{
			if (dim > 0)
			{
				throw MatrixInvalidSizeException();
			}
			
			return this->size[0];
		}
		
		virtual tensor_t<2, Elem, Index> inv() const = 0;
		
		template <typename... Args>
		tensor_t<1, Elem, Index> block(Args... args) const
		{
			static_assert(sizeof...(Args) == 2, "Incorrect number of arguments to block()");
			return this->block(std::make_tuple(args...));
		}
		
		
		virtual tensor_t<1, Elem, Index> block(typename _Helpers::TupleBuilder<2, Index>::value) const = 0;
		
	};
	
	template <int Dims1, int Dims2, typename Elem, typename Index, template <int, typename, typename> typename T, template <int, typename, typename> typename H>
	tensor_t<Dims1+Dims2-2, Elem, Index> MatrixContract(std::shared_ptr<T<Dims1, Elem, Index>>, std::shared_ptr<H<Dims2, Elem, Index>>);
}
}

#include "FuncMatrix.h"
#include "DataMatrix.h"
#include "DataMatrix.hpp"

#include "tensor_t.h"
#include "Matrix.hpp"