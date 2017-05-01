#pragma once

#include "FuncMatrix.h"
#include <tuple>
#include <Func/TupleArgs.h>

namespace Util
{
namespace Math
{
	template <typename ...Args>
	auto reverseTuple(Args... args);
	
	template <typename Arg>
	auto reverseTuple(Arg arg)
	{
		return std::make_tuple(arg);
	}
	
	
	template <typename A, typename ...Args>
	auto reverseTuple(A a, Args... args)
	{
		return std::tuple_cat(reverseTuple(args...), std::make_tuple(a));
	}
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	FuncMatrix<Dims, Elem, Index>::FuncMatrix(Func f) : Matrix<Dims, Elem, Index>(), def(f)
	{
		
	};
	
	
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims-1, Elem, Index>* FuncMatrix<Dims, Elem, Index>::operator[](Index i)
	{
		return new FuncMatrix<Dims-1, Elem, Index>(([=](auto ...args) -> Elem { return def(i, args...); }));
	}
	
	template <int Dims, typename Elem, typename Index>
	std::string FuncMatrix<Dims, Elem, Index>::toString() const
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::mul(const double)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::add(const Matrix<Dims, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::sub(const Matrix<Dims, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::clone() const
	{
		return new FuncMatrix(*this);
	}
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::T() const
	{
		auto n = new FuncMatrix(
		[=] (auto... args)
		{
			auto revArgs = reverseTuple(args...);
			return call_tuple_args(def, revArgs);
		});
		for (int i = 0; i < Dims; i++)
		{
			n->size[i] = this->size[Dims-1-i];
		}
		return n;
	}
	
	
	
	
	
	
	
	
	
	template <int N, int ...Nums>
	class _ProcHelper
	{
		public:
		template <typename ...Args>
		static std::tuple<Args...> Proc(std::tuple<Args...> deleted, std::tuple<Args...> arguments)
		{
			return _ProcHelper<N-1, N-1, Nums...>::Proc(deleted, arguments);
		}
	};
	
	template <int ...Nums>
	class _ProcHelper<0, Nums...>
	{
		public:
		template <typename ...Args>
		static std::tuple<Args...> Proc(std::tuple<Args...> deleted, std::tuple<Args...> arguments)
		{
			auto offset = [](auto removed, auto arg)
			{
				if (arg < removed)
				{
					return arg;
				}
				return arg + 1;
			};
			return std::make_tuple(offset(std::get<Nums>(deleted), std::get<Nums>(arguments))...);
		}
	};
	
	
	
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	Matrix<Dims, Elem, Index>* FuncMatrix<Dims, Elem, Index>::submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value t) const
	{
		auto ret = new FuncMatrix<Dims, Elem, Index>(
		[=] (auto... args)
		{
			return call_tuple_args(def, _ProcHelper<Dims>::Proc(t, std::make_tuple(args...)));
		});
		for (auto i = 0; i < Dims; i++)
		{
			ret->size[i] = this->size[i] - 1;
		}
		return ret;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	FuncMatrix<1, Elem, Index>::FuncMatrix(std::function<Elem(Index)> f) : Matrix<1, Elem, Index>(), def(f)
	{
		
	}
	
	template <typename Elem, typename Index>
	Elem FuncMatrix<1, Elem, Index>::operator[](Index i)
	{
		return def(i);
	}
	
	
	template <typename Elem, typename Index>
	std::string FuncMatrix<1, Elem, Index>::toString() const
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::mul(const double)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::add(const Matrix<1, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::sub(const Matrix<1, Elem, Index>&)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::clone() const
	{
		return new FuncMatrix(*this);
	}
	
	template <typename Elem, typename Index>
	Matrix<2, Elem, Index>* FuncMatrix<1, Elem, Index>::T() const
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	Matrix<1, Elem, Index>* FuncMatrix<1, Elem, Index>::submatrix(std::tuple<Index> t) const
	{
		throw NotImp();
	}
	
	
	
	
	
}
}