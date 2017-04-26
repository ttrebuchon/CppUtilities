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
		
		typedef typename FuncArgHelper<Dims, Index, Elem>::type Func; 
		
		Func def;
		
		protected:
		
		public:
		
		FuncMatrix(Func f);
		
		Matrix<Dims-1, Elem, Index>* operator[](Index i) override;
		
		
		virtual std::string toString() const override;
		virtual Matrix<Dims, Elem, Index>* mul(const double) override;
		virtual Matrix<Dims, Elem, Index>* add(const Matrix<Dims, Elem, Index>&) override;
		virtual Matrix<Dims, Elem, Index>* sub(const Matrix<Dims, Elem, Index>&) override;
		virtual Matrix<Dims, Elem, Index>* clone() const override;
		
	};
	
	
	
	
	
	
	
	template <typename Elem, typename Index>
	class FuncMatrix<1, Elem, Index> : public Matrix<1, Elem, Index>
	{
		private:
		
		std::function<Elem(Index)> def;
		
		protected:
		
		public:
		
		FuncMatrix(std::function<Elem(Index)> f);
		Elem operator[](Index i) override;
		
		
		virtual std::string toString() const override;
		virtual Matrix<1, Elem, Index>* mul(const double) override;
		virtual Matrix<1, Elem, Index>* add(const Matrix<1, Elem, Index>&) override;
		virtual Matrix<1, Elem, Index>* sub(const Matrix<1, Elem, Index>&) override;
		virtual Matrix<1, Elem, Index>* clone() const override;
	};
	
	
}
}

#include "FuncMatrix.hpp"