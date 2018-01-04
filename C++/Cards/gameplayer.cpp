#include "gamePlayer.h"
#include <stdlib.h>
#include <time.h>


/* ============================= 	*/

/*IMPLEMENTATION OF CLASS class*/

/* ============================= 	*/		

// CTOR

GamePlayer::GamePlayer(): Player(){}

// COPY CTOR

/* ============================= 	*/	

/* ============================= 	*/	



// DTOR

GamePlayer::~GamePlayer(){}

/* ============================= 	*/	

/* ============================= 	*/	


// GET FUNCTIONS

/* ============================= 	*/	

/* ============================= 	*/	



// SET FUNCTIONS
/* ============================= 	*/	

/* ============================= 	*/	



// OPERATOR FUNCTIONS

GamePlayer& GamePlayer:: operator= (const GamePlayer& _origin)
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

void GamePlayer::Insert(Card _card)
{
	
	unsigned int i = FindSuit(_card);
	if(i == m_vec.size())
	{
	    m_vec.push_back(_card);
	}
	else
	{
	    i = SearchBiggerCardInSuit(_card, i);
		m_vec.insert(m_vec.begin() + i , _card);
	}
	return;
}


bool GamePlayer::IsHaveBiggerThen(const Card& _card)
{
	unsigned int i = FindSuit(_card);
	if(i == m_vec.size())
	{
	    return false;
	}
	else
	{
	    i = SearchBiggerCardInSuit(_card, i);
		return m_vec[i].GetSuit() == _card.GetSuit()?  true: false;
	}
}

void GamePlayer::DraWBiggerThen(const Card& _card)
{

    unsigned int i = FindSuit(_card);
	i = SearchBiggerCardInSuit(_card, i);
	m_vec.erase(m_vec.begin() + i);
	return;
}

Card GamePlayer::DrawCard()
{
    srand(time(NULL));
    int card = rand()% (m_vec.size() +1) ;
    Card toDraw = m_vec[card-1];
    m_vec.erase(m_vec.begin() + (card-1));
    return toDraw;
}

/* ============================= 	*/	

/* ============================= 	*/

// PRIVATE FUNCTIONS

unsigned int GamePlayer::FindSuit(const Card& _card)
{
	for(unsigned int i = 0; i < m_vec.size(); i += 1)
	{
		if(m_vec[i].GetSuit() == _card.GetSuit())
		{			
			return i;
		}		
	}	
	return m_vec.size();
}

unsigned int GamePlayer::SearchBiggerCardInSuit(const Card& _card, unsigned int _i)
{
	while(m_vec[_i].GetSuit() == _card.GetSuit() && _i <  m_vec.size())
	{
		if(_card.GetRank() < m_vec[_i].GetRank())
		{			
			break;
		}
		++_i;		
	}	
	return _i;
}


