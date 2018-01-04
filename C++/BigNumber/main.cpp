
#include "BigNumber.h"


void OpenFile(virtIO_t& vir

Open(const string& _path, const string& _mode);
int main()
{

	int res, number, flag =1;
	char buffer[1024];
	
	while(flag)
	{
		cout<< "please choose option:" << endl;
		cout<< "1. create from number" << endl;
		cout<< " 2.create from string " <<endl;
		cout<< " 3. create from big number " <<endl;
		cout<< " 4. = operator " <<endl;
		cout<< " 5. = operator from int " <<endl;
		cout<< " 6. > " <<endl;
		cout<< " 7. < " <<endl;
		cout<< " 8. add " <<endl;
		cout<< " 9. add with int" <<endl;
		cout<< " 10. substrsct " <<endl;
		cout<< " 11. substrsct with int" <<endl;
		cout<< " 12. == operator" <<endl;
	
		cout<< "else - exit " <<endl <<endl;
		
		cin >> res;
		
		switch(res)
		{
			case 1:
				{
				cout<< "please enter a number";
				cin>> number;
				BigNumber a(number);
				cout<< "the new BigNumber is:" << a <<endl;
				break;
				}
			case 2:
			    {
				cout<< "please enter a number";
				cin>> buffer;
				BigNumber b(buffer);
				cout<< "the new BigNumber is:" << b <<endl;
				break;
				}
			case 3:
			    {
				cout<< "please enter a number";
				cin>> buffer;
				BigNumber c(buffer);
				BigNumber d(c);
				cout<< "the new BigNumber is:" << d <<endl;
				break;
				}
			case 4:
		        {
				cout<< "please enter a number";
				cin>> buffer;
				BigNumber e(buffer);
				BigNumber f;
				f = e;
				cout<< "the BigNumber after assignment is:" << f <<endl;
				break;
				}
			case 5:
			    {
				cout<< "please enter a number";
				cin>> number;
				BigNumber g;
				g = number;
				cout<< "the BigNumber after assignment from int is:" << g <<endl;
				break;
				}
			case 6:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber h(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber i(buffer);
				if(h > i)
				{
				    cout << "first is bigger" << endl;
				    break;
				}
				cout << "first is not bigger" << endl;				
				break;
				}
			case 7:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber j(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber k(buffer);
				if(j < k)
				{
				    cout << "first is smaller" << endl;
				    break;
				}
				cout << "first is not smaller" << endl;				
				break;
			    }
			case 8:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber l(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber m(buffer);
				cout << "addition is: " << l+ m << endl;				
				break;
				}
			case 9:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber n(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>number;
				cout << "addition with number is: " << n + number << endl;				
				break;
			    }
			case 10:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber o(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber p(buffer);
				cout << "subtraction is: " << o - p << endl;				
				break;
				}
			case 11:
			    {
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber q(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>number;
				cout << "subtraction with number is: " << q - number << endl;
				break;
			    }
			case 12:
			    {   
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber r(buffer);
				cout<<"please enter a numbr:" <<endl;
				cin>>buffer;
				BigNumber s(buffer);
				if(s == r)
				{
				    cout << "equal!!" << endl;
				    break;
 				}
				cout << " not equal" << endl;		
				break;
		        }
			default:
				flag = 0;
				break;

		}
	}	
	return 0;
}

