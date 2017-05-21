#pragma once

#include "FuncMatrix.h"
#include <tuple>
#include <Func/TupleArgs.h>
#include <Exception/NotImplemented.h>
#include <vector>

namespace Util
{
namespace Math
{
	
	
	
	
	//For a tuple of "Args", reverse
	//the ordering of the items
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
	FuncMatrix<Dims, Elem, Index>::FuncMatrix(Func f) : Matrix<Dims, Elem, Index>(), def(f), instantiated()
	{
		
	}
	
	template <int Dims, typename Elem, typename Index>
	FuncMatrix<Dims, Elem, Index>::FuncMatrix(const FuncMatrix<Dims, Elem, Index>& m) : Matrix<Dims, Elem, Index>(m), def(m.def), instantiated()
	{
		for (auto pair : m.instantiated)
		{
			this->instantiated[pair.first] = tensor_t<Dims-1, Elem, Index>(pair.second->clone());
		}
	}
	
	template <int Dims, typename Elem, typename Index>
	template <typename... Size>
	FuncMatrix<Dims, Elem, Index>::FuncMatrix(Func f, Index s1, Size... sizes) : Matrix<Dims, Elem, Index>(), def(f), instantiated()
	{
		static_assert(sizeof...(Size) > 0, "Wrong method being called!");
		auto sizeVec = _Helpers::ArgsToVec<Index>::call(sizes...);
		this->setSize(0, s1);
		for (auto i = 0; i < Dims-1 && i < sizeVec.size(); i++)
		{
			this->setSize(i+1, sizeVec[i]);
		}
	}
	
	template <int Dims, typename Elem, typename Index>
	void FuncMatrix<Dims, Elem, Index>::setSize(const Index dim, const Index s)
	{
		if (dim >= Dims || dim < 0)
		{
			throw std::out_of_range("FuncMatrix::set_size_check");
		}
		this->size[dim] = s;
		if (dim > 0)
		{
			for (auto pair : this->instantiated)
			{
				pair.second->setSize((const Index)(dim-1), (const Index)s);
			}
		}
		else
		{
			this->size[0] = s;
			std::vector<Index> toRemove;
			for (auto pair : this->instantiated)
			{
				if (pair.first >= s)
				{
				toRemove.push_back(pair.first);
				}
			}
			for (auto key : toRemove)
			{
				this->instantiated.erase(key);
			}
		}
	}
	
	
	//Create a new matrix of one less
	//dimension (The value at this[i])
	//by plugging the "i" argument in
	//and returning a new functional
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims-1, Elem, Index> FuncMatrix<Dims, Elem, Index>::operator[](Index i) const
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("FuncMatrix::size_check");
		}
		if (instantiated.count(i) > 0)
		{
			return ((FuncMatrix<Dims, Elem, Index>*)this)->instantiated[i]->clone();
		}
		tensor_t<Dims-1, Elem, Index> tmp =  std::make_shared<FuncMatrix<Dims-1, Elem, Index>>(([=](auto ...args) -> Elem { return def(i, args...); }));
		
