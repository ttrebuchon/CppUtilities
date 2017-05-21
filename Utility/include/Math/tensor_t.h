#pragma once
#include "FuncArgHelper.h"
#include "tensor_t_helpers.hpp"
#include <memory>
#include <type_traits>
#include <assert.h>

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
		tensor_t(const Shared ptr) : Shared(ptr) {}
		/*tensor_t(const Shared&& ptr) : Shared(ptr) {}*/
		template <template <int, typename...> typename T>
		tensor_t(const std::shared_ptr<T<Dims, Elem, Index>> ptr) : Shared(ptr) {}
		virtual ~tensor_t();
		
		//Assignment Operators
		tensor_t& operator=(const Elem);
		tensor_t& operator=(const Shared ptr);
		//tensor_t& operator=(const Shared&& ptr);
		
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
		
		
		//Member Functions
		Index size(const int dim) const;
		std::string toString() const;
		std::string imp() const;
		
		
		//Accessors
		type& operator()(const Index);
		
		template <class... Args>
		RetType<sizeof...(Args)>& operator()(const Args... args);
		
		const type& operator()(const Index) const;
		
		template <class... Args>
		const RetType<sizeof...(Args)>& operator()(const Args... args) const;
		  
		type operator[](const Index) const;
		
		
		
		
		std::function<int()> s = [&]() { return this->use_count(); };
		
		
	};
	
}
}

#include "tensor_t.hpp"