
//#include "Dlist_t.h" 
#include "Container_t.h"
#include "Array_t.h"

#include <iostream>
using namespace std;

int main()
{
	Array_t<int*> x;
	int res, flag = 1;
	unsigned int index;
	
    while(flag)
	{
        cout<< "please choose option:" << endl;
		cout<< "1. Append" << endl;
		cout<< " 2. Prepend " <<endl;
		cout<< " 3. Contains " <<endl;
		cout<< " 4. Find " <<endl;
		cout<< " 5. Index " <<endl;
		cout<< " 6. Insert" <<endl;
		cout<< " 7. Remove " <<endl;
		cout<< " 8. RemoveAll " <<endl;
		cout<< " 9. RemoveAndDelete " <<endl;
		cout<< " 10. RemoveAllAndDeleteAll " <<endl;
		cout<< "else - exit " <<endl <<endl;
		
		cin >> res;
		
		switch(res)
		{
	    	case 1:
	    	    int *elemant1 = new int;
	            *elemant1 = 1;
	            int*& ref1 = elemant1; 
				cout<< "please enter an elemant";
				cin>> *elemant1;
				cout<< "please enter an index";
				cin>> index;
				x.Append(elemant1, index);
				break;
				
			case 2:
			    int *elemant2 = new int;
	            *elemant2 = 1;
	            int*& ref2 = elemant2; 
				cout<< "please enter an elemant";
				cin>> *elemant2;
				cout<< "please enter an index";
				cin>> index;
				x.Prepend(elemant2, index);
				break;
				
			case 3:
			    int *elemant3 = new int;
	            *elemant3 = 1;
	            int*& ref3 = elemant3; 
				cout<< "please enter an elemant";
				cin>> *elemant3;
				cout<< "the elemant is :" << x.Contains(ref3)
				break;
			
			case 4:
			    int *elemant4 = new int;
	            *elemant4 = 1;
	            int*& ref4 = elemant4; 
				cout<< "please enter an elemant";
				cin>> *elemant4;
				cout<< "the resault is:" << x.Find(ref4);
				break;
			
			case 5:
			    int *elemant5 = new int;
	            *elemant5 = 1;
	            int*& ref5 = elemant5; 
				cout<< "please enter an elemant";
				cin>> *elemant5;
				cout<< "the index is:" << x.Find(ref5);
				break;
			
			case 6:
			    int *elemant6 = new int;
	            *elemant6 = 1;
	            int*& ref6 = elemant6; 
				cout<< "please enter an elemant";
				cin>> *elemant6;
				x.Insert(ref6);
				cout<< "inserted!!";
				break;
				
			case 7:
			    int *elemant7 = new int;
	            *elemant7 = 1;
	            int*& ref7 = elemant7; 
				cout<< "please enter an elemant";
				cin>> *elemant7;
				x.Remove(ref7)
				cout<< "removed";
				break;
				
			case 8:
				x.RemoveAll();
				cout<< "removed";
				break;
				
			default:
				flag = 0;
				break;
		}
	x.Print(cout);	
	}
	return 0;
}

