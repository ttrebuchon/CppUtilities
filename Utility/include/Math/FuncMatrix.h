#pragma once

#include <functional>
#include "Matrix.h"
#include "FuncArgHelper.h"


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
		
		protected:
		
		
		
		public:
		
		FuncMatrix(Func f);
		
		virtual std::string imp() const override { return "FuncMatrix"; }
		
		Matrix<Dims-1, Elem, Index>* operator[](Index i) const override;
		
		
		virtual Matrix<Dims, Elem, Index>* mul(const double) override;
		virtual Matrix<Dims, Elem, Index>* mul(const Matrix<Dims, Elem, Index>&) override;
		virtual Matrix<Dims, Elem, Index>* add(const Matrix<Dims, Elem, Index>&) override;
		virtual Matrix<Dims, Elem, Index>* sub(const Matrix<Dims, Elem, Index>&) override;
		virtual Matrix<Dims, Elem, Index>* clone() const override;
		virtual Matrix<Dims, Elem, Index>* T() const override;
		virtual Matrix<Dims, Elem, Index>* submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		//virtual Elem minor(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		
	};
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class FuncMatrix<1, Elem, Index> : public Matrix<1, Elem, Index>
	{
		private:
		
		std::function<Elem(Index)> def;
		
		protected:
		
		
		
		public:
		
		FuncMatrix(std::function<Elem(Index)> f);
		virtual std::string imp() const override { return "FuncMatrix"; }
		
		Elem operator[](Index i) const override;
		
		
		virtual Matrix<1, Elem, Index>* mul(const double) override;
		virtual Matrix<1, Elem, Index>* mul(const Matrix<1, Elem, Index>&) override;
		virtual Matrix<1, Elem, Index>* add(const Matrix<1, Elem, Index>&) override;
		virtual Matrix<1, Elem, Index>* sub(const Matrix<1, Elem, Index>&) override;
		virtual Matrix<1, Elem, Index>* clone() const override;
		
		virtual Matrix<2, Elem, Index>* T() const override;
		virtual Matrix<1, Elem, Index>* submatrix(std::tuple<Index>) const override;
		
	};
	
	
}
}

#include "FuncMatrix.hpp"