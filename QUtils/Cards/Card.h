#pragma once

#include "Suit.h"

namespace QUtils { namespace Cards {
	
	template <class S, class T>
	struct Card
	{
		S suit;
		T value;
	};
	
	template <class S, class T>
	bool operator==(const Card<S, T> c1, const Card<S, T> c2)
	{
		return (c1.suit == c2.suit && c1.value == c2.value);
	}
	
	template <class S, class T>
	bool operator!=(const Card<S, T> c1, const Card<S, T> c2)
	{
		return (c1.suit != c2.suit || c1.value != c2.value);
	}
}
}