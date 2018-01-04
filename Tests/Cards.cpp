#include "../Tests_Helpers.h"
#include <QUtils/Cards/Cards.h>
#include <QUtils/Combinatorial/Permutations.h>
#include <vector>
#include <QUtils/Cards/Blackjack.h>

DEF_TEST(Cards)
{
	using namespace QUtils::Cards;
	
	Deck<Card<StdSuit, StdValue>> deck;
	typedef Deck<StdCard> StdDeck;
	
	static_assert(std::is_same<decltype(deck), StdDeck>::value, "");
	
	std::vector<StdCard> cards;
	{
	
	auto rawPerms = QUtils::Combinatorial::permutations(
		std::list<StdSuit>{
			Hearts,
			Spades,
			Diamonds,
			Clovers
		},
		std::list<StdValue>{
			Two,
			Three,
			Four,
			Five,
			Six,
			Seven,
			Eight,
			Nine,
			Ten,
			Jack,
			Queen,
			King,
			Ace
		});
	
	assert_ex(rawPerms.size() == 52);
	cards.reserve(rawPerms.size());
	
	for (auto& perm : rawPerms)
	{
		cards.push_back(StdCard{perm.first, perm.second});
	}
	
	
	}
	
	assert_ex(cards.size() == 52);
	
	assert_ex(to_string(StdCard{Hearts, Ace}) == "Ace of Hearts");
	assert_ex(to_string(StdCard{Diamonds, Ace}) == "Ace of Diamonds");
	assert_ex(to_string(StdCard{Clovers, Ace}) == "Ace of Clovers");
	assert_ex(to_string(StdCard{Spades, Ace}) == "Ace of Spades");
	
	deck.setCards(cards);
	
	deck.shuffle();
	{
		size_t start = deck.size();
		auto top = deck.peek();
		assert_ex(deck.peek() == top);
		for (int i = 0; i < 52; ++i)
		{
			auto c = deck.draw();
			deck.push_bottom(c);
		}
		assert_ex(deck.size() == start);
		assert_ex(deck.peek() == top);
		
		dout << "\n\n\n";
	}
	
	assert_ex(deck == deck);
	assert_ex(deck != StdDeck());
	
	deck.addCards(deck);
	assert_ex(deck.size() == 104);
	
	deck.shuffle();
	assert_ex(deck.size() == 104);
	
	deck.shuffle();
	{
		size_t start = deck.size();
		auto top = deck.peek();
		assert_ex(deck.peek() == top);
		for (int i = 0; i < 104; ++i)
		{
			auto c = deck.draw();
			deck.push_bottom(c);
		}
		assert_ex(deck.size() == start);
		assert_ex(deck.peek() == top);
	}
	
	assert_ex(Blackjack<StdCard>::HandValue({StdCard{Hearts, Ten}}) == 10);
	
	assert_ex(
	Blackjack<StdCard>::HandValue({
		StdCard{Hearts, Ten},
		StdCard{Hearts, Ace}
	}) == 21);
	
	assert_ex(
	Blackjack<StdCard>::HandValue({
		StdCard{Hearts, Ten},
		StdCard{Hearts, Ace},
		StdCard{Hearts, Ace}
	}) == 12);
	
	assert_ex(
	Blackjack<StdCard>::HandValue({
		StdCard{Hearts, Five},
		StdCard{Hearts, Ace},
		StdCard{Hearts, Ace}
	}) == 17);
	
	assert_ex(
	Blackjack<StdCard>::HandValue({
		StdCard{Hearts, Five},
		StdCard{Hearts, Ace},
		StdCard{Hearts, Ace},
		StdCard{Hearts, King}
	}) == 17);
	
	assert_ex(
	Blackjack<StdCard>::HandValue({
		StdCard{Hearts, Five},
		StdCard{Hearts, Ace},
		StdCard{Hearts, Ace},
		StdCard{Hearts, King},
		StdCard{Hearts, Ten}
	}) == -1);
	
	Blackjack<StdCard> blackjack;
	blackjack.shuffle();
	assert_ex(!blackjack.handInProgress());
	blackjack.deal();
	assert_ex(!blackjack.handInProgress());
	
	assert_ex(blackjack.addPlayer() == 1);
	
	for (const auto& card : blackjack.deck)
	{
		dout << to_string(card) << "\n";
	}
	dout << "\n\n";
	
	assert_ex(blackjack.addPlayer() == 2);
	assert_ex(!blackjack.handInProgress());
	auto topCard = blackjack.deck.peek();
	blackjack.deal();
	assert_ex(blackjack.handInProgress());
	blackjack.player();
	assert_ex(blackjack.handInProgress());
	dout << to_string(blackjack.deck.peek()) << "\n";
	dout << "Value: " << blackjack.player().hand.value() << "\n";
	assert_ex(blackjack.player().hand.cards[0] == topCard);
	
	
	return true;
}