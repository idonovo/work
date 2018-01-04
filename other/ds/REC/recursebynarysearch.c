
#include  <stdio.h>

#define SIZE 20



int BinarySearch(int* arr, int number, int low, int high){
	
	int med;

	
		med= (low+high)/2;
		if(arr[med]==number)
			return med;
		else if (arr[med]<number)
		{
			return BinarySearch(arr, number, med+1, high);
		}	
		else
		{
			return BinarySearch(arr, number, low, med-1);
		}
		
	return -1;
}

int main(){
	
	int array[SIZE];
	int number, i, low=0;
	for (i=0; i<SIZE; i++){
		array[i] = i;
		
	}
	
	printf("please enter a number from the array:\n");
	scanf("%d", &number);
	printf("the number is in cell number %d\n", BinarySearch(array, number, low, SIZE-1));
	
	
}




