#ifndef __CARD_H__
#define __CARD_H__


#include <iostream>
using namespace std;

enum Suits
{
	diamond,
	club,
	hearts,
	spade
};
	

class Card
{

public:
	
	Card(const Card& _org);
	Card(Suits _st, unsigned int _rank);
	~Card();
	const Card& operator= (const Card& _card);
	bool	    operator> (const Card& _card) const;
	
	bool 			SetSuit(Suits _st);
	bool 			SetRank(unsigned int _rank);
	Suits 			GetSuit() const;
	unsigned int 	GetRank() const;
	void 			PresentCard(ostream& _out) const;
	
private:
	
	Suits 			m_suit;
	unsigned int	m_rank; 
};


#endif /* __CARD_H__ */
