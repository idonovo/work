#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cardsPlayer.h"
#include "cards.h"
#include "deck.h"


class GamePlayer: public Player
{

public:
	
	GamePlayer();
	GamePlayer(const GamePlayer& _org);
	virtual ~GamePlayer();
	GamePlayer& operator= (const GamePlayer& _origin);
	
	virtual void	Insert(Card _card);
	virtual Card	DrawCard();
	bool            IsHaveBiggerThen(const Card& _card);
	void		    DraWBiggerThen(const Card& _card);


private:
	unsigned int    FindSuit(const Card& _card);
	unsigned int 	SearchBiggerCardInSuit(const Card& _card, unsigned int _i);

};



#endif /* __PLAYER_H__ */

