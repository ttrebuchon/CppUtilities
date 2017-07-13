#pragma once

#include "FuncMatrix.h"
#include <tuple>
#include <QUtils/Func/TupleArgs.h>
#include <QUtils/Exception/NotImplemented.h>
#include <vector>
#include <QUtils/Tuple/Tuple.h>
#include <iostream>
#include "DataMatrix.h"

namespace QUtils
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
	const tensor_t<Dims-1, Elem, Index>& FuncMatrix<Dims, Elem, Index>::operator()(Index i) const
	{
		if (instantiated.count(i) <= 0)
		{
			auto nPtr = this->operator[](i);
			((FuncMatrix<Dims, Elem, Index>*)this)->instantiated[i] = nPtr;
		}
		static_assert(std::is_same<decltype(instantiated.at(i)), const tensor_t<Dims-1, Elem, Index>&>::value, "static_assert type failure");
		return (const tensor_t<Dims-1, Elem, Index>&)instantiated.at(i);
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::mul(const Elem n)
	{
		auto Def = this->def;
		tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
		{
			return Def(args...)*n;
		});
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
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
			auto Def = this->def;
			FuncMatrix<Dims, Elem, Index>& M = (FuncMatrix<Dims, Elem, Index>&)m;
			Func mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
			{
				return (Def(args...) * mDef(args...));
			});
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			tensor_t<Dims, Elem, Index> ret = new DataMatrix<Dims, Elem, Index, std::vector>();
			for (int i = 0; i < Dims; i++)
			{
				ret->setSize(i, nSize[i]);
			}
			
			for (int i = 0; i < nSize[0]; i++)
			{
				ret(i) = (*this)(i) * m(i);
			}
			return ret;
		}
		
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::div(const Elem n)
	{
		auto Def = this->def;
		tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
		{
			return Def(args...)/n;
		});
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
		}
		return ret;
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::div(const tensor_t<Dims, Elem, Index> m)
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
			auto Def = this->def;
			FuncMatrix<Dims, Elem, Index>& M = (FuncMatrix<Dims, Elem, Index>&)m;
			Func mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>([=] (auto... args)
			{
				return (Def(args...) / mDef(args...));
			});
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			tensor_t<Dims, Elem, Index> ret = new DataMatrix<Dims, Elem, Index, std::vector>();
			for (int i = 0; i < Dims; i++)
			{
				ret->setSize(i, nSize[i]);
			}
			
			for (int i = 0; i < nSize[0]; i++)
			{
				ret(i) = (*this)(i) / m(i);
			}
			return ret;
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
			auto Def = this->def;
			auto& M = (FuncMatrix<Dims, Elem, Index>&)*(std::shared_ptr<Matrix<Dims, Elem, Index>>)m;
			Func mDef = M.def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>(Func([=] (auto... args)
			{
				return (Def(args...) + mDef(args...));
			}));
			for (auto i = 0; i < Dims; i++)
			{
				ret->size[i] = nSize[i];
			}
			return ret;
		}
		else
		{
			tensor_t<Dims, Elem, Index> ret = new DataMatrix<Dims, Elem, Index, std::vector>();
			for (int i = 0; i < Dims; i++)
			{
				ret->setSize(i, nSize[i]);
			}
			
			for (int i = 0; i < nSize[0]; i++)
			{
				ret(i) = (*this)(i) + m(i);
			}
			return ret;
		}
		
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::sub(const tensor_t<Dims, Elem, Index> m)
	{
		assert(this != NULL);
		assert(m != NULL);
		Index nSize[Dims];
		for (int i = 0; i < Dims; i++)
		{
			nSize[i] = -1;
			if (this->Size(i) == 0 || m.size(i) == 0)
			{
				throw MatrixInvalidSizeException();
			}
			
			if (m.size(i) > 0)
			{
				nSize[i] = m.size(i);
			}
			
			if ((this->Size(i) < nSize[i] && this->Size(i) > 0) || (nSize[i] < 0 && this->Size(i) > 0))
			{
				nSize[i] = this->Size(i);
			}
			
			if (nSize[i] == 0)
			{
				nSize[i] = -1;
			}
		}
		
		if (m.imp() == "FuncMatrix")
		{
			auto& M = (FuncMatrix<Dims, Elem, Index>&)*(std::shared_ptr<Matrix<Dims, Elem, Index>>)m;
			auto mDef = M.def;
			auto thisDef = this->def;
			tensor_t<Dims, Elem, Index> ret = std::make_shared<FuncMatrix<Dims, Elem, Index>>(Func([=] (auto... args)
			{
				return (thisDef(args...) - mDef(args...));
			}));
			for (auto i = 0; i < Dims; i++)
			{
				ret->setSize(i, nSize[i]);
			}
			return ret;
		}
		else
		{
			tensor_t<Dims, Elem, Index> ret = new DataMatrix<Dims, Elem, Index>();
			ret.setSize(0, this->Size(0));
			for (Index i = 0; i < this->Size(0); i++)
			{
				ret(i) = (*this)(i) - m(i);
			}
			return ret;
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
		auto func = this->def;
		tensor_t<Dims, Elem, Index> n = std::make_shared<FuncMatrix>(
		[=] (auto... args)
		{
			auto revArgs = reverseTuple(args...);
			return call_tuple_args(func, revArgs);
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
	
	
	template <int index, int size>
	struct _TupleEveryOther
	{
		template <typename... Args>
		static auto call(std::tuple<Args...> tup)
		{
			static_assert(sizeof...(Args) == size, "");
			auto n = _TupleEveryOther<index+2, size>::call(tup);
			auto val = std::get<index>(tup);
			
			auto N = QUtils::Make_Tuple(n);
			return N.prepend(val).getStd();
		}
	};
	
	template <int size>
	struct _TupleEveryOther<size, size>
	{
		template <typename... Args>
		static auto call(std::tuple<Args...> tup)
		{
			return std::make_tuple();
			//auto val = std::get<index>(tup);
			//return make_tuple(val);
		}
	};
	
	template <typename... Args>
	auto TupleEveryOther(std::tuple<Args...> tup)
	{
		return _TupleEveryOther<0, sizeof...(Args)>::call(tup);
	}
	
	
	
	template <int Dims, typename Elem, typename Index>
	struct BlockHelper
	{
		template <int... Nums, typename... Args>
		static std::tuple<Args...> combine(seq<Nums...>, std::tuple<Args...> tup1, std::tuple<Args...> tup2)
		{
			static_assert(sizeof...(Args) == sizeof...(Nums), "BlockHelper::combine() arguments error");
			return std::make_tuple((std::get<Nums>(tup1) + std::get<Nums>(tup2))...);
		}
		
		
		
		
		template <typename... Args>
		static tensor_t<Dims, Elem, Index> call(std::tuple<Args...> tup, auto func)
		{
			static_assert(2*Dims == sizeof...(Args), "");
			//...
			auto everyOther = TupleEveryOther(tup);
			
			
			
			auto nFunc = [=](auto... args) -> Elem
			{
				auto combined = BlockHelper<Dims, Elem, Index>::combine(typename seqgen<0, sizeof...(Args)/2-1>::value(), std::make_tuple(args...), (std::tuple<decltype(args)...>)everyOther);
				return call_tuple_args(func, combined);
			};
			tensor_t<Dims, Elem, Index> tensor = new FuncMatrix<Dims, Elem, Index>(nFunc);
			setSizes(tensor, tup);
			return tensor;
			
		}
		
		template <typename... Args>
		static void setSizes(tensor_t<Dims, Elem, Index> tensor, std::tuple<Args...> tup)
		{
			int sizeInd = Dims - sizeof...(Args) / 2;
			auto valueIndex = std::get<1>(tup) - std::get<0>(tup);
			tensor.setSize(sizeInd, valueIndex);
			auto nTup = Make_Tuple(tup);
			setSizes(tensor, nTup.template takeBack<sizeof...(Args) - 2>().getStd());
		}
		
		static void setSizes(tensor_t<Dims, Elem, Index> tensor, std::tuple<Index, Index> tup)
		{
			int sizeInd = Dims - 1;
			auto valueIndex = std::get<1>(tup) - std::get<0>(tup);
			tensor.setSize(sizeInd, valueIndex);
		}
		
		
		
	};
	
	
	
	
	
	
	
	
	
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
		assert(this != NULL);
		assert(m != NULL);
		const int nDims = Dims+Dims2-2;
		
		
		bool thisAll1 = true;
		bool mAll1 = true;
		for (int i = 0; i < Dims && (thisAll1 || mAll1); i++)
		{
			if (thisAll1)
			{
				thisAll1 = (this->Size(i) == 1);
			}
			if (mAll1)
			{
				mAll1 = (m.size(i) == 1);
			}
		}
		
		/*if (mAll1)
		{
			if (Dims2 == 2)
			{
				return (tensor_t<Dims+Dims2-2, Elem, Index>)(this->operator*(m(0, 0)));
			}
		}
		if (thisAll1)
		{
			if (Dims == 2)
			{
				return (tensor_t<Dims+Dims2-2, Elem, Index>)(m*((*this)(0, 0)));
			}
		}*/
		
		
		
		
		
		if (this->Size(Dims-1) != m.size(0) || this->Size(Dims-1) <= 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		//std::cout << "Cloning m [Imp: " << std::flush << m.imp() << "]" << std::endl;
		auto am = m->clone();
		
		
		
		//std::cout << "Cloning this" << std::endl;
		auto tclone = this->clone();
		//std::cout << "Making res" << std::endl;
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
		//std::cout << "FuncMatrix defined" << std::endl;
		
		
		
		
		for (int i = 0; i < Dims-1; i++)
		{
			res.setSize(i, this->Size(i));
		}
		//std::cout << "Size 1 set" << std::endl;
		for (int i = 1; i < Dims2; i++)
		{
			res.setSize(i+Dims-2, m.size(i));
		}
		//std::cout << "Size 2 set" << std::endl;
		return res.toDataTensor();
	}
	
	namespace _Helpers
	{
	template <int Dims, typename Elem, typename Index>
	struct FuncMatrix_Inv_Dims_Filter
	{
	static tensor_t<2, Elem, Index> call(const tensor_t<Dims, Elem, Index>&)
	{
		throw MatrixInvalidSizeException();
	}
	};
	
	template <typename Elem, typename Index>
	struct FuncMatrix_Inv_Dims_Filter<2, Elem, Index>
	{
	static tensor_t<2, Elem, Index> call(const tensor_t<2, Elem, Index>& m)
	{
		auto size1 = m.size(0);
		auto size2 = m.size(1);
		assert(size1 != 0);
		assert(size2 != 0);
		if (size1 > 0 && size2 > 0 && size1 != size2)
		{
			auto transpose = m.T();
			tensor_t<2, Elem, Index> tensor_this = tensor_t<2, Elem, Index>(((FuncMatrix<2, Elem, Index>*)m.get())->get_ptr());
			return transpose.contract(tensor_this).inv().contract(transpose);
		}
		if (size1 == 1 && size2 == 1)
		{
			tensor_t<2, Elem, Index> oneRet = new DataMatrix<2, Elem, Index>();
			oneRet.setSize(0, 1);
			oneRet(0) = tensor_t<1, Elem, Index>({static_cast<Elem>(static_cast<Elem>(1)/m(0, 0))});
			return oneRet;
			
		}
		
		Index iSize;
		if (size1 < size2)
		{
			iSize = size1;
			
		}
		else
		{
			iSize = size2;
		}
		
		Index ASize = iSize/2;
		Index DSize = ASize;
		if (iSize % 2 != 0)
		{
			DSize++;
		}
		assert(ASize + DSize == iSize);
		
		auto A = m->block(std::make_tuple(0, ASize, 0, ASize)).toDataTensor();
		auto B = m->block(std::make_tuple(0, ASize, ASize, size2)).toDataTensor();
		auto C = m->block(std::make_tuple(ASize, size1, 0, size2 - DSize)).toDataTensor();
		auto D = m->block(std::make_tuple(ASize, size1, size2-DSize, size2)).toDataTensor();
		
		
		
		tensor_t<2, Elem, Index> aInv = A.inv();
		auto AB = aInv.contract(B);
		auto DCABi = (D - C.contract(AB)).inv();
		auto CAi = C.contract(aInv);
		auto newA = aInv + AB.contract(DCABi).contract(CAi);
		auto newB = AB.contract(DCABi)*-1;
		assert(newB.size(0) == B.size(0));
		assert(newB(0).size(0) == B(0).size(0));
		auto newC = DCABi.contract(CAi)*-1;
		auto newD = DCABi;
		auto getAt = [=](Index i, Index j) -> Elem {
			if (i >= newA.size(0))
			{
				if (j >= newA.size(1))
				{
					return newD[i - newA.size(0)][j - newA.size(1)];
				}
				else
				{
					return newC(i - newA.size(0), j);
				}
			}
			else
			{
				if (j >= newA.size(1))
				{
					return newB[i][j - newA.size(1)];
				}
				else
				{
					return newA[i][j];
				}
			}
		};
		tensor_t<2, Elem, Index> solution = new DataMatrix<2, Elem, Index>();
		solution.setSize(0, m.size(0));
		solution.setSize(1, m.size(1));
		for (Index i = 0; i < m.size(0); i++)
		{
			for (Index j = 0; j < m(i).size(0); j++)
			{
				solution(i, j) = getAt(i, j);
			}
		}
		
		assert(solution.size(0) == solution->Size(0));
		assert(solution.size(1) == solution->Size(1));
		return solution;
	}
	};
	}
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<2, Elem, Index> FuncMatrix<Dims, Elem, Index>::inv() const
	{
		assert(Dims == 2);
		return _Helpers::FuncMatrix_Inv_Dims_Filter<Dims, Elem, Index>::call(this->get_ptr());
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::block(typename _Helpers::TupleBuilder<2*Dims, Index>::value tup) const
	{
		auto tensor = _Helpers::BlockHelper<Dims, Elem, Index>::call(tup, this->def);
		return tensor;
	}
	
	template <int Dims, typename Elem, typename Index>
	tensor_t<Dims, Elem, Index> FuncMatrix<Dims, Elem, Index>::toDataTensor() const
	{
		assert(this->Size(0) >= 0);
		
		tensor_t<Dims, Elem, Index> dat = new DataMatrix<Dims, Elem, Index>();
		dat.setSize(0, this->Size(0));
		for (Index i = 0; i < this->Size(0); i++)
		{
			dat(i) = (*this)(i).toDataTensor();
		}
		return dat;
		
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
		if (i >= this->Size(0) && this->Size(0) >= 0)
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
	const Elem& FuncMatrix<1, Elem, Index>::operator()(Index i) const
	{
		if (instantiated.count(i) <= 0)
		{
			auto nElem = this->operator[](i);
			((FuncMatrix<1, Elem, Index>*)this)->instantiated[i] = nElem;
		}
		return instantiated.at(i);
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::mul(const Elem n)
	{
		auto Def = this->def;
		tensor_t<1, Elem, Index> ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
		{
			return Def(i)*n;
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
			auto Def = this->def;
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			auto mDef = M.def;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (Def(i) * mDef(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			auto ret = tensor_t<1, Elem, Index>(new DataMatrix<1, Elem, Index, std::vector>());
			ret->setSize(0, nSize);
			for (int i = 0; i < nSize; i++)
			{
				ret(i) = (*this)(i) * m(i);
			}
			return ret;
		}
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::div(const Elem n)
	{
		auto Def = this->def;
		tensor_t<1, Elem, Index> ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
		{
			return Def(i)/n;
		}));
		ret->setSize(0, this->size[0]);
		return ret;
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::div(const tensor_t<1, Elem, Index> m)
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
			auto Def = this->def;
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			auto mDef = M.def;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (Def(i) / mDef(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			auto ret = tensor_t<1, Elem, Index>(new DataMatrix<1, Elem, Index, std::vector>());
			ret->setSize(0, nSize);
			for (int i = 0; i < nSize; i++)
			{
				ret(i) = (*this)(i) / m(i);
			}
			return ret;
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
			auto Def = this->def;
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			auto mDef = M.def;
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (Def(i) + mDef(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			auto ret = tensor_t<1, Elem, Index>(new DataMatrix<1, Elem, Index, std::vector>());
			ret->setSize(0, nSize);
			for (int i = 0; i < nSize; i++)
			{
				ret(i) = (*this)(i) + m(i);
			}
			return ret;
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
			auto Def = this->def;
			FuncMatrix<1, Elem, Index>& M = (FuncMatrix<1, Elem, Index>&)*(std::shared_ptr<Matrix<1, Elem, Index>>)m;
			auto mDef = M.def;
			
			auto ret = tensor_t<1, Elem, Index>(std::make_shared<FuncMatrix<1, Elem, Index>>([=] (Index i)
			{
				return (Def(i) - mDef(i));
			}));
			ret->setSize(0, nSize);
			return ret;
		}
		else
		{
			auto ret = tensor_t<1, Elem, Index>(new DataMatrix<1, Elem, Index, std::vector>());
			ret->setSize(0, nSize);
			for (int i = 0; i < nSize; i++)
			{
				ret(i) = (*this)(i) - m(i);
			}
			return ret;
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
		auto this_size = this->Size(0);
		auto Def = this->def;
		auto overrides = this->instantiated;
		return tensor_t<2, Elem, Index>(new FuncMatrix<2, Elem, Index>([overrides, Def] (Index i, Index j) {
			if (overrides.count(j) > 0)
			{
				return overrides.at(j);
			}
			
			return Def(j);
		}, 1, this_size));
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::submatrix(std::tuple<Index> t) const
	{
		auto count = this->Size(0);
		if (count == 1 || count == 0)
		{
			throw MatrixInvalidSizeException();
		}
		auto f = this->def;
		Index index = std::get<0>(t);
		return tensor_t<1, Elem, Index>([f, index] (Index i) -> Elem {
			if (i < index)
			{
				return f(i);
			}
			else
			{
				return f(i+1);
			}
		}, this->Size(0)-1);
	}
	
	template <typename Elem, typename Index>
	void FuncMatrix<1, Elem, Index>::append(Elem t)
	{
		Index nSize = this->Size(0)+1;
		this->setSize(0, nSize);
		(*this)(nSize-1) = t;
	}
	
	template <typename Elem, typename Index>
	tensor_t<2, Elem, Index> FuncMatrix<1, Elem, Index>::inv() const
	{
		auto transpose = T();
		tensor_t<1, Elem, Index> tensor_this = tensor_t<1, Elem, Index>(((FuncMatrix<1, Elem, Index>*)this)->get_ptr());
		auto inner = transpose.contract(tensor_this).inv();
		if (inner.size(0) == 1 && inner.size(1) == 1)
		{
			return transpose*inner(0, 0);
		}
		else
		{
			return inner.contract(transpose);
		}
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::block(typename _Helpers::TupleBuilder<2, Index>::value tup) const
	{
		Index start = std::get<0>(tup);
		Index end = std::get<1>(tup);
		
		auto func = this->def;
		tensor_t<1, Elem, Index> m = new FuncMatrix<1, Elem, Index>([=](Index i) -> Elem {
			return func(i + start);
		}, end - start);
		
		return m;
	}
	
	template <typename Elem, typename Index>
	tensor_t<1, Elem, Index> FuncMatrix<1, Elem, Index>::toDataTensor() const
	{
		assert(this->Size(0) >= 0);
		
		tensor_t<1, Elem, Index> dat = new DataMatrix<1, Elem, Index>();
		dat.setSize(0, this->Size(0));
		for (Index i = 0; i < this->Size(0); i++)
		{
			dat(i) = (*this)[i];
		}
		return dat;
		
	}
	
	
	
	
	
}
}