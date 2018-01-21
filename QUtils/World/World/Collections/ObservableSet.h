#pragma once

#include <set>
#include <QUtils/Events.h>

namespace QUtils { namespace World {
namespace Collections {
	
	template <class T, void(*G)(const T&) = nullptr>
	class SetObservers
	{
		public:
		typedef void(*Insert_t)(const T&);
		
		static void insert_f(const T&)
		{
			
		}
		
		constexpr static Insert_t insert = G; /*(Insert_t)([](const T&)
		{
			
		});*/
	};
	
	
	template <class T, class Compare = std::less<T>>
	class ObservableSet : protected std::set<T, Compare>
	{
		private:
		typedef std::set<T, Compare> Base;
		typedef ObservableSet<T, Compare> this_t;
		
		protected:
		
		public:
		typedef T value_type;
		typedef typename Base::iterator iterator;
		EventHandler<this_t*, const T&> onInserted;
		EventHandler<this_t*> onClearing;
		EventHandler<this_t*> onCleared;
		
		void insert(const T& t)
		{
			/*if (Obsrv::insert != nullptr)
			{
				auto p = Base::insert(t);
				if (p.second)
				{
					Obsrv::insert(*p.first);
				}
			}
			else
			{
				Base::insert(t);
			}*/
			if (onInserted.size() > 0)
			{
				auto p = Base::insert(t);
				if (p.second)
				{
					onInserted(this, *p.first);
				}
			}
			else
			{
				Base::insert(t);
			}
		}
		
		void insert(T&& t)
		{
			/*if (Obsrv::insert != nullptr)
			{
				auto p = Base::insert(t);
				if (p.second)
				{
					Obsrv::insert(*p.first);
				}
			}
			else
			{
				Base::insert(t);
			}*/
			if (onInserted.size() > 0)
			{
				auto p = Base::insert(t);
				if (p.second)
				{
					onInserted(this, *p.first);
				}
			}
			else
			{
				Base::insert(t);
			}
		}
		
		void clear()
		{
			if (onClearing.size() > 0)
			{
				onClearing(this);
			}
			Base::clear();
			if (onCleared.size() > 0)
			{
				onCleared(this);
			}
		}
		
		size_t size() const
		{
			return Base::size();
		}
		
		size_t count(const T& t) const
		{
			return Base::count(t);
		}
		
		inline iterator begin() noexcept
		{
			return Base::begin();
		}
		
		inline iterator end() noexcept
		{
			return Base::end();
		}
	};
	
	
}
}
}