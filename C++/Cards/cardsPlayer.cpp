#include "cardsPlayer.h"
#include <stdlib.h>
#include <time.h>


/* ============================= 	*/

/*IMPLEMENTATION OF CLASS class*/

/* ============================= 	*/		

// CTOR

Player::Player()
{
    m_score = 0;
}

// COPY CTOR

Player::Player(const Player& _org)
{
	m_score = _org.m_score;
	m_vec = _org.m_vec;
}
/* ============================= 	*/	

/* ============================= 	*/	



// DTOR

Player::~Player(){}

/* ============================= 	*/	

/* ============================= 	*/	


// GET FUNCTIONS

int Player::GetScore() const
{
	return m_score;
}

bool Player::IsEmpty() const
{
    return (m_vec.size() > 0)? true: false;
}

/* ============================= 	*/	

/* ============================= 	*/	



// SET FUNCTIONS

void Player::ChangeScore(int _x)
{
	m_score += _x;
}

/* ============================= 	*/	

/* ============================= 	*/	



// OPERATOR FUNCTIONS

Player& Player:: operator= (const Player& _origin)
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

void Player::Insert(Card _card)
{
	
	m_vec.push_back(_card);
}


Card Player::DrawCard()
{
    Card toDraw = m_vec[0];
    m_vec.erase(m_vec.begin());
    return toDraw;
}

void Player::PresentCards(ostream& _out) const
{
    for (unsigned int i = 0; i < m_vec.size(); i += 1)
	{
		m_vec[i].PresentCard(_out);
	}
}
/* ============================= 	*/	

/* ============================= 	*/

// PRIVATE FUNCTIONS


