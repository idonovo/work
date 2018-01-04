#ifndef __GAMECARDS_H__
#define __GAMECARDS_H__

#include "cardsPlayer.h"
#include "gamePlayer.h"
#include "deck.h"
#include "cards.h" 

class Game
{
public:

    Game(){};
	virtual ~Game(){};
	Game(const Game& _game);
	const Game& operator= (const Game& _game);
	
	virtual void    DealingCards(unsigned int _numOfCards) = 0;
	virtual void    PresentHands(ostream& _out) const = 0;
    
};
#endif /* __GAMECARDS_H__ */

