#pragma once

#include "Matrix.h"
#include <tuple>
#include <Func/TupleArgs.h>
#include "FuncArgHelper.h"
#include <sstream>

namespace Util
{
namespace Math
{
	namespace _Helpers
	{
		
		template <int N, typename Type, typename ...Args>
		struct n_args
		{
			typedef typename n_args<N-1, Type, Type, Args...>::value value;
			
			static value call(Type t, Args... args)
			{
				return n_args<N-1, Type, Type, Args...>::call(t, t, args...);
			}
		};
		
		template <typename Type, typename ...Args>
		struct n_args<0, Type, Args...>
		{
			typedef std::tuple<Args...> value;
			
			static value call(Type, Args... vals)
			{
				return std::make_tuple(vals...);
			}
		};
		
		template <int N, typename Num>
		typename n_args<N, Num>::value n_zeros_tup()
		{
			return n_args<N, Num>::call(0);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		template <int size, int index, typename Num_t, typename ...Args>
		struct tuple_adder
		{
			
			static Num_t call(Num_t total, std::tuple<Args...> nums)
			{
				return tuple_adder<size, index+1, Num_t, Args...>::call(total + std::get<index>(nums), nums);
			}
		};
		
		template <int size, typename Num_t, typename ...Args>
		struct tuple_adder<size, size, Num_t, Args...>
		{
			
			static Num_t call(Num_t total, std::tuple<Args...> nums)
			{
				return total;
			}
		};
		
		template <typename Num_t, typename ...Args>
		Num_t tuple_sum(std::tuple<Args...> t)
		{
			return tuple_adder<sizeof...(Args), 0, Num_t, Args...>::call(0, t);
		}
		
		
		
		template <int i, int Dims, typename Elem, typename Index>
		struct matrix_at_tup
		{
			template <typename ...Args>
			static Elem call(const std::shared_ptr<const Matrix<Dims, Elem, Index>> m, std::tuple<Args...> t)
			{
				auto m2 = m->at(std::get<sizeof...(Args)-i>(t));
				auto r = matrix_at_tup<i-1, Dims-1, Elem, Index>::call(m2, t);
				return r;
			}
		};
		
		template <typename Elem, typename Index>
		struct matrix_at_tup<1, 1, Elem, Index>
		{
			template <typename ...Args>
			static Elem call(const std::shared_ptr<const Matrix<1, Elem, Index>> m, std::tuple<Args...> t)
			{
				auto v = m->at(std::get<sizeof...(Args)-1>(t));
				return v;
			}
		};
		
		
		
		template <int Dims, typename Elem, typename Index, typename ...Args>
		Elem matrix_at(const std::shared_ptr<const Matrix<Dims, Elem, Index>> m, std::tuple<Args...> t)
		{
			return matrix_at_tup<Dims, Dims, Elem, Index>::call(m, t);
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	Elem Matrix<Dims, Elem, Index>::det() const
	{
		Index size = this->Size(0);
		for (auto i = 0; i < Dims; i++)
		{
			if (size != -1)
			{
				break;
			}
			size = this->Size(i);
		}
		
		for (auto i = 1; i < Dims; i++)
		{
			if (this->Size(i) != size && this->Size(i) != -1)
			{
				throw MatrixInvalidSizeException();
			}
		}
		if (size == 1)
		{
			auto tmp = at(0);
			auto val = tmp->det();
			return val;
		}
		
		auto cof = [](auto i)
		{
			return ((i % 2)*(-2) + 1);
		};
		
		Elem total = 0;
		
		for (auto i = 0; i < size; i++)
		{
			auto atArgs = _Helpers::ConcatArgs<Index>::Get(i, _Helpers::n_zeros_tup<Dims-1, Index>());
			
			Elem currentVal = _Helpers::matrix_at(this->get_ptr(), atArgs);
			if (currentVal != 0)
			{
				total += cof(i)*minor(_Helpers::ConcatArgs<Index>::Get(i, _Helpers::n_zeros_tup<Dims-1, Index>()))*currentVal;
			}
		}
		
		return total;
	}
	
	template <int Dims, typename Elem, typename Index>
	Elem Matrix<Dims, Elem, Index>::minor(typename _Helpers::TupleBuilder<Dims, Index>::value indexes) const
	{
		auto sub = submatrix(indexes);
		Elem val = sub->det();
		return val;
	}
	
	template <int Dims, typename Elem, typename Index>
	std::string Matrix<Dims, Elem, Index>::toString() const
	{
		std::stringstream val;
		val << "[ ";
		for (Index i = 0; i < this->size[0]; i++)
		{
			if (i > 0)
			{
				val << ", ";
			}
			auto tmp = this->at(i);
			val << tmp->toString();
		}
		val << " ]";
		return val.str();
	}
	
	template <int Dims, typename Elem, typename Index>
	void Matrix<Dims, Elem, Index>::set(const Index i, const tensor_t<Dims-1, Elem, Index> ptr)
	{
		(*this)(i) = *ptr;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	Elem Matrix<1, Elem, Index>::det() const
	{
		if (this->size[0] != 1)
		{
			throw MatrixInvalidSizeException();
		}
		
		return at(0);
	}
	
	template <typename Elem, typename Index>
	std::string Matrix<1, Elem, Index>::toString() const
	{
		std::stringstream val;
		val << "[";
		for (Index i = 0; i < this->size[0]; i++)
		{
			if (i > 0)
			{
				val << ", ";
			}
			val << this->at(i);
		}
		val << "]";
		return val.str();
	}
	
}
}