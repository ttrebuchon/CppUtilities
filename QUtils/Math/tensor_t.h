#pragma once
#include "FuncArgHelper.h"
#include "tensor_t_helpers.hpp"
#include <memory>
#include <type_traits>
#include <assert.h>
#include <initializer_list>

namespace Util
{
namespace Math
{
	template <int Dims, typename Elem, typename Index>
	class Matrix;
	
	
	
	template <int Dims, typename Elem, typename Index = int>
	class tensor_t : public std::shared_ptr<Matrix<Dims, Elem, Index>>
	{
		private:
		typedef std::shared_ptr<Matrix<Dims, Elem, Index>> Shared;
		typedef std::shared_ptr<const Matrix<Dims, Elem, Index>> Shared_c;
		
		typedef
		    typename std::conditional<Dims==1, Elem, tensor_t<Dims-1, Elem, Index>>::type
		    type;
		
		template <int Args>
		using RetType = typename _Helpers::_tensor_t::MultiIndexRetType<tensor_t, Dims, Elem, Index, Args>::type;
		
		protected:
		
		//Internal Functions
		inline tensor_t& ptr();
		inline const tensor_t& ptr() const;
		inline Matrix<Dims, Elem, Index>& obj();
		inline const Matrix<Dims, Elem, Index>& obj() const;
		
		public:
		tensor_t() : Shared() {}
		tensor_t(const Shared_c ptr) : Shared(
			(ptr != NULL) ? ((Matrix<Dims, Elem, Index>*)ptr.get())->get_ptr() : NULL
		) {}
		tensor_t(Matrix<Dims, Elem, Index>* ptr) : Shared(ptr->get_ptr()) {}
		tensor_t(const std::initializer_list<type>);

		template <template <int, typename...> typename T>
		tensor_t(const std::shared_ptr<T<Dims, Elem, Index>> ptr) : Shared(ptr) {}

		tensor_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f
		);
		
		template <typename... Size>
		tensor_t(
		typename _Helpers::FuncArgHelper<Dims, Index, Elem>::type f, Size... sizes
		);

		virtual ~tensor_t();



		
		//Assignment Operators
		tensor_t& operator=(const Elem);
		tensor_t& operator=(const Shared ptr);
		
		//Arithmetic Operators
		tensor_t operator+(const tensor_t) const;
		tensor_t operator-(const tensor_t) const;
		tensor_t operator*(const tensor_t) const;
		tensor_t operator/(const tensor_t) const;
		tensor_t operator*(const Elem) const;
		tensor_t operator/(const Elem) const;
		
		
		//Arithmetic Assignment Operators
		tensor_t& operator+=(const tensor_t);
		tensor_t& operator-=(const tensor_t);
		tensor_t& operator*=(const tensor_t);
		tensor_t& operator/=(const tensor_t);
		tensor_t& operator*=(const Elem);
		tensor_t& operator/=(const Elem);


		//Comparison Operators
		template <typename Elem2>
		bool operator==(const tensor_t<Dims, Elem2, Index>) const;
		
		
		//Member Functions
		Index size(const int dim) const;
		void setSize(const int dim, const Index size);
		void setSize(const Index size) { setSize(0, size); }
		std::string toString() const;
		std::string imp() const;
		int order() const { return Dims; }
		Elem det() const;
		tensor_t<2, Elem, Index> inv() const;

		template <int Dims2>
		tensor_t<Dims+Dims2-2, Elem, Index> contract(const tensor_t<Dims2, Elem, Index>);

		template <typename... Args>
		tensor_t submatrix(Args... args) const;
		
		template <typename... Args>
		tensor_t submatrix(std::tuple<Args...> args) const;
		
		tensor_t<_Helpers::_tensor_t::transposeDims(Dims), Elem, Index> T() const;
		
		template <typename... Args>
		tensor_t<Dims, Elem, Index> block(Args...) const;
		
		tensor_t<Dims, Elem, Index> toDataTensor() const;
		
		
		//Accessors
		type& operator()(const Index);
		
		template <class... Args>
		RetType<sizeof...(Args)>& operator()(const Args... args);
		
		const type& operator()(const Index) const;
		
		template <class... Args>
		const RetType<sizeof...(Args)>& operator()(const Args... args) const;
		  
		type operator[](const Index) const;
		
		
	};
	
}
}

#include "tensor_t.hpp"