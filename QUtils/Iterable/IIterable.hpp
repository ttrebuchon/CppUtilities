#pragma once
#include "IIterable.h"

namespace QUtils { namespace Iterable {
	
	
	
	namespace Meta { namespace OfType {
		
		template <class T, class G>
		struct Helper
		{
			static IIterable<G> call(const IIterable<T>* const it)
			{
				return it->select([](auto x) -> G
				{
					return static_cast<G>(x);
				});
			}
		};
		
		template <class T, class G>
		struct Helper<T*, G*>
		{
			static IIterable<G*> call(const IIterable<T*>* const it)
			{
				return it->select([](auto x) -> G*
				{
					return dynamic_cast<G*>(x);
				}).where([](auto x)
				{
					return (x != nullptr);
				});
			}
		};
		
		
	}
	}
	
	template <class T>
	template <class G>
	IIterable<G> IIterable<T>::ofType() const
	{
		return Meta::OfType::Helper<T, G>::call(this);
	}
	
}
}