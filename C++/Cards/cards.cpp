#include "cards.h"

/* ============================= 	*/

/*IMPLEMENTATION OF CLASS class*/

/* ============================= 	*/		

// CTOR

Card::Card(Suits _st, unsigned int _rank)
{
	m_suit = _st;
	m_rank = _rank; 
}

// COPY CTOR

Card::Card(const Card& _card)
{
	m_suit = _card.m_suit;
	m_rank = _card.m_rank;
}

/* ============================= 	*/	

/* ============================= 	*/	

// DTOR

Card::~Card(){}

/* ============================= 	*/	

/* ============================= 	*/	


// GET FUNCTIONS

Suits Card::GetSuit() const
{
	return m_suit;
}

unsigned int Card::GetRank() const
{
	return m_rank;
}

/* ============================= 	*/	

/* ============================= 	*/	



// SET FUNCTIONS

bool Card::SetSuit(Suits _st)
{
	if(_st > 3)
	{
		return false;
	}
	m_suit = _st;
	return true;
}

bool Card::SetRank(unsigned int _rank)
{
	if(_rank < 2 || _rank > 14)
	{
		return false;
	}
	m_rank = _rank;
	return true;
}

/* ============================= 	*/	

/* ============================= 	*/	


// OPERATOR FUNCTIONS

const Card& Card::operator= (const Card& _card)
{
	if(this != & _card)
	{
		m_suit = _card.m_suit;
		m_rank = _card.m_rank;
	}
	return *this;
}


bool Card::operator> (const Card& _card) const
{
	return (m_rank > _card.m_rank);
}

/* ============================= 	*/	

/* ============================= 	*/	



// ADDITIONAL FUNCTIONALITY

void Card:: PresentCard(ostream& _out) const
{
			
	switch(m_rank)
	{
		case 14: _out << "Ace";   break;
		case 11: _out << "Jack";  break;
		case 12: _out << "Queen"; break;
		case 13: _out << "King";  break;

		default:
			_out << m_rank;
			break;
	}
	switch(m_suit)
	{
		case diamond: _out << " of Diamonds" << endl; break;
		case spade:   _out << " of Spades" << endl;   break;
		case hearts:   _out << " of Hearts" << endl;   break;
		case club:    _out << " of Clubs" << endl;    break;
	}

}

/* ============================= 	*/	

/* ============================= 	*/

// PRIVATE FUNCTIONS
