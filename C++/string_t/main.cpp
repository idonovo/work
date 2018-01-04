#include "string_t.h"
#include <stdio.h>
#include <iostream>
using namespace std;


int main()
{
	String_t y;
	String_t x;
	char buffer[128];
	
	int res, check, cap, start, flag =1;
	
	while(flag)
	{
		cout<< "please choose option:" << endl;
		cout<< "1. set" << endl;
		cout<< " 2. get " <<endl;
		cout<< " 3. compare " <<endl;
		cout<< " 4. upper " <<endl;
		cout<< " 5. lower " <<endl;
		cout<< " 6. prepend a string" <<endl;
		cout<< " 7. prepend String_t " <<endl;
		cout<< " 8. check contains " <<endl;
		cout<< " 9. is equal (==) " <<endl;
		cout<< " 10. is bigger (<) " <<endl;
		cout<< " 11. length " <<endl;
		cout<< "12. get capacity" <<endl;
		cout<< " 13. set capacity " <<endl;
		cout<< " 14. case sensetive" <<endl;
		cout<< " 15.  cancel case sensetive" <<endl;
		cout<<  " 16. get num of strings " <<endl;
		cout<< " 17. get first occurance in string" <<endl;
		cout<< " 18. get last occurance in string" <<endl;
		cout<< "19. get new string"  <<endl;
		cout<< "else - exit " <<endl <<endl;
		
		cin >> res;
		
		switch(res)
		{
			case 1:
				cout<< "please enter a string (up to 128 chars):";
				cin>> buffer;
				x.setString(buffer);
				cout<< "the new string is:" <<endl;
				x.print();
				break;
			
			case 2:
				cout<<"the string is:" <<endl;
				cout<< x.getString();
				break;
				
			case 3:
				cout<<"please enter a string:" <<endl;
				cin>>y;
				check = x.compare(y);
				if(check == 2)
				{
					cout<<"my string is bigger:" <<endl;
					break;
				}
				else if(check ==1)
				{	
					cout<<"your string is bigger:" <<endl;
					break;
				}
				cout<<"equal:" <<endl;
				break;
				
			case 4:
				x.ConvertToUpper();
				x.print();
				break;
			
			case 5:
				x.ConvertToLower();
				x.print();
				break;
			
			case 6:
				cout<<"please enter a string:" <<endl;
				cin>>buffer;
				x.Prepend(buffer);
				x.print();
				break;
				
			case 7:
				cout<<"please enter a string:" <<endl;
				cin>>y;
				x.Prepend(y);
				cout<<"pnew string is:" <<endl;
				x.print();
				break;
			
			case 8:
				cout<<"please enter a string:" <<endl;
				cin>>buffer;
				if(x.Contains(buffer))
				{
					cout<<"found!!!\n";
					break;
				}
				cout<<"not found!!!\n";
				break;
				
			case 9:
				cout<<"please enter a string:" <<endl;
				cin>>y;
				if(x == y)
				{
					cout<<"equal!!!" <<endl;
					break;
				}
				cout<<"not eqaul!!!" <<endl;
				break;
			
			case 10:
				cout<<"please enter a string:" <<endl;
				cin>>y;
				if(x < y)
				{
					cout<<"my string bigger!!!" <<endl;
					break;
				}
				cout<<"my string not bigger!!!" <<endl;
				break;
			
			case 11:
				cout<< "the length is" << x.length() <<endl;
				break;
			
			case 12:
				cout<< "the default capacity is" << String_t::GetDefaultSize() <<endl;
				break;
			
			case 13:
				cout<<"please enter new capacity" <<endl; 
				cin >> cap;
				cout<< "the new capacity is " << String_t::GetDefaultSize() <<endl;
				break;
			
			case 14:
				cout<< "now case sensitive" <<endl;
				String_t::SetOnCaseSens();
				break;
			
			case 15:
				cout<< "cancel case sensitive" <<endl;
				String_t::SetOffCaseSens();
				break;
			
			case 16:
				cout<<"num of strings is : " << String_t::GetNumOfObjs() << endl; 
				break;
				
			case 17:
			    cout<< "please enter a single char" <<endl;
			    cin >> buffer[0];
			    cout<< "the index of first occurance is: " << x.GetFirst(buffer[0]) <<endl;
				break;
			
			case 18:
				cout<< "please enter a single char" <<endl;
			    cin >> buffer[0];
			    cout<< "the index of last occurance is: " << x.GetLast(buffer[0]) <<endl;
				break;
			
			case 19:
				cout<< "please enter a start index and length" <<endl;
			    cin >> start >> cap;
			    y = x(start, cap); 
			    cout<< "the new string is" << y.getString() <<endl;
				break;		
			default:
				flag = 0;
				break;
		}			
	}
}

