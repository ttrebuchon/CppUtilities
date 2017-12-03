#pragma once
#include "../IIterable_Ptr.h"

namespace QUtils { namespace Iterable { namespace Internal {
	
	template <class T, class G>
	class SharedPtr_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;
		
		
		private:
		
		protected:
		std::shared_ptr<G> ptr;
		
		
		public:
		
		SharedPtr_IIterable_Ptr(std::shared_ptr<G> ptr) : ptr(ptr)
		{}
		
		virtual iterator begin() override
		{
			return ptr->begin();
		}
		
		virtual iterator end() override
		{
			return ptr->end();
		}
		
		virtual const_iterator cbegin() const override
		{
			/*static_assert(std::is_same<typename G::const_iterator, void>::value, "");
			typedef decltype(ref.begin()) F;
			static_assert(std::is_same<F, void>::value, "");*/
			return ptr->begin();
		}
		
		virtual const_iterator cend() const override
		{
			return ptr->end();
		}
		
		virtual std::unique_ptr<IIterable_Ptr<T>> reference() const override
		{
			return std::make_unique<SharedPtr_IIterable_Ptr<T, G>>(ptr);
		}
	};
}
}
}