		for (auto i = 1; i < Dims; i++)
		{
			tmp->size[i-1] = this->size[i];
		}
		return tmp;
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims-1, Elem, Index>& FuncMatrix<Dims, Elem, Index>::operator()(Index i)
	{
		if (instantiated.count(i) <= 0)
		{
			auto nPtr = this->operator[](i);
			instantiated[i] = nPtr;
		}
		static_assert(std::is_same<decltype(instantiated[i]), tensor_t<Dims-1, Elem, Index>&>::value, "static_assert type failure");
		return (tensor_t<Dims-1, Elem, Index>&)instantiated[i];
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::mul(const double n)
	{
		tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
		{
			return def(args...)*n;
		});
		for (auto i = 0; i < Dims; i++)
		{
			ret->size[i] = this->size[i];
		}
		return ret;
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::mul(const tensor_t<Dims, Elem, Index> m)
	{
		Index nSize[Dims];
		for (int i = 0; i < Dims; i++)
		{
			nSize[i] = -1;
			if (this->size[i] == 0 || m.size(i) == 0)
			{
				throw MatrixInvalidSizeException();
			}
			
			if (m.size(i) > 0)
			{
				nSize[i] = m.size(i);
			}
			
			if ((this->size[i] < nSize[i] && this->size[i] > 0) || (nSize[i] < 0 && this->size[i] > 0))
			{
				nSize[i] = this->size[i];
			}
			
			if (nSize[i] == 0)
			{
				nSize[i] = -1;
			}
		}
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<Dims, Elem, Index>& M = (FuncMatrix<Dims, Elem, Index>&)m;
			Func mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
			{
				return (def(args...) * mDef(args...));
			});
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			throw NotImp();
		}
		
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::add(const tensor_t<Dims, Elem, Index> m)
	{
		Index nSize[Dims];
		for (int i = 0; i < Dims; i++)
		{
			nSize[i] = -1;
			if (this->size[i] == 0 || m.size(i) == 0)
			{
				throw MatrixInvalidSizeException();
			}
			
			if (m.size(i) > 0)
			{
				nSize[i] = m.size(i);
			}
			
			if ((this->size[i] < nSize[i] && this->size[i] > 0) || (nSize[i] < 0 && this->size[i] > 0))
			{
				nSize[i] = this->size[i];
			}
			
			if (nSize[i] == 0)
			{
				nSize[i] = -1;
			}
		}
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<Dims, Elem, Index>& M = (FuncMatrix<Dims, Elem, Index>&)m;
			Func mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>(Func([=] (auto... args)
			{
				return (def(args...) + mDef(args...));
			}));
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			throw NotImp();
		}
		
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::sub(const tensor_t<Dims, Elem, Index> m)
	{
		Index nSize[Dims];
		for (int i = 0; i < Dims; i++)
		{
			nSize[i] = -1;
			if (this->size[i] == 0 || m.size(i) == 0)
			{
				throw MatrixInvalidSizeException();
			}
			
			if (m.size(i) > 0)
			{
				nSize[i] = m.size(i);
			}
			
			if ((this->size[i] < nSize[i] && this->size[i] > 0) || (nSize[i] < 0 && this->size[i] > 0))
			{
				nSize[i] = this->size[i];
			}
			
			if (nSize[i] == 0)
			{
				nSize[i] = -1;
			}
		}
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<Dims, Elem, Index>& M = (FuncMatrix<Dims, Elem, Index>&)m;
			auto mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>(Func([=] (auto... args)
			{
				return (def(args...) - mDef(args...));
			}));
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			throw NotImp();
		}
		
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::clone() const
	{
		auto nPtr = std::make_shared<FuncMatrix>(this->def);
		for (int i = 0; i < Dims; i++)
		{
			nPtr->size[i] = this->size[i];
		}
		for (auto KV : this->instantiated)
		{
			nPtr->instantiated[KV.first] = tensor_t<Dims-1, Elem, Index>(KV.second->clone());
		}
		return tensor_t<Dims, Elem, Index>(nPtr);
	}
	
	//Transpose the matrix by reversing
	//the order of the functions
	//arguments 
	//Ex: f(i, j, k) => f(k, j, i)
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::T() const
	{
		tensor_t<Dims, Elem, Index> n = std::make_shared<FuncMatrix>(
		[=] (auto... args)
		{
			auto revArgs = reverseTuple(args...);
			return call_tuple_args(def, revArgs);
		});
		for (int i = 0; i < Dims; i++)
		{
			n->setSize(i, this->size[Dims-1-i]);
		}
		return n;
	}
	
	
	
	
	
	
	
	
	namespace _Helpers
	{
	//Helper that offsets index
	//arguments if necessary for
	//creating a new functional for a
	//submatrix
	template <int N, int ...Nums>
	class ProcHelper
	{
		public:
		template <typename ...Args>
		static std::tuple<Args...> Proc(std::tuple<Args...> deleted, std::tuple<Args...> arguments)
		{
			return ProcHelper<N-1, N-1, Nums...>::Proc(deleted, arguments);
		}
	};
	
	template <int ...Nums>
	class ProcHelper<0, Nums...>
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
	
	
	
	
	
	template <int ...Nums> struct seq { };
	
	template <int First, int Last, int ...Nums>
	struct seqgen
	{
		typedef typename seqgen<First, Last-1, Last, Nums...>::value value;
	};
	
	template <int First, int... Nums>
	struct seqgen<First, First, Nums...>
	{
		typedef seq<First, Nums...> value;
	};
	
	
	template <typename T, typename ...Args, int ...Nums>
	std::tuple<Args...> tuple_remove_first_inner(std::tuple<T, Args...> t, seq<Nums...>)
	{
		return std::make_tuple(std::get<Nums>(t)...);
	}
	
	
	template <typename T, typename ...Args>
	std::tuple<Args...> tuple_remove_first(std::tuple<T, Args...> t)
	{
		return tuple_remove_first_inner(t, typename seqgen<1, sizeof...(Args)>::value());
	}
	
	
	
	
	
	
	
