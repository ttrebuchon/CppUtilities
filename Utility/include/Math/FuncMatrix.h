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
		std::map<Index, tensor_t<Dims-1, Elem, Index>> instantiated;
		
		protected:
		
		
		
		public:
		
		FuncMatrix(Func f);
		FuncMatrix(const FuncMatrix&);
		template <typename... Size>
		FuncMatrix(Func f, Index s1, Size...);
		
		virtual std::string imp() const override { return "FuncMatrix"; }
		
		virtual void resize(const Index s) override {};
		
		virtual void setSize(const Index dim, const Index s) override;
		
		tensor_t<Dims-1, Elem, Index> operator[](Index i) const override;
		tensor_t<Dims-1, Elem, Index>& operator()(Index i) override;
		const tensor_t<Dims-1, Elem, Index>& operator()(Index i) const override;
		
		
		virtual tensor_t<Dims, Elem, Index> mul(const double) override;
		virtual tensor_t<Dims, Elem, Index> mul(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> add(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> sub(const tensor_t<Dims, Elem, Index>) override;
		virtual tensor_t<Dims, Elem, Index> clone() const override;
		virtual tensor_t<Dims, Elem, Index> T() const override;
		virtual tensor_t<Dims, Elem, Index> submatrix(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		//virtual Elem minor(typename _Helpers::TupleBuilder<Dims, Index>::value) const override;
		virtual tensor_t<2, Elem, Index> inv() const override;
		virtual tensor_t<Dims, Elem, Index> block(typename _Helpers::TupleBuilder<2*Dims, Index>::value) const override;
		virtual tensor_t<Dims, Elem, Index> toDataTensor() const override;
		
		void flattenOverrides();
		
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
		FuncMatrix(Func f, Index size);
		//FuncMatrix(std::shared_ptr<FuncMatrix>);
		
		virtual std::string imp() const override { return "FuncMatrix"; }
		
		virtual void resize(const Index s) override {};
		
		virtual void setSize(const Index dim, const Index s) override;
		
		
		Elem operator[](Index i) const override;
		Elem& operator()(Index i) override;
		const Elem& operator()(Index i) const override;
		
		
		virtual tensor_t<1, Elem, Index> mul(const double) override;
		virtual tensor_t<1, Elem, Index> mul(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> add(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> sub(const tensor_t<1, Elem, Index>) override;
		virtual tensor_t<1, Elem, Index> clone() const override;
		
		virtual tensor_t<2, Elem, Index> T() const override;
		virtual tensor_t<1, Elem, Index> submatrix(std::tuple<Index>) const override;
		virtual void append(Elem value) override;
		virtual tensor_t<2, Elem, Index> inv() const override;
		virtual tensor_t<1, Elem, Index> block(typename _Helpers::TupleBuilder<2, Index>::value) const override;
		virtual tensor_t<1, Elem, Index> toDataTensor() const override;
		
		void flattenOverrides();
	};
	
	
}
}

#include "FuncMatrix.hpp"