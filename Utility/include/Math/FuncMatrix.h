#pragma once

#include <functional>
#include "Matrix.h"
#include "FuncArgHelper.h"
#include <memory>
#include <map>


namespace Util
{
namespace Math
{
	
	
	
	template <int Dims, typename Elem, typename Index = int>
	class FuncMatrix : public Matrix<Dims, Elem, Index>
	{
		private:
		
		//std::function<Elem(Index...)>
		//where there are "Dims" number
		//of Index arguments
		typedef typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type Func; 
		
		Func def;
		std::map<Index, std::shared_ptr<Matrix<Dims-1, Elem, Index>>> instantiated;
		
		protected:
		
		
		
		public:
		
		FuncMatrix(Func f);
		FuncMatrix(const FuncMatrix&);
		
		virtual std::string imp() const override { return "FuncMatrix"; }
		
		std::shared_ptr<Matrix<Dims-1, Elem, Index>> operator[](Index i) const override;
		Matrix<Dims-1, Elem, Index>& operator()(Index i) override;
		
		
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> mul(const double) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> mul(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> add(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> sub(const Matrix<Dims, Elem, Index>&) override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> clone() const override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> T() const override;
		virtual std::shared_ptr<Matrix<Dims, Elem, Index>> submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		//virtual Elem minor(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		
	};
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class FuncMatrix<1, Elem, Index> : public Matrix<1, Elem, Index>
	{
		private:
		
		typedef std::function<Elem(Index)> Func; 

		Func def;
		std::map<Index, Elem> instantiated;
		
		protected:
		
		
		
		public:
		
		FuncMatrix(Func f);
		FuncMatrix(const FuncMatrix&);
		//FuncMatrix(std::shared_ptr<FuncMatrix>);
		
		virtual std::string imp() const override { return "FuncMatrix"; }
		
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

#include "FuncMatrix.hpp"