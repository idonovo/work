#include "memPage_t.h"
#include "memManager_t.h"
#include "memPool_t.h"
#include <iostream>
using namespace std;

int main()
{
    
    
    memPage_t a(10);
    char buf[32] = {'i' ,'0', 'o','d', 'o','d', 'o','d', 'o','d', 'o','d', 'o'};
    char buff[6];
    char bufff[10];
    
    
    cout<< a.WriteData(0, 2, buf)<< endl;
    cout<< a.WriteData(2, 2, buf)<< endl;
    cout<< a.WriteData(4, 2, buf)<< endl;
    cout<< a.ReadData(0, 6, buff)<< endl;
    buff[5] = '\0';
    cout<< buff << endl;
    try
    {
    	a.SetPos(8);
    }
    catch(char* _msg)
    {
    	cout << _msg << endl;
    }
    
    
    
    return 0;
}
