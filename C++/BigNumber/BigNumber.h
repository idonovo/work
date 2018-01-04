

#include <iostream>
#include <string>
using namespace std;


class BigNumber
{

public:
    BigNumber();
	BigNumber(char* _number);
	BigNumber(unsigned int _number);
	BigNumber (BigNumber& _bigNumber);
	~BigNumber ();
	
	const string& GetNumber() const;
	
    BigNumber&operator=(const BigNumber& _number);
    BigNumber&operator=(const unsigned int _number);
    BigNumber&operator-(const BigNumber& _number);
    BigNumber&operator+(const BigNumber& _number);
    bool operator>(const BigNumber& _number) const;
    bool operator< (const BigNumber& _number) const;
    bool operator==(const BigNumber& _number) const;

private:
    void SetStrings(string& _short, string& _large, const BigNumber& _number, unsigned int* _largeLength, unsigned int* _shorterLength);
    
private:
	string m_number;
};

ostream& operator<<(ostream& _os, const BigNumber& _number);

istream& operator>>(istream& _os, BigNumber& _number);
