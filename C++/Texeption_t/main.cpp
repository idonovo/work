#include "Texeption_t.h"
#include <iostream>
using namespace std;


#define FILE_NAME "desktop/work/"

void foo()
{
    int number;
    const char* msg = "negative number!!";
    while(1)
    {
        cout << "please enter a number" << endl;
        cin >> number;
        int& t = number;
        if(number < 0)
        {
            TExeption_t<int> b(t);
            b.SetTExeption_t(FILE_NAME, msg, __LINE__);
            throw b;
            
        }
        cout << "good choice. try again" << endl;          
    }
}

int main()
{
   
    try
    {
        foo();
    }
    catch(TExeption_t<int> b)
    {
    	cout << b.m_msg << endl << b.m_line  << endl << b.m_file << endl << b.m_object << endl;
    }
    return 0;
    
}


