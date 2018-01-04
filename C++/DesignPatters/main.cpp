#include "AccountImp.h"
#include "Subject.h"
#include "Bank.h"
#include "Observer.h"
#include "Accounts.h"
#include "SingleAccount.h"

int main()
{
	bool isRunning = true;
	int input,action;
	string type;
	
	
	Bank& bank = Bank::CreateBank();
	while(isRunning)
	{
		cout << "1) would you like to open an account? "<< endl;
		cout << "2) would you like to Notify accounts?"<< endl;
		cout << "3) Get number of accounts in bank"<< endl;
		cin >> input;
		switch(input)
		{
		    case 1:
		    {
			    cout << "which Account would you wont to open?" << endl;
			    cout << "1) Personal Account" << endl;
			    cout << "2) Family Account" << endl;
			    cout << "3) Stock Account" << endl;
			    cout << "4) exit" << endl;
			    cin >> action;
			    switch (action) 
			        {
			            ;
			            case 1:
			            	type="Personal";
			                break;                    
			            case 2:
			            	type="Family";
			                break;
			            case 3:
			            	type="Stock";
			                break;
					    case 4:		            
			                isRunning=false;
			                break;
			        }
			    bank.OpenAccount(type);
			break;
		    }
		    case 2:
		    {
			    cout << "which type to send message?" << endl;
			    cout << "1) Personal Account" << endl;
			    cout << "2) Family Account" << endl;
			    cout << "3) Stock Account" << endl;
			    cout << "4) All Accounts" << endl;
			    cin >> action;
			    switch (action) 
			        {
			            case 1:
			            	bank.Meeting();
			                break;                    
			            case 2:
			            	bank.GiveBonus();
			                break;
			            case 3:
			            	bank.Invest();
			                break;
		                case 4:
		                	bank.Meeting();
			            	bank.GiveBonus();
			            	bank.Invest();
		                	break;
			            default:
			                isRunning = 0;
			        }
			break;
		    }
		    case 3:
		    {
		        cout<< "The number of account is: " << bank.GetNumOfAcc()<<endl;
		        break;
		    }
		    default:
		    {
		        isRunning = 0;
		        break;
		    }
	    }
	}
	return 0;
}

