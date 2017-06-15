#pragma once

#include <functional>

namespace Util
{
	template <typename T>
	class LazyLoad
	{
		private:
		T* ent;
		
		std::function<T*()> constructor;
		
		void init()
		{
			ent = new T();
		}
		
		inline T* get()
		{
			if (ent == nullptr)
			{
				init();
			}
			return ent;
		}
		
		protected:
		
		public:
		template <typename ...Args>
		LazyLoad(Args... args) : ent(nullptr), constructor([args...]() { return new T(args...); }) {}
		~LazyLoad() {
			if (ent != nullptr) delete ent;
		}
		
		T& v()
		{
			return *ent;
		}
		
		operator T&()
		{
			return *get();
		}
		
		LazyLoad<T>& operator=(const T& t)
		{
			*get() = t;
			return *this;
		}
		
		T& operator->()
		{
			return *get();
		}
		
		template <typename R>
		bool operator==(const R& r)
		{
			return (*get() == r);
		}
		
		template <typename R>
		bool operator!=(const R& r)
		{
			return (*get() != r);
		}
		
		template <typename A>
		LazyLoad<T>& operator=(const A& a)
		{
			*get() = a;
			return *this;
		}
		
		template <typename G>
		auto operator+(const G& g) -> decltype(*get() + g)
		{
			return (*get() + g);
		}
		
		template <typename G>
		auto operator-(const G& g) -> decltype(*get() - g)
		{
			return (*get() - g);
		}
		
		
		
	};
	
	template <typename V, typename H>
	auto operator<<(V& v, LazyLoad<H>& h) -> decltype( v << h.v())
	{
		return (v << h.v());
	}
	
	template <typename V, typename H>
	auto operator+(V& v, LazyLoad<H>& h) -> decltype( v + h.v())
	{
		return (v + h.v());
	}
	
	template <typename V, typename H>
	auto operator-(V& v, LazyLoad<H>& h) -> decltype( v - h.v())
	{
		return (v - h.v());
	}
	
	template <typename V, typename H>
	auto operator/(V& v, LazyLoad<H>& h) -> decltype( v / h.v())
	{
		return (v / h.v());
	}
	
	template <typename V, typename H>
	auto operator*(V& v, LazyLoad<H>& h) -> decltype( v * h.v())
	{
		return (v * h.v());
	}
	
	template <typename V, typename H>
	auto operator==(V& v, LazyLoad<H>& h) -> decltype( v == h.v())
	{
		return (v == h.v());
	}
	
	
	
	
	
	
	
	
	
	
	
	template <typename T>
	class LazyLoad<T*>
	{
		private:
		T* ent;
		bool inited;
		
		std::function<T*()> constructor;
		
		void init()
		{
			if (!inited)
			{
				ent = constructor();
				inited = true;
			}
		}
		
		inline T*& get()
		{
			if (ent == nullptr)
			{
				init();
			}
			return ent;
		}
		
		protected:
		
		
		public:
		template <typename ...Args>
		LazyLoad(Args... args) : ent(nullptr), inited(false), constructor([args...]() { return new T(args...); }) { }
		
		void free() {
			if (inited)
			{
				delete ent;
			}
		}
		
		T*& v()
		{
			return get();
		}
		
		T* operator->()
		{
			return get();
		}
		
		T& operator*()
		{
			return *get();
		}
		
		operator T*()
		{
			return get();
		}
		
		template <typename H>
		LazyLoad<T*>& operator=(const H h)
		{
			ent = h;
			return *this;
		}
		
		template <typename H>
		auto operator+(const H h) -> decltype(ent + h)
		{
			return (get() + h);
		}
	};
	
	template <typename V, typename H>
	auto operator<<(V& v, LazyLoad<H*>& h) -> decltype( v << h.v())
	{
		return (v << h.v());
	}
	
	template <typename V, typename H>
	auto operator+(V& v, LazyLoad<H*>& h) -> decltype( v + h.v())
	{
		return (v + h.v());
	}
	
	template <typename V, typename H>
	auto operator-(V& v, LazyLoad<H*>& h) -> decltype( v - h.v())
	{
		return (v - h.v());
	}
	
	template <typename V, typename H>
	auto operator/(V& v, LazyLoad<H*>& h) -> decltype( v / h.v())
	{
		return (v / h.v());
	}
	
	template <typename V, typename H>
	auto operator*(V& v, LazyLoad<H*>& h) -> decltype( v * h.v())
	{
		return (v * h.v());
	}
	
	template <typename V, typename H>
	auto operator==(V& v, LazyLoad<H*>& h) -> decltype( v == h.v())
	{
		return (v == h.v());
	}
	
	
	
}