#include "deck.h"
#include <stdlib.h>     /* srand, rand */

#define DECK_SIZE 15
/* ============================= 	*/

/*IMPLEMENTATION OF CLASS class*/

/* ============================= 	*/		

// CTOR
	
Deck::Deck()
{
	for (unsigned int i = 2; i < DECK_SIZE; i += 1)
	{
		Card c1(diamond, i);
		Card c2(club, i);
		Card c3(hearts, i);
		Card c4(spade, i);
		m_vec.push_back(c1);
		m_vec.push_back(c2);
		m_vec.push_back(c3);
		m_vec.push_back(c4);
	}
	
}
// COPY CTOR
Deck::Deck(const Deck& _org)
{
	m_vec = _org.m_vec;
}

/* ============================= 	*/	

/* ============================= 	*/	

// DTOR

Deck::~Deck(){}
/* ============================= 	*/	

/* ============================= 	*/	


// GET FUNCTIONS

Card Deck::DrawCard()
{
	if(!IsEmpty())
	{
	    Card toDraw(m_vec.back());
	    m_vec.pop_back();
	    return toDraw;
	}
	Card spadeAce(spade, 1);
	return spadeAce;
}


/* ============================= 	*/	

/* ============================= 	*/	



// OPERATOR FUNCTIONS

const Deck& Deck::operator= (const Deck& _origin)
{
	if(this != &_origin)
	{
		m_vec = _origin.m_vec;
	}
	return *this;
}

/* ============================= 	*/	

/* ============================= 	*/	



// ADDITIONAL FUNCTIONALITY

bool Deck::IsEmpty() const
{
	return m_vec.empty();
}

void Deck::InsertCard(Card& _card)
{
	m_vec.push_back(_card);
}

void Deck::PresentCards(ostream& _out) const
{
	for (unsigned int i = 0; i < m_vec.size(); i += 1)
	{
		m_vec[i].PresentCard(_out);
	}
}

void Deck::Shuffle()
{
	random_shuffle(m_vec.begin(), m_vec.end());
}
/* ============================= 	*/	

/* ============================= 	*/

// PRIVATE FUNCTIONS
