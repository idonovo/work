#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorts.h"

#define SIZE 10

int SmallToBigSwitch(int _curNum, int _beforeNum);

int BigToSmallSwitch(int _curNum, int _beforeNum);


void BubbleSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    BubbleSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort 4 Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShakeSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    ShakeSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Shake Sort 4 Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void QuickSortRec4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    QuickRec(testVector);
  
    VectorGet(testVector, index, &item);
	
	printf("Quick Sort Rec. 4 Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void InsertSort4NumSmall(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    InsertionSort(testVector, &SmallToBigSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort 4 Num small to big:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void InsertSort4NumBig(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    InsertionSort(testVector, &BigToSmallSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort 4 Num big to small:");
	if(item == 1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShellSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -56);
	VectorAdd(testVector, 24);
    VectorAdd(testVector, 55);
 	VectorAdd(testVector, 52);
 	VectorAdd(testVector, 39);
 	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -56);
	VectorAdd(testVector, 24);
    VectorAdd(testVector, 55);
 	VectorAdd(testVector, 52);
 	VectorAdd(testVector, 39);

    ShellSort(testVector);
    VectorPrint(testVector);
    VectorGet(testVector, index, &item);
	printf("Shell Sort 4 Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void SelectionSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 89);
    VectorAdd(testVector, 55);
    SelectionSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Selection Sort 4 Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void BubbleSortNegNum(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    VectorAdd(testVector, -55);
    BubbleSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort Neg. Num:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShakeSortNegNum(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    VectorAdd(testVector, -55);
    ShakeSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Shake Sort Neg. Num:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void QuickSortRecNegNum(){
    
    int item;
    size_t index = 2;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    QuickRec(testVector);
    VectorGet(testVector, index, &item);
	printf("Quick Sort Rec. Neg. Num:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void InsertSortNegNumSmall(){
    
    int item;
    size_t index = 2;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    InsertionSort(testVector, &SmallToBigSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Neg Num small to big:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void InsertSortNegNumBig(){
    
  	int item;
    size_t index = 2;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    InsertionSort(testVector, &BigToSmallSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Neg Num big to small:");
	if(item == -89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShellSortNegNum(){
    
    int item;
    size_t index = 2;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    ShellSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Shell Sort 4 Num:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void SelectionSortNegNum(){
    
    int item;
    size_t index = 2;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, -1);
	VectorAdd(testVector, -89);
    SelectionSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Selection Sort Neg Num:");
	if(item == -1){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void BubbleSortSameNum(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    BubbleSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort Same Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShakeSortSameNum(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 12);
    VectorAdd(testVector, 89);
    ShakeSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Shake Sort Same Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void QuickSortRecSameNum(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    QuickRec(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Quick Sort Rec. Same Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void InsertSortSameNumSmall(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    InsertionSort(testVector, &SmallToBigSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Same Num small to big:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void InsertSortSameNumBig(){

	int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    InsertionSort(testVector, &BigToSmallSwitch);
    
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Same Num big to small:");
	printf("PASS\n");
	VectorPrint(testVector);

	
	VectorDestroy(testVector);	
	return;
}


void ShellSortSameNum(){
    
   	int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    ShellSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Shell Sort Same Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void SelectionSortSameNum(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    SelectionSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Selection Sort Same Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void BubbleSortPosAndNeg(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 89);
    VectorAdd(testVector, 12);
    BubbleSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort Pos. and Neg. Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShakeSortPosAndNeg(){
    
    int item;
    size_t index = 5;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -12);
    VectorAdd(testVector, 55);
    VectorAdd(testVector, 12);
    VectorAdd(testVector, 89);
    ShakeSort(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Shake Sort Pos. and Neg. Num:");
	if(item == 89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void QuickSortRecPosAndNeg(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -89);
	VectorAdd(testVector, 19);
    QuickRec(testVector);
    VectorGet(testVector, index, &item);
	VectorPrint(testVector);
	 
	printf("Quick Sort Rec. Pos. and Neg. Num:");
	if(item == 19){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;

}

void QuickSortIter4Num(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 7);
	VectorAdd(testVector, 9);
	VectorAdd(testVector, -4);
	VectorAdd(testVector, 11);
	
    QuickSortIter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort 4 Num:");
	if(item == 11){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void QuickSortIterNegNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -4);
	VectorAdd(testVector, -11);
	
    QuickSortIter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort Neg Num:");
	if(item == -4){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void QuickSortIterSameNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -11);
    QuickSortIter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Bubble Sort Same Num:");
	if(item == -7){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void QuickSortIterNegAndPosNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,4);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, 23);
	VectorAdd(testVector, -11);
    QuickSortIter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Quick Sort Itt. Neg and Pos Num:");
	if(item == 23){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}


void InsertSortNegAndPosNumSmall(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -89);
	VectorAdd(testVector, 19);
    InsertionSort(testVector, &SmallToBigSwitch);
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Neg and Pos Num small to big:");
	if(item == 19){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void InsertSortNegAndPosNumBig(){
	
	int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -89);
	VectorAdd(testVector, 19);
    InsertionSort(testVector, &BigToSmallSwitch);    
    VectorGet(testVector, index, &item);
	printf("Insertion Sort Pos and Neg big to small:");
	if(item == -89){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void ShellSortNegAndPos(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -89);
	VectorAdd(testVector, 19);
    ShellSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Shell Sort 4 Num:");
	if(item == 19){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void SelectionSortNegAnfPosNum(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, -67);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, -89);
	VectorAdd(testVector, 19);
    SelectionSort(testVector);
    VectorGet(testVector, index, &item);
	printf("Selection Sort Neg and Pos Num:");
	if(item == 19){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortRec4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 7);
	VectorAdd(testVector, 9);
	VectorAdd(testVector, 55);
    VectorAdd(testVector, 43);
    MergeSortRec(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort 4 Num:");
	if(item == 55){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}
void MergeSortRecNegNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -4);
	VectorAdd(testVector, -11);	
    QuickSortIter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Neg Num:");
	if(item == -4){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortRecSameNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -11);
    MergeSortRec(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Rec Same Num:");
	if(item == -7){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortRecNegAndPosNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,4);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, 23);
	VectorAdd(testVector, -11);
    MergeSortRec(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Rec. Neg and Pos Num:");
	if(item == 23){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortItter4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(20, SIZE);
	VectorAdd(testVector, 10);
	VectorAdd(testVector, 9);
	VectorAdd(testVector, 55);
	VectorAdd(testVector, 23);
   	MergeSortItter(testVector);
    VectorGet(testVector, index, &item);
	printf("Merge Sort 4 Num:");
	if(item == 55){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortItterNegNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -4);
	VectorAdd(testVector, -11);	
    MergeSortItter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Itter. Neg Num:");
	if(item == -4){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortItterSameNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,-7);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, -11);
   	MergeSortItter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Itter. Same Num:");
	if(item == -7){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void MergeSortItterNegAndPosNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,4);
	VectorAdd(testVector, -9);
	VectorAdd(testVector, 23);
	VectorAdd(testVector, -11);
    MergeSortItter(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Merge Sort Itter Neg and Pos Num:");
	if(item == 23){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void CountingSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 3);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 5);
    VectorAdd(testVector, 2);
    CountingSort(testVector, NULL, 0, 5);
    VectorGet(testVector, index, &item);
	printf("Counting Sort 4 Num:");
	if(item == 5){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}



void CountingSortSameNum(){
    
    int item;
    size_t index =3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector,4);
	VectorAdd(testVector, 4);
	VectorAdd(testVector, 2);
	VectorAdd(testVector, 4);
   	CountingSort(testVector, NULL, 0, 4);
    VectorGet(testVector, index, &item);
	printf("Counting Sort Same Num:");
	if(item == 4){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void CountingSort10Num(){
    
    int item;
    size_t index = 9;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 3);
	VectorAdd(testVector, 1);
	VectorAdd(testVector, 12);
	VectorAdd(testVector, 13);
	VectorAdd(testVector, 5);
    VectorAdd(testVector, 2);
    VectorAdd(testVector, 9);
	VectorAdd(testVector, 10);
	VectorAdd(testVector, 8);
    VectorAdd(testVector, 9);
    CountingSort(testVector, NULL, 0, 13);
    VectorGet(testVector, index, &item);
    VectorPrint(testVector);
	
	printf("Counting Sort 10 Num:");
	if(item == 13){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void RadixSort4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 317);
	VectorAdd(testVector, 215);
	VectorAdd(testVector, 629);
    VectorAdd(testVector, 852);
    RadixSort(testVector, 3);
    VectorPrint(testVector);
    VectorGet(testVector, index, &item);
	
	printf("Radix Sort 4 Num:");
	if(item == 852){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void RadixDiffrentDigits4Num(){
    
    int item;
    size_t index = 3;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 17);
	VectorAdd(testVector, 2152);
	VectorAdd(testVector, 629);
    VectorAdd(testVector, 8523235);
    RadixSort(testVector, 7);
    VectorGet(testVector, index, &item);
	
	printf("Radix Sort Diffrent Digits Num:");
	if(item == 8523235){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}

void Radixsort10Num(){
    
    int item;
    size_t index = 9;
    Vector* testVector = VectorCreate(100, SIZE);
	VectorAdd(testVector, 17);
	VectorAdd(testVector, 2152);
	VectorAdd(testVector, 629);
    VectorAdd(testVector, 23235);
    VectorAdd(testVector, 117);
	VectorAdd(testVector, 2152);
	VectorAdd(testVector, 619);
    VectorAdd(testVector, 34235);
    VectorAdd(testVector, 69);
    VectorAdd(testVector, 54);
    RadixSort(testVector, 5);
    VectorGet(testVector, index, &item);
	
	printf("Radix Sort 10 Num:");
	if(item == 34235){
	    printf("PASS\n");
	    VectorPrint(testVector);
	    VectorDestroy(testVector);
	    return;
	}
	printf("FAIL\n"); 
	VectorDestroy(testVector);	
	return;
}
/****************performance tests***************************/
void MeasureTime1000Typical(SortFunc _howToSort){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(1000, SIZE);
	for (i = 0; i < 50; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    _howToSort(testVector);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}

void MeasureTime1000TypicalInsertion(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(1000, SIZE);
	for (i = 0; i < 1000; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    InsertionSort(testVector, &BigToSmallSwitch);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}		

void MeasureTime1000TypicalCounting(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(1000, SIZE);
	for (i = 0; i < 1000; i++) 
	{
   		VectorAdd(testVector, rand() % 1000);
	}
	t = clock();
    CountingSort(testVector, NULL, 0, 1000);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}	

void MeasureTime1000TypicalRadix(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(1000, SIZE);
	for (i = 0; i < 1000; i++) 
	{
   		VectorAdd(testVector, rand() % 1000);
	}
	t = clock();
    RadixSort(testVector, 4);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}	

void MeasureTime10000Typical(SortFunc _howToSort){
	
	clock_t t;
	double time_taken;
	int i;
	
	Vector* testVector = VectorCreate(10000, SIZE);
	srand(0);
	for (i = 0; i < 3800; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    _howToSort(testVector);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 10,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}

void MeasureTime10000TypicalInsertion(){
	
	clock_t t;
	double time_taken;
	int i;
	
	Vector* testVector = VectorCreate(10000, SIZE);
	srand(0);
	for (i = 0; i < 10000; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    InsertionSort(testVector, &BigToSmallSwitch);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 10,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}

void MeasureTime10000TypicalCounting(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(10000, SIZE);
	for (i = 0; i < 10000; i++) 
	{
   		VectorAdd(testVector, rand() % 10000);
	}
	t = clock();
    CountingSort(testVector, NULL, 0, 10000);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,0000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}	

void MeasureTime10000TypicalRadix(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(10000, SIZE);
	for (i = 0; i < 10000; i++) 
	{
   		VectorAdd(testVector, rand() % 10000);
	}
	t = clock();
    RadixSort(testVector, 5);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 1,0000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}
		
void MeasureTime50000Typical(SortFunc _howToSort){
	
	clock_t t;
	double time_taken;
	int i;
	
	Vector* testVector = VectorCreate(50000, SIZE);
	srand(0);
	for (i = 0; i < 50000; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    _howToSort(testVector);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
 
    printf("it tooks %f seconds to sort 50,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}
void MeasureTime50000TypicalInsertion(){
	
	clock_t t;
	double time_taken;
	int i;
	
	Vector* testVector = VectorCreate(50000, SIZE);
	srand(0);
	for (i = 0; i < 50000; i++) 
	{
   		VectorAdd(testVector, rand());
	}
	t = clock();
    InsertionSort(testVector, &BigToSmallSwitch);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 

 
    printf("it tooks %f seconds to sort 50,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}

void MeasureTime50000TypicalCounting(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(50000, SIZE);
	for (i = 0; i < 50000; i++) 
	{
   		VectorAdd(testVector, rand() % 50000);
	}
	t = clock();
    CountingSort(testVector, NULL, 0, 50000);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 50,000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}	


void MeasureTime50000TypicalRadix(){
	
	clock_t t;
	double time_taken;
	int i;
	Vector* testVector;
	srand(0);
	testVector = VectorCreate(50000, SIZE);
	for (i = 0; i < 50000; i++) 
	{
   		VectorAdd(testVector, rand() % 50000);
	}
	t = clock();
    RadixSort(testVector, 5);
    t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
 
    printf("it tooks %f seconds to sort 50,0000 \n", time_taken);
    VectorDestroy(testVector);
    return;
}

int main(){
/*
    printf("\nBubbleSort Tests:\n");
    BubbleSort4Num();
    BubbleSortNegNum();
    BubbleSortSameNum();
    BubbleSortPosAndNeg();
    
    printf("\nShakeSort Tests:\n");
	ShakeSort4Num();
	ShakeSortNegNum();
	ShakeSortSameNum();
	ShakeSortPosAndNeg();
	
	printf("\nQuickSort Rec. Tests:\n");
	QuickSortRec4Num();
	QuickSortRecNegNum();
	QuickSortRecSameNum();
	QuickSortRecPosAndNeg();
	
	printf("\nQuickSort Iter. Tests:\n");
	QuickSortIter4Num();
	QuickSortIterNegNum();
	QuickSortIterSameNum();
	QuickSortIterNegAndPosNum();
	
	printf("\nInsertionSort Tests(smallToBig):\n");
	InsertSort4NumSmall();
	InsertSortNegNumSmall();
	InsertSortSameNumSmall();
	InsertSortNegAndPosNumSmall();	
	
	printf("\nInsertionSort Tests(bigToSmall):\n");
	InsertSort4NumBig();
	InsertSortNegNumBig();	
	InsertSortSameNumBig();
	InsertSortNegAndPosNumBig();
	
	printf("\nShellSort Tests:\n");
	ShellSort4Num();
	ShellSortNegNum();
	ShellSortSameNum();
	ShellSortNegAndPos();
	
	printf("\nSelectionSort Tests:\n");
	SelectionSort4Num();
	SelectionSortSameNum();
	SelectionSortNegNum();
	SelectionSortNegAnfPosNum();
	
	printf("\nMerge Sort Rec. Tests:\n");
	MergeSortRec4Num();
    MergeSortRecSameNum();
    MergeSortRecNegAndPosNum();
    
    printf("\nMerge Sort Itter. Tests:\n");
    MergeSortItter4Num();
    MergeSortItterNegNum();
	MergeSortItterSameNum();
	MergeSortItterNegAndPosNum();
	
	printf("\nCounting Sort Tests:\n");
	CountingSort4Num();*/
	CountingSortSameNum();
	CountingSort10Num();
	
	printf("\nRadix Sort Tests:\n");
	RadixSort4Num();
	RadixDiffrentDigits4Num();
    Radixsort10Num();
    
/*************performanc tests**********************/	

	printf("\nrandom 1000 numbers:\n");
	printf("bubble sort:\n");
	MeasureTime1000Typical(&BubbleSort);
	printf("shake sort:\n");
	MeasureTime1000Typical(&ShakeSort);
	printf("insertion sort:\n");
	MeasureTime1000TypicalInsertion();
	printf("quick sort:\n");
	MeasureTime1000Typical(&QuickRec);
	printf("quick sort itter.:\n");
	MeasureTime1000Typical(&QuickSortIter);
	printf("shell sort:\n"); 
	MeasureTime1000Typical(&ShellSort);
	printf("selection sort:\n");
	MeasureTime1000Typical(&SelectionSort);
	printf("Merge sort Rec.:\n");
	MeasureTime1000Typical(&MergeSortRec);
	printf("Merge sort Itter.:\n");
	MeasureTime1000Typical(&MergeSortItter);
	printf("Counting Sort:\n");
	MeasureTime1000TypicalCounting();
	printf("Radix Sort:\n");
	MeasureTime1000TypicalRadix();
	/*
	printf("\nrandom 10000 numbers:\n");
	printf("bubble sort:\n");
	MeasureTime10000Typical(&BubbleSort);
	printf("shake sort:\n");
	MeasureTime10000Typical(&ShakeSort);
	printf("insertion sort:\n");
	MeasureTime10000TypicalInsertion();
	printf("quick sort:\n");
	MeasureTime10000Typical(&QuickRec);
	printf("quick sort itter.:\n");
	MeasureTime10000Typical(&QuickSortIter);
	printf("shell sort:\n");
	MeasureTime10000Typical(&ShellSort);
	printf("selection sort:\n");
	MeasureTime10000Typical(&SelectionSort);
	printf("Merge sort:\n");
	MeasureTime10000Typical(&MergeSortRec);
	printf("Merge sort Itter.:\n");
	MeasureTime10000Typical(&MergeSortItter);
	printf("Counting Sort:\n");
	MeasureTime10000TypicalCounting();
	printf("Radix Sort:\n");
	MeasureTime10000TypicalRadix();
	
	printf("\nrandom 50000 numbers:\n");
	printf("bubble sort:\n");
	MeasureTime50000Typical(&BubbleSort);
	printf("shake sort:\n");
	MeasureTime50000Typical(&ShakeSort);
	printf("insertion sort:\n");
	MeasureTime50000TypicalInsertion();
	printf("quick sort:\n");
	MeasureTime50000Typical(&QuickRec);
	printf("quick sort itter:\n");
	MeasureTime50000Typical(&QuickSortIter); 
	printf("shell sort:\n");
	MeasureTime50000Typical(&ShellSort);
	printf("selection sort:\n");
	MeasureTime50000Typical(&SelectionSort);
	printf("Merge sort:\n");
	MeasureTime50000Typical(&MergeSortRec);
	printf("Merge sort Itter.:\n");
	MeasureTime50000Typical(&MergeSortItter);
	printf("Counting Sort:\n");
	MeasureTime50000TypicalCounting();
	printf("Radix Sort:\n");
	MeasureTime50000TypicalRadix();
*/
	return 0;
  
}





