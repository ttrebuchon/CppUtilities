#pragma once
#include "../IIterable_Ptr.h"

namespace QUtils { namespace Iterable { namespace Internal {
	
	template <class T, class G>
	class Reference_IIterable_Ptr : public IIterable_Ptr<T>
	{
		public:
		typedef Iterator<T> iterator;
		
		
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
	};
}
}
}