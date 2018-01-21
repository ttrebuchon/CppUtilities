#pragma once

#include "../Effect.h"
#include <set>
#include <QUtils/Iterable/IIterable.h>
#include "ObservableSet.h"

namespace QUtils { namespace World {
	
	namespace Helpers
	{
		struct Effect_Compare
		{
			std::less<Time> lesser;
			
			bool operator()(Effect::CPtr p1, Effect::CPtr p2) const
			{
				if (!p2)
				{
					return false;
				}
				if (!p1)
				{
					return true;
				}
				
				auto t1 = p1->time().end;
				auto t2 = p2->time().end;
				
				return (t1 != t2) ? lesser(p1->time().end, p2->time().end) : (p1 < p2);
			}
		};
		
		struct Invert_Effect_Compare
		{
			Effect_Compare comp;
			
			bool operator()(Effect::Ptr p1, Effect::Ptr p2) const
			{
				return !comp(p1, p2);
			}
		};
	}
	
	/*class EffectSet_Obs
	{
		typedef typename Effect::Ptr T;
		
		public:
		
		static void insert(const T&)
		{
			std::cerr << "Inserting!!!\n\n\n" << std::endl;
		}
	};*/
	
	
	/*class EffectSet : std::set<Effect::Ptr, Helpers::Effect_Compare>
	{
		protected:
		typedef std::set<Effect::Ptr, Helpers::Effect_Compare> Base;
		typedef Effect::Ptr T;
		
		public:
		typedef typename Base::iterator iterator;
		
		void clear();
		void insert(const T);
		size_t size() const;
		size_t count(const T) const;
		
		iterator begin() const;
		iterator end() const;
	};*/
	
	//typedef Collections::ObservableSet<Effect::Ptr, Collections::SetObservers<Effect::Ptr, &EffectSet_Obs::insert>, Helpers::Effect_Compare> EffectSet;
	typedef Collections::ObservableSet<Effect::Ptr, Helpers::Effect_Compare> EffectSet;
}
}