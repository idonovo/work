#include <stdio.h>
#include <algorithm>

#include "BigNumber.h"


ostream& operator<<(ostream& _os, const BigNumber& _number)
{
	_os<< _number.GetNumber();
	return _os;
}

istream& operator>>(istream& _os, BigNumber& _number)
{
	char buffer[1024];
	_os >> buffer;
	_number = atoi(buffer);
	return _os;
}

/***************************************************************************/
BigNumber:: BigNumber(){}

BigNumber:: ~BigNumber(){}

BigNumber::BigNumber(char* _number)
{
	if(_number)
	{
		m_number = _number;
	}
}

BigNumber::BigNumber(unsigned int _number)
{
	char buffer[16];
	sprintf(buffer, "%d", _number);
	m_number = buffer; 		
}

BigNumber::BigNumber (BigNumber& _bigNumber)
{
	m_number = _bigNumber.m_number;
}

const string& BigNumber::GetNumber() const
{
	return m_number;
}



BigNumber& BigNumber::operator=(const BigNumber& _number)
{
	if(this != &_number)
	{
		m_number = _number.m_number;
	}
	return *this;
}

BigNumber& BigNumber::operator=(const unsigned int _number)
{
	if(_number != (unsigned int)stoi(m_number))
	{
		char buffer[16];
		sprintf(buffer, "%d", _number);
		m_number = buffer; 
	}
	return *this; 
}

bool BigNumber::operator>(const BigNumber& _number) const
{
	unsigned int myLen = m_number.length();
	unsigned int compareLen = _number.m_number.length();
	
	if(myLen != compareLen)
	{
		return (myLen > compareLen);
	}
	
	return (m_number.compare(_number.m_number) > 0);
}
 
bool BigNumber::operator<(const BigNumber& _number)const
{
	unsigned int myLen = m_number.length();
	unsigned int compareLen = _number.m_number.length();
	
	if(myLen != compareLen)
	{
		return (myLen < compareLen);
	}
	
	return (m_number.compare(_number.m_number) < 0);
}
 
bool BigNumber::operator==(const BigNumber& _number) const
{
	 return (0 == m_number.compare(_number.m_number));
}

BigNumber& BigNumber::operator+(const BigNumber& _number)
{
	unsigned int shorterLength, largeLength, carry = 0;
	string shortString, largeString, returnString;
	
	SetStrings(shortString, largeString, _number, &largeLength, &shorterLength);
	
	for(unsigned int i = 0; i < shorterLength; i += 1)
	{
		unsigned int sum = (shortString[i] - '0') + (largeString[i] - '0') + carry;
		returnString.push_back(sum % 10 + '0');
		carry = sum/10; 
	}
	
	for(unsigned int x = shorterLength; x < largeLength; x += 1)
	{
		unsigned int sum = (largeString[x] - '0') + carry;
		returnString.push_back(sum % 10 + '0');
		carry = sum/10; 
	}
	
	if(carry > 0)
	{
		returnString.push_back(carry + '0');
	}
	
	reverse(returnString.begin(), returnString.end());
	
	m_number = returnString;
	
	return *this;
}

void BigNumber::SetStrings(string& _short, string& _large, const BigNumber& _number, unsigned int* _largeLength, unsigned int* _shorterLength)
{
	if(*this >_number)
	{
		*_shorterLength = _number.m_number.length();
		_short = _number.m_number;
		*_largeLength= m_number.length();
		_large= m_number;
	
	}
	else
	{
		*_shorterLength = m_number.length(); 
		_short =  m_number;
		*_largeLength= _number.m_number.length();
		_large= _number.m_number;
	}
	
	reverse(_large.begin(), _large.end());
	reverse(_short.begin(), _short.end());
}

BigNumber& BigNumber::operator-(const BigNumber& _number)
{
	unsigned int shorterLength, largeLength, carry = 0;
	string shortString, largeString, returnString;
	
	SetStrings(shortString, largeString, _number, &largeLength, &shorterLength);
	
	for(unsigned int i = 0; i < shorterLength; i += 1)
	{
		int sum = (largeString[i] - '0') - (shortString[i] - '0') - carry;
		if(sum < 0)
		{
			sum += 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		returnString.push_back(sum + '0');
	}
	

	for(unsigned int x = shorterLength; x < largeLength; x += 1)
	{
		
		if(largeString[x] == '0' && carry == 1)
		{
			largeString[x] = '9';
			--largeString[x+1]; 
		}
		int sum1 = ((largeString[x] - '0') - carry);
		returnString.push_back(sum1 + '0');
		carry =0;
	}
	
	
	reverse(returnString.begin(), returnString.end());
	
	m_number = returnString;
	
	return *this;
}
