#ifndef __MYGAMECARDS_H__
#define __MYGAMECARDS_H__

#include "cardGame.h"

#include "cardsPlayer.h"
#include "gamePlayer.h"
#include "deck.h"
#include "cards.h" 

class MyGame: public Game
{

public:

    MyGame(unsigned int m_numOfRoundes, bool _showHandEachRound);
	virtual ~MyGame();
	MyGame(const MyGame& _game);
	const MyGame& operator= (const MyGame& _game);
	
	virtual void    DealingCards(unsigned int _numOfCards);
	virtual int     RoundRoutine(ostream& _out);
	virtual void    PresentHands(ostream& _out) const;
	unsigned int    GetNumOfRoundes()const {return m_numOfRoundes;}

private:
	void    MatchRoutine(unsigned int _player1, unsigned int _player2);
	
protected:
    
    bool            m_showHandEachRound;
    unsigned int    m_numOfRoundes;
    GamePlayer      m_players[4];
    
};
#endif /* __GAMECARDS_H__ */

