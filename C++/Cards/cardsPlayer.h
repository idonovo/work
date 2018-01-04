#ifndef __CARDPLAY_H__
#define __CARDPLAY_H__

#include "cards.h"
#include "deck.h"



class Player
{

public:
	
	Player();
	Player(const Player& _org);
	virtual ~Player();
	Player& operator= (const Player& _origin);
	
	virtual void	Insert(Card _card);
	virtual Card    DrawCard();
	void		    ChangeScore(int _x);	
	int             GetScore() const;

	bool 		    IsEmpty() const;
	void 		    PresentCards(ostream& _out) const;
	
protected:
	vector<Card> 	m_vec;
	int 	m_score;

};
#endif /* __CARDPLAY_H__ */

