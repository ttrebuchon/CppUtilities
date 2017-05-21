#pragma once

#include "DataMatrix.h"
#include <Exception/NotImplemented.h>

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
		
	}
	
	
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<Dims, Elem, Index, Container>::DataMatrix(Data d) : Matrix<Dims, Elem, Index>(), data(d.size())
	{
		auto i = 0;
		for (auto subD : d)
		{
			data[i++] = std::make_shared<DataMatrix<Dims-1, Elem, Index, Container>>(subD);
		}
		
		this->size[0] = d.size();
		for (int n = 1; n < Dims; n++)
		{
			this->size[n] = data[0]->size[n-1];
		}
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	DataMatrix<Dims, Elem, Index, Container>::DataMatrix() : Matrix<Dims, Elem, Index>(), data()
	{
		for (int i = 0; i < Dims; i++)
		{
			this->size[i] = 0;
		}
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<Dims, Elem, Index, Container>::resize(const Index s)
	{
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
				data[i] = std::make_shared<DataMatrix<Dims-1, Elem, Index, Container>>();
				for (int j = 1; j < Dims; j++)
				{
					data[i]->setSize(j-1, this->size[j]);
				}
			}
		}
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<Dims, Elem, Index, Container>::setSize(const Index dim, const Index s)
	{
		if (dim >= Dims || dim < 0)
		{
			throw std::out_of_range("FuncMatrix::set_size_check");
		}
		this->size[dim] = s;
		if (dim > 0)
		{
			for (auto ptr : data)
			{
				ptr->setSize((const Index)(dim-1), (const Index)s);
			}
		}
		else
		{
			this->resize(s);
		}
	}
	
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims-1, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::operator[](Index i) const
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() != this->size[0])
		{
			throw std::range_error("DataMatrix::inconsistent_internal_sizes");
		}
		assert(data[i] != NULL);
		return data[i]->clone();
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims-1, Elem, Index>& DataMatrix<Dims, Elem, Index, Container>::operator()(Index i)
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() <= i)
		{
			this->resize(i+1);
		}
		assert(data[i] != NULL);
		return data[i];
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::mul(const double n)
	{
		auto nc = Container<Subset>(this->size[0]);
		
		for (Index i = 0; i < this->size[0]; i++)
		{
			nc[i] = Subset(this->at(i)->mul(n));
		}
		
		auto ret = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index>(this->size[0]));
		
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
			ret->size[i] = this->size[i];
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
		if (this->size[i] != m.size(i))
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
			ret->size[i] = this->size[i];
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
		if (this->size[i] != m.size(i))
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
			ret->size[i] = this->size[i];
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
		auto cl = std::shared_ptr<DataMatrix<Dims, Elem, Index, Container>>(new DataMatrix<Dims, Elem, Index, Container>((Index)data.size()));
		for (int i = 0; i < Dims; i++)
		{
			cl->size[i] = this->size[i];
		}
		
		for (auto i = 0; i < this->size[0]; i++)
		{
			cl->data[i] = data[i]->clone();
		}
		return tensor_t<Dims, Elem, Index>(cl);
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::T() const
	{
		throw NotImp();
	}
	
	template <int Dims, typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<Dims, Elem, Index> DataMatrix<Dims, Elem, Index, Container>::submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const
	{
		throw NotImp();
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
		if (dim >= 1 || dim < 0)
		{
			throw std::out_of_range("FuncMatrix::set_size_check");
		}
		this->size[dim] = s;
		this->resize(s);
	}
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	Elem DataMatrix<1, Elem, Index, Container>::operator[](Index i) const
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (data.size() != this->size[0])
		{
			throw std::range_error("DataMatrix::inconsistent_internal_sizes");
		}
		return data[i];
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	Elem& DataMatrix<1, Elem, Index, Container>::operator()(Index i)
	{
		if (i >= this->size[0] && this->size[0] >= 0)
		{
			throw std::out_of_range("DataMatrix::size_check");
		}
		if (i >= data.size())
		{
			this->resize(i+1);
		}
		return data[i];
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::mul(const double n)
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
		throw NotImp();
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	tensor_t<1, Elem, Index> DataMatrix<1, Elem, Index, Container>::submatrix(std::tuple<Index>) const
	{
		throw NotImp();
	}
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	void DataMatrix<1, Elem, Index, Container>::append(Elem value)
	{
		throw NotImp();
	}
	
	
}
}