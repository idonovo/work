
<<<<<<< HEAD

#include <stdlib.h>
#include <string.h>

static int CheckParameters(const char* _str){

    if(NULL == _str)
	{
	    return 1;
	}
	return 0;

}

static void InsertByIndex(char* _str1, const char* _str2, size_t _index){
    
    _str1[_index] = _str2[_index];
    return; 
}


static int IsEndOfStr(const char* _str, size_t _index){

    if(_str[_index] == '\0'){
        return 1;
    }
    return 0;

}

/***************************************************************/
=======
#include <stdio.h>
#include <stdlib.h>


size_t MyStrlenItter(const char* _string){
	
	size_t i = 0;
	while(++*_string)	
	
	return i;

}

>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
static size_t StrlenRec(const char* _string, size_t _i){

	if(_string[_i] == '\0'){
		return _i;
	}	
	return StrlenRec(_string, _i + 1);
}

<<<<<<< HEAD
static int CompareRec(const char* _s1, const char* _s2, size_t _i){

	if (_s1[_i] != _s2[_i])
	{
		return _s1[_i] - _s2[_i];
	}
	
	if ((!IsEndOfStr(_s1, _i)) && (IsEndOfStr(_s2, _i)))
	{
		return _s1[_i];	
	} 
	
	if ((IsEndOfStr(_s1, _i)) && (!IsEndOfStr(_s2, _i)))
	{
		return 0 - _s2[_i];	
	} 
	
	if((IsEndOfStr(_s1, _i)) && (IsEndOfStr(_s2, _i)))
	{
	    return 0;
	}
	return CompareRec( _s1, _s2, _i + 1);
}

static char* NCopyRec(char* _destination, const char* _source, size_t _num){

    if(_num <= 0)
    {
        _destination[_num] = _source[_num];
        return _destination;
    }
    
    _destination[_num] = _source[_num];
    
    return NCopyRec(_destination, _source, _num-1);

}

static char* CopyRec(char* _destination, const char* _source, size_t i){

    if(_source[i] == '\0' || i > strlen(_destination)){
        _destination[i] = '\0';
        return _destination;
    }
    _destination[i] = _source[i];
    
    return CopyRec(_destination, _source, i+1);
}


/***************************************************************/
size_t Strlen(const char* _string){
	
	size_t i = 0;
	
	if(CheckParameters( _string))
	{
	    return i;
	}
	while(!IsEndOfStr(_string, i)){
	    ++i;
	}	
	
	return i;

}

size_t StrLenRec(const char* _string){

	size_t i = 0;
	if(NULL == _string)
	{
	    return i;
	}
	
	return StrlenRec(_string, i);
=======
size_t MyStrlenRec(const char* _string){

	size_t i = 0;
	
	return StrlenRec(_string, i);
}

int StrCompare(const char* _s1, const char* _s2){

	int i;

	
	for(i=0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i]){
			return str1[i] - str2[i];
		}
	}

	if (str2[i] != '\0')
	{
		return 0 - str2[i];	
	} 
	
	return 0;	
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
}

int StrCompare(const char* _s1, const char* _s2){

	size_t i;
	
<<<<<<< HEAD
	if(CheckParameters(_s1) && CheckParameters(_s2))
	{
		return -300;
    }
    
	if(CheckParameters(_s1))
=======
	if(NULL ==_s1)
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
	{
		return 0 - _s2[0];
	}
	
<<<<<<< HEAD
	if(CheckParameters(_s2))
	{
		return _s1[0];
	}	
=======
	if(NULL ==_s2)
	{
		return _s1[0];
	}
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
	
	for(i=0; _s1[i] != '\0'; i++)
	{
		if (_s1[i] != _s2[i])
		{
			return _s1[i] - _s2[i];
		}
	}

<<<<<<< HEAD
	if (!IsEndOfStr(_s2, i))
=======
	if (str2[i] != '\0')
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
	{
		return 0 - _s2[i];	
	} 
	
	return 0;	
}

<<<<<<< HEAD

