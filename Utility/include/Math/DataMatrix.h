#pragma once

#include "Matrix.h"
#include "FuncMatrix.h"

#include <vector>

namespace Util
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
		
		typedef Matrix<Dims-1, Elem, Index> Subset;
		
		Container<std::shared_ptr<Subset>> data;
		
		DataMatrix(Index);
		
		public:
		template <typename DataSet>
		DataMatrix(DataSet);
		DataMatrix(Data);
		virtual ~DataMatrix() { }
		
		virtual std::string imp() const override { return "DataMatrix"; }
		
		std::shared_ptr<Matrix<Dims-1, Elem, Index>> operator[](Index i) const override;
		Matrix<Dims-1, Elem, Index>& operator()(Index i) override;
		
		
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> mul(const double) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> mul(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> add(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> sub(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> clone() const override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> T() const override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		
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
		
		virtual std::string imp() const override { return "DataMatrix"; }
		
		Elem operator[](Index i) const override;
		Elem& operator()(Index i) override;
		
		
		virtual std::shared_ptr<Matrix<1, Elem, Index>> mul(const double) override;
		virtual std::shared_ptr<Matrix<1, Elem, Index>> mul(const Matrix<1, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<1, Elem, Index>> add(const Matrix<1, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<1, Elem, Index>> sub(const Matrix<1, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<1, Elem, Index>> clone() const override;
		
		virtual std::shared_ptr<Matrix<2, Elem, Index>> T() const override;
		virtual std::shared_ptr<Matrix<1, Elem, Index>> submatrix(std::tuple<Index>) const override;
		virtual void append(Elem value) override;
		
	};
}
}

#include "DataMatrix.hpp"