#include "myGame.h"
#include "cardsPlayer.h"
#include "gamePlayer.h"
#include "deck.h"
#include "cards.h" 
#include "cardGame.h" 

int main()
{
    
    
    cout << "please enter num of rounds:" <<endl;
	unsigned int rounds;
	cin >> rounds;
	
	cout<< "to show hands each rounde press 1 or 0 if not" << endl;
    bool hands;
    cin >> hands;
	
	MyGame game(rounds, hands);
	game.DealingCards(52);
	for (unsigned int i = 0; i < game.GetNumOfRoundes(); i += 1)
	{
	    if(game.RoundRoutine(cout) > 0)
	    {
	        cout << "the winner is player number  " << i+1 << endl;
	        break;
	    }  
	}
	
	game.PresentHands(cout);
	return 0;
}


