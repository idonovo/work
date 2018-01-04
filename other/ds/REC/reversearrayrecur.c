#include  <stdio.h>

#define SIZE 10
#define LOW 0


char* Reverse(char* _array, int _low, int _size){
	
	char temp;
	
		if(_low< _size){
		temp = _array[_low];
		_array[_low] = _array[_size];
		_array[_size] = temp;
		return Reverse(_array, _low+1 , _size-1);
		}
	
	return _array;

}

int main(){
	char chars[10];
	printf("please enter a series of 10 chars:");
	scanf("%s", chars);
	char* reversechars = Reverse(chars, LOW, SIZE-1);
	
	printf("the reverse order is %s\n", reversechars);
	
	return 0;
	
			

}
	

