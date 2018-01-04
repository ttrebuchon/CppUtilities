#pragma once

#include "Card.h"
#include "StandardValues.h"
#include "Deck.h"
#include <QUtils/Exception/ArgumentOutOfRange.h>

namespace QUtils { namespace Cards {
	
	typedef Card<StdSuit, StdValue> StdCard;
	
	template <class Suit, class Value>
	std::string to_string(const Card<Suit, Value> card)
	{
		return to_string(card.value) + " of " + to_string(card.suit);
	}
	
	static std::string to_string(const StdSuit suit)
	{
		switch (suit)
		{
			case Hearts:
			return "Hearts";
			
			case Spades:
			return "Spades";
			
			case Diamonds:
			return "Diamonds";
			
			case Clovers:
			return "Clovers";
			
			default:
			throw ArgOutOfRange();
		}
	}
	
	static std::string to_string(const StdValue value)
	{
		switch (value)
		{
			case Two:
			return "2";
			
			case Three:
			return "3";
			
			case Four:
			return "4";
			
			case Five:
			return "5";
			
			case Six:
			return "6";
			
			case Seven:
			return "7";
			
			case Eight:
			return "8";
			
			case Nine:
			return "9";
			
			case Ten:
			return "10";
			
			case Jack:
			return "Jack";
			
			case Queen:
			return "Queen";
			
			case King:
			return "King";
			
			case Ace:
			return "Ace";
			
			default:
			throw ArgOutOfRange();
		}
	}
	
	
}
}