=======
/***************************************************************/
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
int StrCompareRec(const char* _s1, const char* _s2){

	size_t i = 0;
	
<<<<<<< HEAD
	if(CheckParameters(_s1) && CheckParameters(_s2))
	{
		return -300;
    }
    
	if(CheckParameters(_s1))
=======
	if(NULL ==_s1)
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
	{
		return 0 - _s2[0];
	}
	
<<<<<<< HEAD
	if(CheckParameters(_s2))
=======
	if(NULL ==_s2)
>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
	{
		return _s1[0];
	}
	
	return CompareRec(_s1, _s2, i);
}	
	
<<<<<<< HEAD
char* StrCopy(char* _destination, const char* _source){

    size_t i = 0;
    
    if(CheckParameters(_destination) || CheckParameters(_source))
	{
		return NULL;
	}
	
    while(!IsEndOfStr(_source, i) || !IsEndOfStr(_destination, i))
    {
	   InsertByIndex(_destination , _source, i);
	   ++i;
	}	
    
    _destination[i] = '\0';
    return _destination; 
}

char* StrCopyRec(char* _destination, const char* _source){

    size_t i = 0;
    
      if(CheckParameters(_destination) || CheckParameters(_source))
	{
		return NULL;
	}
    
    return CopyRec(_destination, _source, i); 
}

char* StrNCopy(char* _destination, const char* _source, size_t _num){
    
    size_t i = 0;
    
    if(CheckParameters(_destination) || CheckParameters(_source))
	{
		return NULL;
	}
	
	if( _num > strlen(_source))
	{
		return NULL;
	} 
	
	while(i <= _num)
    {
	   InsertByIndex(_destination , _source, i);
	   ++i;
	}	
    _destination[i+1] = '\0'; 
    return _destination;
}


char* StrNCopyRec(char* _destination, const char* _source, size_t _num){
    
     if(CheckParameters(_destination) || CheckParameters(_source))
	{
		return NULL;
	}
	
	if( _num > strlen(_source))
	{
		return NULL;
	} 
	
	return NCopyRec(_destination, _source, _num);
	
}	

char* StrConcat(char* _destination, const char* _source){
    
 
    size_t destLength = strlen(_destination);
	size_t i;
	
	if(CheckParameters(_destination) || CheckParameters(_source))
	{
		return NULL;
	}
	
	for(i=0; i<destLength; i++)
	{
		InsertByIndex(_destination, _source, i);
	} 

	for(i = 0; _source[i] != '\0'; i++)
	{
		_destination[destLength] = _source[i];
		++destLength;
		
	} 
    _destination[i+1] = '\0';
    
	return _destination;
}

char* StrSubString(const char* _str, const char* _search){

	size_t i,x, tempIndex, flag, searchSize, strSize;
	char* ptr;
	
    if(CheckParameters(_str) || CheckParameters(_search))
	{
		return NULL;
	}
    
    searchSize = strlen(_search);
    strSize = strlen(_str);
    
    for(i = 0; i <= (strSize- searchSize); ++i)
    {     
        if(_str[i] == _search[0])
        {
            flag = 0;
            tempIndex =i;
            for(x =0; x < searchSize; ++x){
            
                if(_str[tempIndex] != _search[x])
                {
                    ++flag;
                }
                ++tempIndex;
            }
            if(flag == 0)
            {
              return (char*)(_str+i);  
            }
        }
    }  
    free(ptr);
    
    return NULL;
=======
static int CompareRec(const char* _s1, const char* _s2, size_t _i){

	if (_s1[_i] != _s2[_i])
	{
		return _s1[_i] - _s2[_i];
	}
	
	if (_s2[_i] == '\0' && _s1[_i] != '\0')
	{
		return _s1[_i];	
	} 
	
	if (_s2[_i] != '\0' && _s1[_i] == '\0')
	{
		return 0 - _s2[_i];	
	} 
	
	return CompareRec( _s1, _s2, ++_i);
}

int main








>>>>>>> 2d50d92ea4e4cd1b2ba5c9955d3f3727c4d9cd8d
}