	template <int N, typename Elem, typename Index>
	struct Caller
	{
		template <typename ...Args>
		static Matrix<1, Elem, Index>* PrefixCaller(Matrix<N, Elem, Index>* m, Index i, Args... args)
	{
		auto m2 = (*m)[i];
		auto m3 = Caller<N-1, Elem, Index>::PrefixCaller(m2, args...);
		delete m2;
		return m3;		
	}
		
		template <typename ...Args>
		static Elem PostfixCaller(Matrix<N-1, Elem, Index>* m, Index i, Args... args)
		{
			auto m2 = (*m)[i];
			auto m3 = Caller<N-1, Elem, Index>::PostfixCaller(m2, args...);
			delete m2;
			return m3;
		}
		
		template <typename ...Args>
		static Elem PostfixCaller_T(Matrix<N-1, Elem, Index>* m, std::tuple<Index, Args...> argsT)
		{
			auto m2 = (*m)[std::get<0>(argsT)];
			auto m3 = Caller<N-1, Elem, Index>::PostfixCaller_T(m2, tuple_remove_first(argsT));
			delete m2;
			return m3;
		}
	
	};
	
	template <typename Elem, typename Index>
	struct Caller<2, Elem, Index>
	{
		template <typename ...Args>
		static std::shared_ptr<Matrix<1, Elem, Index>> PrefixCaller(std::shared_ptr<Matrix<2, Elem, Index>> m, Index i, Args... args)
	{
		auto m2 = (*m)[i];
		return m2;
	}
	template <typename ...Args>
	static Elem PostfixCaller(std::shared_ptr<Matrix<1, Elem, Index>> m, Index i, Args... args)
		{
			auto m2 = (*m)[i];
			return m2;
		}
		
		
	template <typename ...Args>
		static Elem PostfixCaller_T(std::shared_ptr<Matrix<1, Elem, Index>> m, std::tuple<Index, Args...> argsT)
		{
			auto m2 = (*m)[std::get<0>(argsT)];
			return m2;
		}
	};
	
	template <typename Elem, typename Index>
	struct Caller<1, Elem, Index>
	{
		template <typename ...Args>
		static Elem PostfixCaller_T(Elem e, std::tuple<>)
		{
			return e;
		}
	};
	
	
	template <int N, int ...Nums>
	struct TuplePost
	{
		template <typename ...Args>
		static auto Get(std::tuple<Args...> tup)
		{
			return TuplePost<N-1, Nums..., (sizeof...(Args)-N)>::Get(tup);
		}
	};
	
	template <int ...Nums>
	struct TuplePost<0, Nums...>
	{
		template <typename ...Args>
		static auto Get(std::tuple<Args...> tup)
		{
			return std::make_tuple(std::get<Nums>(tup)...);
		}
	};
	
	template <typename T>
	bool try_delete(T t)
	{
		return false;
	}
	
