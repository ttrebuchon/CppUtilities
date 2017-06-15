#pragma once

#include "DataMatrix.h"
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Tuple/Tuple.h>
#include <assert.h>
#include "FuncMatrix.hpp"
#include <QUtils/Func/TupleArgs.h>

#ifdef DEBUG

#include <assert.h>
#define sanity_d(x) assert(x)

#else

#define sanity_d(x)

#endif

namespace Util
{
namespace Math
{
	namespace _Helpers
	{
		template <int Dims, typename T, template <typename...> typename Container, typename Index>
		struct Sizer
		{
			static void getSizes(Index s[Dims], typename RecursiveDataMatrix<Dims, T, Container>::type data)
		{
			s[0] = _getSize(data);
			Sizer<Dims-1, T, Container, Index>::getSizes(&(s[1]), data[0]);
			
		}
		};
		
		
		template <typename T, template <typename...> typename Container, typename Index>
		struct Sizer<1, T, Container, Index>
		{
			static void getSizes(Index s[1], typename RecursiveDataMatrix<1, T, Container>::type data)
		{
			s[0] = _getSize(data);
		}
		};
	}
	
	template <typename Container>
	int _getSize(Container& c)
	{
		return c.size();
	}
	
	
	
	
	
	
	
	
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<Dims, Elem, Index, Container>::DataMatrix(Index size) : Matrix<Dims, Elem, Index>(), data(size)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] = std::make_shared<DataMatrix<Dims-1, Elem, Index, Container>>();
		}
	}
	
	
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<Dims, Elem, Index, Container>::DataMatrix(Data d) : Matrix<Dims, Elem, Index>(), data(d.size())
	{
		auto i = 0;
		for (auto subD : d)
		{
			data[i++] = std::make_shared<DataMatrix<Dims-1, Elem, Index, Container>>(subD);
		}
		
		this->setSize(0, d.size());
		for (int n = 1; n < Dims; n++)
		{
			this->setSize(n, data[0]->Size(n-1));
		}
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<Dims, Elem, Index, Container>::DataMatrix() : Matrix<Dims, Elem, Index>(), data(0)
	{
		for (int i = 0; i < Dims; i++)
		{
			this->size[i] = 0;
		}
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<Dims, Elem, Index, Container>::resize(const Index s)
	{
		/*std::cout << "DataMatrix<" << Dims << ">::resize(" << s << ")" << std::endl;
		std::cout << "prev size: " << data.size() << std::endl;*/
		if (s == data.size())
		{
			
		}
		else if (s < data.size())
		{
			data.resize(s);
		}
		else
		{
			auto prevS = data.size();
			data.resize(s);
			for (int i = prevS; i < data.size(); i++)
			{
				assert(data[i] == NULL);
				data[i] = std::make_shared<DataMatrix<Dims-1, Elem, Index, Container>>();
				/*std::cout << "Created " << data[i].get() << " at data[" << i << "]" << std::endl;*/
				for (int j = 1; j < Dims; j++)
				{
					data[i]->setSize(j-1, this->Size(j));
				}
				assert(data[i] != NULL);
			}
			for (int i = 0; i < data.size(); i++)
			{
				assert(data[i] != NULL);
			}
		}
		/*std::cout << "DataMatrix<" << Dims << ">::resize(" << s << ") Returning." << std::endl;*/
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<Dims, Elem, Index, Container>::setSize(const Index dim, const Index s)
	{
		/*std::cout << "DataMatrix<" << Dims << ">::setSize(" << dim << ", " << s << ")" << std::endl;*/
		assert(s >= 0);
		if (dim >= Dims || dim < 0)
		{
			throw std::out_of_range("DataMatrix::set_size_check");
		}
		this->size[dim] = s;
		/*std::cout << "this->size[dim=" << dim << "] set to " << s << std::endl;*/
		if (dim > 0)
		{
			/*std::cout << "data.size(): " << data.size() << std::endl;*/
			if (data.size() > 0)
			{
				//std::cout << data[0].get() << std::endl;
			}
			for (int i = 0; i < data.size(); i++)
			{
				assert(data[i] != NULL);
			}
			for (auto ptr : data)
			{
				assert(ptr != NULL);
				ptr->setSize((const Index)(dim-1), (const Index)s);
			}
		}
		else
		{
			this->resize(s);
		}
		//std::cout << "setSize Returning." << std::endl;
	}
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims-1, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::operator[](Index i) const
	{
		assert(i >= 0);
		if (i >= this->Size(0) && this->Size(0) >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() != this->Size(0))
		{
			throw std::range_error("DataMatrix::inconsistent_internal_sizes");
		}
		assert(data.at(i) != NULL);
		return data.at(i)->clone();
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims-1, Elem, Index>& DataMatrix<Dims, Elem, Index, Container>::operator()(Index i)
	{
		assert(i >= 0);
		if (i >= this->Size(0) && this->Size(0) >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() <= i)
		{
			this->resize(i+1);
		}
		assert(data.at(i) != NULL);
		return data.at(i);
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	const tensor_t<Dims-1, Elem, Index>& DataMatrix<Dims, Elem, Index, Container>::operator()(Index i) const
	{
		assert(i >= 0);
		if (i >= this->Size(0) && this->Size(0) >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() <= i)
		{
			((DataMatrix<Dims, Elem, Index, Container>*)this)->resize(i+1);
		}
		assert(data.at(i) != NULL);
		return data.at(i);
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::mul(const Elem n)
	{
		auto nc = Container<Subset>(this->Size(0));
		
		for (Index i = 0; i < this->Size(0); i++)
		{
			nc[i] = Subset(this->at(i)->mul(n));
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->Size(0)));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->size[i]);
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::mul(const tensor_t<Dims, Elem, Index> m)
	{
		for (auto i = 0; i < Dims; i++)
		{
		if (this->size[i] != m.size(i))
		{
			throw MatrixInvalidSizeException();
		}
		}
		
		
		auto nc = Container<Subset>(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i)->mul(m[i]);
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->size[0]));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::div(const Elem n)
	{
		auto nc = Container<Subset>(this->Size(0));
		
		for (Index i = 0; i < this->Size(0); i++)
		{
			nc[i] = Subset(this->at(i)->div(n));
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->Size(0)));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->size[i]);
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::div(const tensor_t<Dims, Elem, Index> m)
	{
		for (auto i = 0; i < Dims; i++)
		{
		if (this->size[i] != m.size(i))
		{
			throw MatrixInvalidSizeException();
		}
		}
		
		
		auto nc = Container<Subset>(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i)->div(m[i]);
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->size[0]));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
	
		
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::add(const tensor_t<Dims, Elem, Index> m)
	{
		for (auto i = 0; i < Dims; i++)
		{
		if (this->Size(i) != m.size(i))
		{
			throw MatrixInvalidSizeException();
		}
		}
		
		
		auto nc = Container<Subset>(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i)->add(m[i]);
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->size[0]));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
		
		
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::sub(const tensor_t<Dims, Elem, Index> m)
	{
		for (auto i = 0; i < Dims; i++)
		{
		if (this->Size(i) != m.size(i))
		{
			throw MatrixInvalidSizeException();
		}
		}
		
		
		auto nc = Container<Subset>(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i)->sub(m[i]);
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->size[0]));
		
		for (auto i = 0; i < Dims; i++)
		{
			ret->setSize(i, this->Size(i));
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			ret->data[i] = nc[i];
		}
		
		return tensor_t<Dims, Elem, Index>(ret);
	}
		
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::clone() const
	{
		//std::cout << "DataMatrix<" << Dims << ">::clone()" << std::endl;
		//std::cout << "data.size(): " << data.size() << std::endl;
		auto cl = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index, Container>((Index)data.size()));
		//std::cout << "cl created" << std::endl;
		for (int i = 0; i < Dims; i++)
		{
			//std::cout << "Setting Size for Dim " << i << "/" << (Dims-1) << " (" << std::flush << this->Size(i) << ")" << std::endl;
			cl->setSize(i, this->Size(i));
		}
		//std::cout << "Sizes set." << std::endl;
		
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			assert(data[i] != NULL);
			cl->data[i] = data[i]->clone();
		}
		return tensor_t<Dims, Elem, Index>(cl);
	}
	
	namespace _Helpers
	{
	template <int N, typename Elem, typename Index>
	struct DataMatrix_T_Setter
	{
		static void call(auto source, auto dest, std::function<Index(int)> count, int dim)
		{
			Index size = count(dim);
			for (Index i = 0; i < size; i++)
			{
				DataMatrix_T_Setter<N-1, Elem, Index>::call([&] (auto... args) -> Elem&
				{
					return source(i, args...);
				}, [&] (auto... args) -> Elem&
				{
					return dest(i, args...);
				}, count, dim+1);
			}
		}
	};
	
	template <typename Elem, typename Index>
	struct DataMatrix_T_Setter<1, Elem, Index>
	{
		static void call(auto source, auto dest, std::function<Index(int)> count, int dim)
		{
			Index size = count(dim);
			for (Index i = 0; i < size; i++)
			{
				dest(static_cast<Index>(i)) = source(static_cast<Index>(i));
			}
		}
	};
	
	template <int N, typename Ret, typename T, typename ...Args>
	struct DataMatrix_T_ArgGen : DataMatrix_T_ArgGen<N-1, Ret, T, T, Args...> 
	{ };
	
	template <typename Ret, typename T, typename ...Args>
	struct DataMatrix_T_ArgGen<0, Ret, T, Args...>
	{
		typedef std::function<Ret(Args...)> type;
	};
	
	template <typename Index>
	auto DataMatrix_T_Getter_Wrapper(auto& t, Index arg1)
	{
		return t(arg1);
	}
	
	template <typename Index, typename ...Args>
	auto DataMatrix_T_Getter_Wrapper(auto& t, Index arg1, Args... args)
	{
		return DataMatrix_T_Getter_Wrapper(t(arg1), args...);
	}
	
	
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::T() const
	{
		tensor_t<Dims, Elem, Index> M = new DataMatrix<Dims, Elem, Index, Container>();
		for (int i = 0; i < Dims; i++)
		{
			M.setSize(i, this->Size(Dims-i-1));
		}
		
		
		
		typename _Helpers::DataMatrix_T_ArgGen<Dims, Elem&, Index>::type access = [&] (auto... args) -> Elem& {
			static_assert(sizeof...(args) == Dims, "");
			return tensor_t<Dims, Elem, Index>(this->get_ptr())(args...);
		};
		
		auto revAccess = [access] (auto... args) -> Elem& {
			static_assert(sizeof...(args) == Dims, "");
			auto revTup = reverseTuple(args...);
			
			return call_tuple_args(access, revTup);
		};
		
		auto newAccess = [&] (auto... args) -> Elem& {
			static_assert(sizeof...(args) == Dims, "");
			return M(args...);
		};
		
		auto sizeFunc = [&] (int i) -> Index {
			return M.size(i);
		};
		
		_Helpers::DataMatrix_T_Setter<Dims, Elem, Index>::call(revAccess, newAccess, sizeFunc, 0);
		
		//throw NotImp();
		return M;
	}
	
	namespace _Helpers
	{
		template <template <typename...> typename Obj, int Count, typename T, typename... Args>
		struct RepObjectBuilder
		{
			typedef typename RepObjectBuilder<Obj, Count-1, T, T, Args...>::type type;
		};
		
		template <template <typename...> typename Obj, typename T, typename... Args>
		struct RepObjectBuilder<Obj, 0, T, Args...>
		{
			typedef Obj<Args...> type;
		};
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value args) const
	{
		for (int i = 0; i < Dims; i++)
		{
			auto s = this->Size(i);
			if (s == 1 || s == 0)
			{
				throw MatrixInvalidSizeException();
			}
		}
		
		tensor_t<Dims, Elem, Index> m = new DataMatrix<Dims, Elem, Index>();
		m.setSize(0, this->Size(0)-1);
		Index index = std::get<0>(args);
		
		
		auto nTup = typename _Helpers::RepObjectBuilder<Tuple, Dims, Index>::type(args);
		auto back = nTup.template takeBack<Dims-1>();
		
		auto count = this->Size(0);
		auto size2 = this->Size(1);
		Index i = 0;
		for (Index n = 0; n < count; n++)
		{
			if (n != index)
			{
				m(i) = ((*this)[n]).submatrix(back.getStd());
				m(i++).setSize(0, size2-1);
			}
		}
		return m;
	}
	
	namespace _Helpers
	{
	template <int Dims, typename Elem, typename Index>
	struct DataMatrix_Inv_Dims_Filter
	{
	static tensor_t<2, Elem, Index> call(const tensor_t<Dims, Elem, Index>&)
	{
		throw MatrixInvalidSizeException();
	}
	};
	
	template <typename Elem, typename Index>
	struct DataMatrix_Inv_Dims_Filter<2, Elem, Index>
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
			tensor_t<2, Elem, Index> tensor_this = tensor_t<2, Elem, Index>(((Matrix<2, Elem, Index>*)m.get())->get_ptr());
			return transpose.contract(tensor_this).inv().contract(transpose);
		}
		if (size1 == 1 && size2 == 1)
		{
			tensor_t<2, Elem, Index> oneRet = new DataMatrix<2, Elem, Index>();
			oneRet.setSize(0, 1);
			oneRet(0) = tensor_t<1, Elem, Index>({static_cast<Elem>(static_cast<Elem>(1)/(m[0][0]))});
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
		
		auto A = m->block(std::make_tuple(0, ASize, 0, ASize));
		auto B = m->block(std::make_tuple(0, ASize, ASize, size2));
		auto C = m->block(std::make_tuple(ASize, size1, 0, size2 - DSize));
		auto D = m->block(std::make_tuple(ASize, size1, size2-DSize, size2));
		
		
		
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
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<2, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::inv() const
	{
		assert(Dims == 2);
		return _Helpers::DataMatrix_Inv_Dims_Filter<Dims, Elem, Index>::call(this->get_ptr());
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::block(typename _Helpers::TupleBuilder<2*Dims, Index>::value tup) const
	{
		Index start = std::get<0>(tup);
		Index end = std::get<1>(tup);
		assert(end >= start);
		Index size = end - start;
		tensor_t<Dims, Elem, Index> m = new DataMatrix<Dims, Elem, Index, Container>();
		m.setSize(0, size);
		auto nTup = Make_Tuple(tup).template takeBack<2*Dims - 2>().getStd();
		for (Index i = start; i < end; i++)
		{
			m(i-start) = ((DataMatrix<Dims, Elem, Index, Container>*)this)->operator()(i).block(nTup);
			//m(i-start) = this->operator[](i).block(nTup);
		}
		return m;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<1, Elem, Index, Container>::DataMatrix(Data d) : Matrix<1, Elem, Index>(), data(d)
	{
		this->size[0] = _getSize(d);
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<1, Elem, Index, Container>::DataMatrix() : Matrix<1, Elem, Index>(), data()
	{
		this->size[0] = 0;
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<1, Elem, Index, Container>::resize(const Index s)
	{
		if (s != data.size())
		{
			data.resize(s);
		}
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<1, Elem, Index, Container>::setSize(const Index dim, const Index s)
	{
		//std::cout << "DataMatrix<" << 1 << ">::setSize(" << dim << ", " << s << ")" << std::endl;
		assert(s >= 0);
		if (dim >= 1 || dim < 0)
		{
			throw std::out_of_range("DataMatrix::set_size_check");
		}
		this->size[dim] = s;
		this->resize(s);
		//std::cout << "DataMatrix<1>::setSize() Returning..." << std::endl;
	}
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	Elem DataMatrix<1, Elem, Index, Container>::operator[](Index i) const
	{
		assert(i >= 0);
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() != this->size[0])
		{
			throw std::range_error("DataMatrix::inconsistent_internal_sizes");
		}
		return data.at(i);
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	Elem& DataMatrix<1, Elem, Index, Container>::operator()(Index i)
	{
		assert(i >= 0);
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (i >= data.size())
		{
			this->resize(i+1);
		}
		return data.at(i);
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	const Elem& DataMatrix<1, Elem, Index, Container>::operator()(Index i) const
	{
		assert(i >= 0);
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (i >= data.size())
		{
			((DataMatrix<1, Elem, Index, Container>*)this)->resize(i+1);
		}
		return data.at(i);
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::mul(const Elem n)
	{
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) * n;
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::mul(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] != m.size(0))
		{
			throw MatrixInvalidSizeException();
		}
		
		
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) * m[i];
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::div(const Elem n)
	{
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) / n;
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::div(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] != m.size(0))
		{
			throw MatrixInvalidSizeException();
		}
		
		
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) / m[i];
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
	
		
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::add(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] != m.size(0))
		{
			throw MatrixInvalidSizeException();
		}
		
		
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) + m[i];
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
		
		
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::sub(const tensor_t<1, Elem, Index> m)
	{
		if (this->size[0] != m.size(0))
		{
			throw MatrixInvalidSizeException();
		}
		
		
		auto nc = Data(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = this->at(i) - m[i];
		}
		
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(nc));
	}
		
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::clone() const
	{
		return tensor_t<1, Elem, Index>(std::make_shared<DataMatrix<1, Elem, Index, Container>>(data));
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<2, Elem, Index> DataMatrix<1, Elem, Index, Container>::T() const
	{
		Index size = this->Size(0);
		tensor_t<2, Elem, Index> M = new DataMatrix<2, Elem, Index, Container>();
		M.setSize(0, size);
		M.setSize(1, 1);
		
		for (Index i = 0; i < size; i++)
		{
			M(i, 0) = (*this)(i);
		}
		return M;
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::submatrix(std::tuple<Index> args) const
	{
		auto s = this->Size(0);
		if (s == 1 || s == 0)
		{
			throw MatrixInvalidSizeException();
		}
		
		
		
		tensor_t<1, Elem, Index> m = new DataMatrix<1, Elem, Index>();
		m.setSize(0, this->Size(0)-1);
		Index index = std::get<0>(args);
		
		Index i = 0;
		for (Index n = 0; n < s; n++)
		{
			if (n != index)
			{
				m(i++) = (*this)[n];
			}
		}
		return m;
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<1, Elem, Index, Container>::append(Elem value)
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<2, Elem, Index> DataMatrix<1, Elem, Index, Container>::inv() const
	{
		auto transpose = T();
		tensor_t<1, Elem, Index> tensor_this = tensor_t<1, Elem, Index>(((DataMatrix<1, Elem, Index, Container>*)this)->get_ptr());
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
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::block(typename _Helpers::TupleBuilder<2, Index>::value tup) const
	{
		tensor_t<1, Elem, Index> m = new DataMatrix<1, Elem, Index, Container>();
		
		Index start = std::get<0>(tup);
		Index end = std::get<1>(tup);
		assert(end >= start);
		
		m->setSize(0, end-start);
		Index mIndex = 0;
		for (Index i = start; i < end; i++)
		{
			m(mIndex++) = (*this)[i];
		}
		return m;
	}
	
	
}
}