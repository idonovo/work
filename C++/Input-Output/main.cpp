#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"

#include <string.h>

#define BIN_FILE_NAME "textBin.txt"
#define ASCII_FILE_NAME "textAscii.txt"


void OpenFile(virtIO_t* _vir, char rOw)
{
    string j(BIN_FILE_NAME);
    string p(&rOw);
    (*_vir).Open(j, p);
}

void WriteInt(virtIO_t* _vir, int number)
{    
    try
    {
    	*_vir << number << ' ';
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return;
    }
}

void WriteChar(virtIO_t* _vir, char x)
{    
    try
    {
    	*_vir << x<< ' ';
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return;
    }
}


void WriteFloat(virtIO_t* _vir, float x)
{    
    try
    {
    	*_vir << x << ' ';
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return;
    }
}

int ReadInt(virtIO_t* _vir)
{ 
    int number;
    try
    {
    	*_vir >> number;
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return -1;
    }
    return number;
} 

char ReadChar(virtIO_t* _vir)
{
    char letter;
    try
    {
    	*_vir >> letter;
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return '\0';
    }
    return letter;
}

float ReadFloat(virtIO_t* _vir)
{
    float number;
    try
    {
    	*_vir >> number;
    }
    catch(Status _st)
    {
    	cout << _st << "please change mode" << endl;
    	return -1;
    }
    return number;
}

int main (int argc, char const* argv[])
{
	int number, flag, select, res;
	char a;
	float q;
	char rOw[2];
	string j(BIN_FILE_NAME);
	string p(ASCII_FILE_NAME);
	virtIO_t* ptr;
	
	cout << "please enter 1 for binIO or 0 for asciiIO" << endl;
	cin >> select;
		
	cout<< "please choose option:" << endl;
	cout<< " r. read" << endl;
	cout<< " w. write " <<endl;
	cout<< " a. append " <<endl;
	cin>> rOw;
	string m = rOw;
	binIO_t y(j, m);
	asciiIO_t x(p, m);
	
	(select)? ptr = &y: ptr = &x;
		 
	while(flag)
	{
	
		cout<< "please choose option:" << endl;
		cout<< " 1. write int" <<endl;
		cout<< " 2. write char" <<endl;
		cout<< " 3. write double" <<endl;
		cout<< " 4. read int" <<endl;
		cout<< " 5. read char" <<endl;
		cout<< " 6. read double" <<endl;
		cout<< "else - exit " <<endl <<endl;
		
		cin >> res;
		
		switch(res)
		{
			case 1:
				{
					cout<< "please enter a number";
					cin>> number;
		            WriteInt(ptr, number);
					break;
				}
			case 2:
			    {
					cout<< "please enter a letter";
					cin>> a;
		            WriteChar(ptr, a);
					break;
				}
			case 3:
			    {
					cout<< "please enter a float number";
					cin>> q;
		            WriteFloat(ptr, q);
					break;
				}
			case 4:
				{				 
		            cout << "the number is" << ReadInt(ptr) <<endl;
					break;
				}
			case 5:
			    {
					cout << "the letter is" << ReadChar(ptr) <<endl; 
					break;
				}
			case 6:
			    {
					cout << "the number is" << ReadFloat(ptr) <<endl; 
					break;
				}
	        default:
	            {
			        flag = 0;
			        break;
	            }
	     }
	}   
}


