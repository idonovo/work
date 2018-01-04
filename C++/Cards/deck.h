#ifndef __DECK_H__
#define __DECK_H__

#include "cards.h"
#include <vector>
#include <algorithm>  
#include <iostream>
using namespace std;

class Deck
{

public:
	
	Deck();
	Deck(const Deck& _org);
	~Deck();
	const Deck& operator= (const Deck& _origin);
	
	void	Shuffle();
	bool 	IsEmpty() const;
	
	Card	DrawCard();
	
	void	InsertCard(Card& _card);
	void 	PresentCards(ostream& _out) const;
	
private:
	vector<Card> m_vec;

};

#endif /* __DECK_H__ */
