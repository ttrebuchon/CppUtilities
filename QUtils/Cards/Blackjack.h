#pragma once
#include <QUtils/Likely.h>
#include "Cards.h"
#include <QUtils/Exception/ArgumentOutOfRange.h>

namespace QUtils { namespace Cards {
	
	template <class T, class Money = long>
	class Blackjack
	{
		//Helpers
		public:
		constexpr static int CardValue(const T card)
		{
			switch (card.value)
			{
				case Two:
				return 2;
				
				case Three:
				return 3;
				
				case Four:
				return 4;
				
				case Five:
				return 5;
				
				case Six:
				return 6;
				
				case Seven:
				return 7;
				
				case Eight:
				return 8;
				
				case Nine:
				return 9;
				
				case Ten:
				case Jack:
				case Queen:
				case King:
				return 10;
				
				case Ace:
				return -1;
				
				default:
				throw ArgOutOfRange();
			}
		}
		
		static int HandValue(const auto hand)
		{
			size_t aces = 0;
			int val = 0;
			
			for (const T& card : hand)
			{
				if (val > 21)
				{
					break;
				}
				if (unlikely(card.value == Ace))
				{
					++aces;
				}
				else
				{
					val += CardValue(card);
				}
			}
			
			if (aces + val > 21)
			{
				return -1;
			}
			
			int elevens = static_cast<int>((21 - val - aces)/10);
			if (elevens > 0)
			{
				val += 11*elevens;
				aces -= elevens;
			}
			
			val += aces;
			
			
			if (val > 21)
			{
				return -1;
			}
			
			return val;
		}
		
		static int HandValue(std::initializer_list<T> hand)
		{
			size_t aces = 0;
			int val = 0;
			
			for (const T& card : hand)
			{
				if (val > 21)
				{
					break;
				}
				if (unlikely(card.value == Ace))
				{
					++aces;
				}
				else
				{
					val += CardValue(card);
				}
			}
			
			if (aces + val > 21)
			{
				return -1;
			}
			
			int elevens = static_cast<int>((21 - val - aces)/10);
			if (elevens > aces)
			{
				elevens = aces;
			}
			
			if (elevens > 0)
			{
				val += 11*elevens;
				aces -= elevens;
			}
			
			val += aces;
			
			
			if (val > 21)
			{
				return -1;
			}
			
			return val;
		}
		
		static Deck<StdCard> StdCards()
		{
			Deck<StdCard> deck;
			for (int i = 0; i < 13; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					deck.addCard(StdCard{(StdSuit)j, (StdValue)i});
				}
			}
			return deck;
		}
		
		public:
		class Hand
		{
			public:
			std::vector<T> cards;
			
			Hand() : cards()
			{
				cards.reserve(5);
			}
			
			inline size_t count() const
			{ return cards.size(); }
			
			int value() const
			{
				return HandValue(cards);
			}
		};
		
		class Wager
		{
			public:
			Money quantity;
		};
		
		
		class Player
		{
			public:
			Blackjack<T>& game;
			Hand hand;
			Money money;
			bool playing;
			
			Money wager;
			
			Player(Blackjack<T>& game) : game(game), hand(), money(0), playing(true), wager(0)
			{
				
			}
		};
		
		protected:
		public:
		Deck<T> deck;
		std::vector<T> discard;
		Hand dealer;
		size_t playerTurnIndex;
		
		public:
		std::vector<Player> players;
		
		
		Blackjack() : Blackjack(StdCards())
		{}
		
		Blackjack(const Deck<T>& deck) : deck(deck), discard(), dealer(), playerTurnIndex(-1), players()
		{
			discard.reserve(deck.size());
		}
		
		inline const Deck<T>& getDeck() const
		{
			return deck;
		}
		
		inline Deck<T>& getDeck()
		{
			return deck;
		}
		
		
		void deal()
		{
			if (players.size() == 0)
			{
				return;
			}
			
			if (handInProgress())
			{
				//TODO
				throw std::exception();
			}
			
			for (auto& player : players)
			{
				player.hand.cards.push_back(deck.draw());
			}
			dealer.cards.push_back(deck.draw());
			
			
			for (auto& player : players)
			{
				player.hand.cards.push_back(deck.draw());
			}
			dealer.cards.push_back(deck.draw());
			
			playerTurnIndex = 0;
		}
		
		bool handInProgress() const
		{
			if (dealer.count() > 0)
			{
				return true;
			}
			if (players.size() > 0)
			{
				for (auto& player : players)
				{
					if (player.hand.count() > 0)
					{
						return true;
					}
				}
			}
			return false;
		}
		
		size_t addPlayer()
		{
			if (handInProgress())
			{
				//TODO
				throw std::exception();
			}
			
			players.emplace_back(*this);
			return players.size();
		}
		
		void shuffle()
		{
			if (handInProgress())
			{
				//TODO
				throw std::exception();
			}
			
			deck.addCards(discard);
			discard.clear();
			deck.shuffle();
		}
		
		const Player& player() const
		{
			return players.at(playerTurnIndex);
		}
		
		
	};
}
}