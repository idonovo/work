
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

ostream& prnLine(ostream& os)
{
	return os << endl << "|_______________________|" << endl;
}

int main (int argc, char const* argv[])
{
	string name;
	int id;
	
	ofstream inpFile("file");
	
	inpFile <<  prnLine << setw(10) <<"ID     " << " | " <<  setw(10) << "NAME     " << prnLine;
	
	cout<< "please enter number of persons" << endl;
	int flag; 
	cin >> flag; 
		
	while(flag)
	{
		cout<< "please enter name" << endl;
		cin >> name;
	
		cout<< "please enter id" << endl;
		cin >> id;
		while(!cin.good())
		{
			cin.clear();
			cin.ignore();
			cout<< "please enter a number" << endl;
			cin >> id;
		}				
		inpFile << "|" << setw(10)  <<left  << setfill('-') << id << " | " <<  setw(10) << left << name << setfill('-') << "| " << prnLine;
		--flag;
	}
	
	return 0;
}

