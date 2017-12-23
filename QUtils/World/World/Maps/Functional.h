#pragma once

#include <functional>
#include "../Map.h"

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace World {
namespace Maps {
	
	template <class T>
	class FunctionalMap : public Map<T>
	{
		public:
		using typename Map<T>::Vec_t;
		
		
		
		
		private:
		
		protected:
		typedef std::function<Vec_t(T, T, T*, T*)> Func_t;
		Func_t grad;
		
		public:
		typedef std::shared_ptr<FunctionalMap<T>> Ptr;
		
		template <class F>
		static Ptr Create(F func)
		{
			auto ptr = Ptr(new FunctionalMap<T>);
			ptr->grad = Func_t(func);
			return ptr;
		}
		
		static Ptr Create(const Func_t func)
		{
			auto ptr = Ptr(new FunctionalMap<T>);
			ptr->grad = func;
			return ptr;
		}
		
		
		virtual bool hits(const Vec_t& bsse, const Vec_t& dir, Vec_t* result) const override
		{
			throw NotImp();
		}
		
		virtual T slant(const Vec_t& pos, const Vec_t& dir) const override
		{
			auto g = grad(pos.x, pos.y, NULL, NULL);
			g.z = 0;
			return g.dot(Vec_t{dir.x, dir.y, 0}.unit());
			return grad(pos.x, pos.y, NULL, NULL).z*dir.unit().z;
		}
	};
	
}
}
}