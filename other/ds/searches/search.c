
#include <stddef.h>
#include <stdio.h>


int LinearSearch(int* _array, int _size, int _num){
	
	size_t i;
	
	_array[_size] = _num;
	
	while(1){
	
		if(_array[i] == _num)
		{
			break;
		}
		i++;
	}
	
	if(i < _size){
		return 0;
	}
		return 1;
}

void Swap(int* _array, int i){

	int temp;
	
	if(i<0)
	{
		temp = _array[i];
		_array[i] = _array[i-1];
		_array[i-1] = temp;
	}
	return;
}

int ImpLinearSearch(int* _array, int _size, int _num){

	size_t i;
	
	_array[_size] = _num;
	
	while(1){
	
		if(_array[i] == _num)
		{
			break;
		}
		i++;
	}
	
	if(i < _size){
		Swap(_array , i);
		return 0;
	}
		return 1;
}


int ProportionalSearch(int* _array, int _nOfItems, int _num){

	int pivot, lowIndex = 0;
	int highIndex = _nOfItems-1;
	int varNOfItems;
	int min = _array[lowIndex];
	int averageGap = (_array[highIndex] - _array[lowIndex])/_nOfItems;
	
	pivot = (_num-min) /averageGap;
	 
	 while(lowIndex <=highIndex)
	 {			 	
	 	if(_array[pivot] == _num){
	 		return 0;
	 	}
	 	if(_array[pivot] < _num){
	 		lowIndex = pivot;
	 		varNOfItems =highIndex - lowIndex;
	 		min = _array[lowIndex];
	 		pivot += _num / ((_array[highIndex] - _array[lowIndex])/ varNOfItems);
	 		if(pivot == lowIndex){
	 			++pivot;
	 			++lowIndex;
	 		} 
	 	} 	 	  
		else if(_array[pivot] > _num){
	 		highIndex = pivot;
	 		varNOfItems = highIndex - lowIndex;
	 		pivot -= (_array[pivot] - _num) / ((_array[pivot] - _array[lowIndex]/ varNOfItems));
	 		if(pivot == highIndex){
	 			--pivot;
	 			--highIndex;
	 		} 
	 	}	
	 } 
	 return -1;
}
	
int main(){

	int array[6] = {10 ,20, 40, 60, 80, 100};
	
	if (ProportionalSearch(array, 6, 45) == 0)
	{
		printf("success!!\n");
		return 0;
	}  
	
	printf("failure!!");
	return 0;
}

/*
int JumpSearch(int* _ array, int _size, int _num){}*/
