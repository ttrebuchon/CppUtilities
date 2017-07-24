#pragma once

#include <QUtils/Types/TypeSequence.h>

namespace QUtils
{
namespace Multi
{
	template <class A, class ...B>
	class Result : public Types::TemplateFromTupleTypes<Result, typename Types::ExcludeLastN<1, A, B...>::type>::type
	{
		typedef typename Types::TemplateFromTupleTypes<Result, typename Types::ExcludeLastN<1, A, B...>::type>::type Base;
		typedef typename Types::ExcludeLastN<1, A, B...>::type OthersTuple;
		typedef typename Types::LastType<B...>::type InnerType;
		private:
		InnerType result;
		
		
		public:
		Result() : Base(), result()
		{}
		
		
		
		typename std::remove_reference<InnerType>::type& get()
		{
			return result;
		}
		
		typename std::remove_reference<InnerType>::type& get() const
		{
			return result;
		}
	};
	
	template <class A>
	class Result<A>
	{
		private:
		A result;
		
		
		public:
		Result(A a) :result(a)
		{}
		Result() : result()
		{}
		
		typename std::remove_reference<A>::type& get()
		{
			return result;
		}
		
		typename std::remove_reference<A>::type& get() const
		{
			return result;
		}
	};
	
	template <>
	class Result<void>
	{
		private:
		
		
		public:
		Result(void)
		{}
		
	};
	
	namespace Helpers
	{
		template <int, class...>
		struct CasterHelper
		{
			
		};
		
		
		template <int N, class A, class... B>
		struct CasterHelper<N, Result<A, B...>>
		{
			private:
			
			typedef typename Types::TemplateFromTupleTypes<Result, typename Types::ExcludeLastN<1, A, B...>::type>::type Base;
			
			
			public:
			
			static auto& get(Result<A, B...>& res)
			{
				auto& r = (Base&)res;
				return CasterHelper<N-1, Base>::get(r);
			}
		};
		
		template <class... A>
		struct CasterHelper<0, Result<A...>>
		{
			private:
			
			
			public:
			
			static auto& get(Result<A...>& res)
			{
				return res;
			}
		};
		
		template <class A, class... B>
		struct CasterHelper<0, Result<A, B...>>
		{
			private:
			
			
			public:
			
			static auto& get(Result<A, B...>& res)
			{
				return res;
			}
		};
		
		template <class T>
		struct RemoveRef
		{
			typedef T type;
		};
		
		template <class T>
		struct RemoveRef<T&>
		{
			typedef T type;
		};
	}
	template <int N>
	auto& result_cast(auto& res)
	{
		typedef decltype(res) R;
		return Helpers::CasterHelper<N, typename Helpers::RemoveRef<R>::type>::get(res);
	}
}
}