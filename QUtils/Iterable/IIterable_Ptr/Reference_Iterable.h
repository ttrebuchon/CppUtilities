#pragma once
#include "../IIterable_Ptr.h"

namespace QUtils { namespace Iterable { namespace Internal {
	
	template <class T, class G>
	class Reference_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		typedef Iterator<const T> const_iterator;
		
		
		private:
		
		protected:
		G& ref;
		
		
		public:
		
		Reference_IIterable_Ptr(G& obj) : ref(obj)
		{}
		
		virtual iterator begin() override
		{
			return ref.begin();
		}
		
		virtual iterator end() override
		{
			return ref.end();
		}
		
		virtual const_iterator cbegin() const override
		{
			/*static_assert(std::is_same<typename G::const_iterator, void>::value, "");
			typedef decltype(ref.begin()) F;
			static_assert(std::is_same<F, void>::value, "");*/
			return ref.begin();
		}
		
		virtual const_iterator cend() const override
		{
			return ref.end();
		}
		
		virtual std::unique_ptr<IIterable_Ptr<T>> reference() const override
		{
			return std::make_unique<Reference_IIterable_Ptr<T, G>>(ref);
		}
	};
}
}
}