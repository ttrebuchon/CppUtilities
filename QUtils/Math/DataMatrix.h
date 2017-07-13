#pragma once

#include "Matrix.h"
#include "FuncMatrix.h"

#include <vector>

namespace QUtils
{
namespace Math
{
	namespace _Helpers
	{
		template <int n, typename T, template <typename...> typename Container>
		struct RecursiveDataMatrix
		{
			typedef Container<typename RecursiveDataMatrix<n-1, T, Container>::type> type;
		};
		
		template <typename T, template <typename...> typename Container>
		struct RecursiveDataMatrix<0, T, Container>
		{
			typedef T type;
		};
	}
	
	
	
	
	
	
	
	template <typename Container>
	int _getSize(Container&);
	
	
	
	template <int Dims, typename Elem, typename Index = int, template <typename...> typename Container = std::vector>
	class DataMatrix : public Matrix<Dims, Elem, Index>
	{
		private:
		
		protected:
		
		typedef typename _Helpers::RecursiveDataMatrix<Dims, Elem, Container>::type Data;
		
		typedef tensor_t<Dims-1, Elem, Index> Subset;
		
		Container<Subset> data;
		
		DataMatrix(Index);
		
		public:
		template <typename DataSet>
		DataMatrix(DataSet);
		DataMatrix(Data);
		DataMatrix();
		virtual ~DataMatrix() { }
		
		virtual std::string imp() const override { return "DataMatrix"; }
		
		virtual void resize(const Index s) override;
		
		virtual void setSize(const Index dim, const Index s) override;
		
		tensor_t<Dims-1, Elem, Index> operator[](Index i) const override;
		tensor_t<Dims-1, Elem, Index>& operator()(Index i) override;
		const tensor_t<Dims-1, Elem, Index>& operator()(Index i) const override;
		
		
		virtual tensor_t<Dims, Elem, Index> mul(const Elem) override;
		virtual tensor_t<Dims, Elem, Index> mul(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> div(const Elem) override;
		virtual tensor_t<Dims, Elem, Index> div(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> add(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> sub(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> clone() const override;
		virtual tensor_t<Dims, Elem, Index> T() const override;
		virtual tensor_t<Dims, Elem, Index> submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		virtual tensor_t<2, Elem, Index> inv() const override;
		virtual tensor_t<Dims, Elem, Index> block(typename _Helpers::TupleBuilder<2*Dims, Index>::value) const override;
		virtual tensor_t<Dims, Elem, Index> toDataTensor() const override { return clone(); }
		
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename Elem, typename Index, template <typename...> typename Container>
	class DataMatrix<1, Elem, Index, Container> : public Matrix<1, Elem, Index>
	{
		private:
		
		protected:
		typedef typename _Helpers::RecursiveDataMatrix<1, Elem, Container>::type Data;
		
		Data data;
		
		public:
		DataMatrix(Data);
		DataMatrix();
		
		virtual std::string imp() const override { return "DataMatrix"; }
		
		virtual void resize(const Index s) override;
		
		virtual void setSize(const Index dim, const Index s) override;
		
		Elem operator[](Index i) const override;
		Elem& operator()(Index i) override;
		const Elem& operator()(Index i) const override;
		
		
		virtual tensor_t<1, Elem, Index> mul(const Elem) override;
		virtual tensor_t<1, Elem, Index> mul(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> div(const Elem) override;
		virtual tensor_t<1, Elem, Index> div(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> add(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> sub(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> clone() const override;
		
		virtual tensor_t<2, Elem, Index> T() const override;
		virtual tensor_t<1, Elem, Index> submatrix(std::tuple<Index>) const override;
		virtual void append(Elem value) override;
		virtual tensor_t<2, Elem, Index> inv() const override;
		virtual tensor_t<1, Elem, Index> block(typename _Helpers::TupleBuilder<2, Index>::value) const override;
		virtual tensor_t<1, Elem, Index> toDataTensor() const override { return clone(); }
		
	};
}
}

//#include "DataMatrix.hpp"