	template <typename T>
	bool try_delete(T* t)
	{
		delete t;
		return true;
	}
	
	
	
	
	
	
	
	
	
	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value removed) const
	{
		for (auto size : this->size)
		{
			if (size <= 1)
			{
				throw MatrixInvalidSizeException();
			}
		}
		auto defco = Func(def);
		tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>(
		[=] (auto... args)
		{
			//Package the functional's
			//arguments into a tuple
			//Pass both that and the
			//submatrix() arg tuple
			//containing the indexes of
			//the removed rows/cols
			//into Proc() to have the
			//functional's indexes be
			//offset if necessary, and
			//return a tuple of
			//corrected args,
			//Use call_tuple_args() to
			//call def with the
			//modified arguments
			return call_tuple_args(defco, _Helpers::ProcHelper<Dims>::Proc(removed, std::make_tuple(args...)));
		});
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->size[i] - 1);
		}
		
		return ret;
	}
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	template <int Dims2>
	tensor_t<Dims+Dims2-2, Elem, Index> Matrix<Dims, Elem, Index>::contract(tensor_t<Dims2, Elem, Index> m)
	{
		const int nDims = Dims+Dims2-2;
		if (this->size[Dims-1] != m.size(0) || this->size[Dims-1] <= 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		auto am = m->clone();
		
		
		
		
		auto tclone = this->clone();
		tensor_t<nDims, Elem, Index> res = std::make_shared<FuncMatrix<nDims, Elem, Index>>([=] (auto... args)
		{
			
			auto m_1 = _Helpers::Caller<Dims, Elem, Index>::PrefixCaller(tclone, args...);
			Elem val = 0;
			for (Index i = 0; i < am.size(0); i++)
			{
				
				auto m2_tmp = am->at(i);
				
				auto m2_args_tup = _Helpers::TuplePost<Dims2-1>::Get(std::make_tuple(args...));
				Elem m_2_val = _Helpers::Caller<Dims2, Elem, Index>::PostfixCaller_T(m2_tmp, m2_args_tup);
				
				_Helpers::try_delete(m2_tmp);
				val += m_1->at(i)*m_2_val;
			}
			return val;
		});
		
		
		
		
		
		for (int i = 0; i < Dims-1; i++)
		{
			res.setSize(i, this->size[i]);
		}
		for (int i = 1; i < Dims2; i++)
		{
			res.setSize(i+Dims-2, m.size(i));
		}
		return res;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	FuncMatrix<1, Elem, Index>::FuncMatrix(std::function<Elem(Index)> f) : Matrix<1, Elem, Index>(), def(f)
	{
		
	}

	template <typename Elem, typename Index>
	FuncMatrix<1, Elem, Index>::FuncMatrix(const FuncMatrix<1, Elem, Index>& m) : Matrix<1, Elem, Index>(m), def(m.def)
	{
		for (auto pair : m.instantiated)
		{
			this->instantiated[pair.first] = pair.second;
		}
	}
	
	template <typename Elem, typename Index>
	FuncMatrix<1, Elem, Index>::FuncMatrix(std::function<Elem(Index)> f, Index size) : Matrix<1, Elem, Index>(), def(f)
	{
		this->setSize(0, size);
	}
	
	template <typename Elem, typename Index>
	void FuncMatrix<1, Elem, Index>::setSize(const Index dim, const Index s)
	{
		if (dim > 0 || dim < 0)
		{
			throw std::out_of_range("FuncMatrix::set_size_check");
		}
		
		this->size[0] = s;
		std::vector<Index> toRemove;
		for (auto pair : this->instantiated)
		{
			if (pair.first >= s)
			{
			toRemove.push_back(pair.first);
			}
		}
		for (auto key : toRemove)
		{
			this->instantiated.erase(key);
		}
	}
	
	template <typename Elem, typename Index>
	Elem FuncMatrix<1, Elem, Index>::operator[](Index i) const
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("FuncMatrix::size_check");
		}
		if (instantiated.count(i) > 0)
		{
			return ((FuncMatrix<1, Elem, Index>*)this)->instantiated[i];
		}
		return def(i);
	}
	
	template <typename Elem, typename Index>
	Elem& FuncMatrix<1, Elem, Index>::operator()(Index i)
	{
		if (instantiated.count(i) <= 0)
		{
			auto nElem = this->operator[](i);
			instantiated[i] = nElem;
		}
		return instantiated[i];
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::mul(const double n)
	{
		tensor_t<1, Elem, Index> ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
		{
			return def(i)*n;
		}));
		ret->setSize(0, this->size[0]);
		return ret;
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::mul(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] == 0 || m.size(0) == 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		Index nSize = -1;
		if (m.size(0) > 0)
		{
			nSize = m.size(0);
		}
		
		if ((this->size[0] < nSize && this->size[0] > 0) || (nSize < 0 && this->size[0] > 0))
		{
			nSize = this->size[0];
		}
		
		if (nSize == 0)
		{
			nSize = -1;
		}
		
		
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (def(i) * M.def(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			throw NotImp();
		}
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::add(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] == 0 || m.size(0) == 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		Index nSize = -1;
		if (m.size(0) > 0)
		{
			nSize = m.size(0);
		}
		
		if ((this->size[0] < nSize && this->size[0] > 0) || (nSize < 0 && this->size[0] > 0))
		{
			nSize = this->size[0];
		}
		
		if (nSize == 0)
		{
			nSize = -1;
		}
		
		
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (def(i) + M.def(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			throw NotImp();
		}
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::sub(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] == 0 || m.size(0) == 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		Index nSize = -1;
		if (m.size(0) > 0)
		{
			nSize = m.size(0);
		}
		
		if ((this->size[0] < nSize && this->size[0] > 0) || (nSize < 0 && this->size[0] > 0))
		{
			nSize = this->size[0];
		}
		
		if (nSize == 0)
		{
			nSize = -1;
		}
		
		
		
		if (m.imp() == "FuncMatrix")
		{
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (def(i) - M.def(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			throw NotImp();
		}
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::clone() const
	{
		return tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix>(*this));
	}
	
	template <typename Elem, typename Index>
	tensor_t<2, Elem, Index> FuncMatrix<1, Elem, Index>::T() const
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::submatrix(std::tuple<Index> t) const
	{
		throw MatrixInvalidSizeException();
	}
	
	template <typename Elem, typename Index>
	void FuncMatrix<1, Elem, Index>::append(Elem t)
	{
		throw NotImp();
	}
	
	
	
	
	
}
}