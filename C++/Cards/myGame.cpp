#include "myGame.h"
#include "cardGame.h"

/* ============================= 	*/

/*IMPLEMENTATION OF CLASS class*/

/* ============================= 	*/		

// CTOR

MyGame::MyGame(unsigned int _numOfRoundes, bool _showHandEachRound): Game()
{
    m_numOfRoundes = _numOfRoundes;
    m_showHandEachRound = _showHandEachRound;
}

// COPY CTOR



/* ============================= 	*/	

/* ============================= 	*/	

// DTOR

MyGame::~MyGame(){}

/* ============================= 	*/	

/* ============================= 	*/	


// GET FUNCTIONS


/* ============================= 	*/	

/* ============================= 	*/	



// SET FUNCTIONS

/* ============================= 	*/	

/* ============================= 	*/	


// OPERATOR FUNCTIONS

/* ============================= 	*/	

/* ============================= 	*/	



// ADDITIONAL FUNCTIONALITY

void MyGame::DealingCards(unsigned int _numOfCards)
{
    Deck deck;
    deck.Shuffle();
    
    for (unsigned int i = 0; i < 13; i += 1)
	{
		for (unsigned int x = 0; x < 4; x += 1)
		{
		    m_players[x].Insert(deck.DrawCard());
		}
	}

}

void MyGame::MatchRoutine(unsigned int _player1, unsigned int _player2)
{
    Card draw = m_players[_player1].DrawCard();
    Card& d = draw;
    
    if(m_players[_player2].IsHaveBiggerThen(d))
    {
         m_players[_player2].DraWBiggerThen(d);
         m_players[_player2].ChangeScore(1);
    }
    else
    {
        m_players[_player2].Insert(draw);
    }
}

int MyGame::RoundRoutine(ostream& _out)
{
    for (unsigned int x = 0; x < 4; x += 1)
	{
		MatchRoutine(x%4, (x+1)%4);
	}
	
	if(m_showHandEachRound)
	{
	    _out << "current hands:" << endl;
	    PresentHands(_out);
	}
	
	for (unsigned int x = 0; x < 4; x += 1)
	{
		if(m_players[x].IsEmpty())
		{
		    return x;
		}
	}
	return -1;
}

void MyGame::PresentHands(ostream& _out) const
{
    for (unsigned int x = 0; x < 4; x += 1)
	{
		_out << "player number  " << x+1 <<" cards:" << endl;
		m_players[x].PresentCards(_out);
		_out << endl;
	}

}
/* ============================= 	*/	

/* ============================= 	*/

// PRIVATE FUNCTIONS
