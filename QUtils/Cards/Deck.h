#pragma once
#include <deque>
#include <random>

namespace QUtils { namespace Cards {
	
	template <class T>
	class Deck
	{
		protected:
		std::deque<T> imp;
		
		public:
		
		inline auto begin()
		{ return imp.begin(); }
		
		inline auto end()
		{ return imp.end(); }
		
		inline auto begin() const
		{ return imp.cbegin(); }
		
		inline auto end() const
		{ return imp.cend(); }
		
		
		
		template <class S>
		void setCards(S& s)
		{
			imp = std::deque<T>(s.begin(), s.end());
		}
		
		T draw()
		{
			T card = imp.front();
			imp.pop_front();
			return card;
		}
		
		void push_bottom(const T card)
		{
			imp.push_back(card);
		}
		
		void shuffle()
		{
			std::random_shuffle(imp.begin(), imp.end());
		}
		
		inline size_t size() const
		{ return imp.size(); }
		
		T peek() const
		{
			return imp.front();
		}
		
		template <class S>
		void addCards(S s)
		{
			for (const auto& card : s)
			{
				imp.push_back(card);
			}
		}
		
		void addCard(const T card)
		{
			imp.push_back(card);
		}
		
		
		template <class G>
		friend bool operator==(const Deck<G> d1, const Deck<G> d2);
		
		template <class G>
		friend bool operator!=(const Deck<G> d1, const Deck<G> d2);
	};
	
	template <class T>
	bool operator==(const Deck<T> d1, const Deck<T> d2)
	{
		return (d1.imp == d2.imp);
	}
	
	template <class T>
	bool operator!=(const Deck<T> d1, const Deck<T> d2)
	{
		return (d1.imp != d2.imp);
	}
}
}