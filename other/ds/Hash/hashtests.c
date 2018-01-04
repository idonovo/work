/*           HASH API functions tests - by Ido Naveh            */   

# include <stdio.h>
# include <stdlib.h>

# include "hash.h"


#define MAGIC 7377175
#define SIZE 10

void IsCreate(){
	
	Hash* testHash = HashCreate(SIZE);
    printf("Is Create:");
	if (testHash != NULL){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	return;
}	


void IsInsert(){
	
	Hash* testHash = HashCreate(SIZE);
    printf("Is Insert:");
	if(HashInsert(testHash, SIZE) == ERR_OK){
		printf("PASS\n");
		HashPrint(testHash);
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}	

void IsInsertSameIndexNumber(){
	
	Hash* testHash = HashCreate(SIZE);
    printf("Is Insert Same Index Number:");
    HashInsert(testHash, 2);
    HashInsert(testHash, 1);
	if(HashInsert(testHash, 14) == ERR_OK){
		printf("PASS\n");
		HashPrint(testHash);
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}	

void IsInsertSameNumber(){
	
	Hash* testHash = HashCreate(SIZE);
    printf("Is Insert Same Number:");
    HashInsert(testHash, 2);
    HashInsert(testHash, 1);
	if(HashInsert(testHash, 2) == ERR_INVALID_NUM){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}	

void IsInsertNegativeNumber(){
	
	Hash* testHash = HashCreate(SIZE);
    printf("Is Insert Negative Number:");
    HashInsert(testHash, 2);
    HashInsert(testHash, 1);
	if(HashInsert(testHash, -2) == ERR_INVALID_NUM){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}	

void IsInsertBeyondSize(){
	Hash* testHash = HashCreate(3);
    printf("Is Insert Beyond Size:");
    HashInsert(testHash, 2);
    HashInsert(testHash, 1);
    HashInsert(testHash, 3);
	if(HashInsert(testHash, 4) == ERR_OVERFLOW){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsInsertMultipleSameIndex(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Insert Beyond Size:");
    HashInsert(testHash, 1);
    HashInsert(testHash, 12);
    HashInsert(testHash, 23);
    HashInsert(testHash, 2);
    HashInsert(testHash, 13);
    HashInsert(testHash, 24);
	if(HashInsert(testHash, 4) == ERR_OK){
		printf("PASS\n");
		HashPrint(testHash);
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsRemove(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Remove:");
    HashInsert(testHash, 1);
    HashInsert(testHash, 8);  
	if(HashRemove(testHash, 1) == ERR_OK){
		printf("PASS\n");
		HashPrint(testHash);
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsRemoveSameNumber(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Remove:");
    HashInsert(testHash, 1);
    HashInsert(testHash, 8); 
    HashRemove(testHash, 1);
	if(HashRemove(testHash, 1) == ERR_INVALID_NUM){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsRemoveNotExistNumber(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Remove Not Exist Number");
    HashInsert(testHash, 1);
    HashInsert(testHash, 8); 
	if(HashRemove(testHash, 7) == ERR_INVALID_NUM){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsRemoveEmptyHash(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Remove From Empty Hash: "); 
	if(HashRemove(testHash, 7) == ERR_UNDERFLOW){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsHashFound(){
	Hash* testHash = HashCreate(SIZE);
	HashInsert(testHash, 12);
    HashInsert(testHash, 23);
    HashInsert(testHash, 2);
    printf("Is Hush Found: "); 
	if(HashIsFound(testHash, 23) == 1){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsHashNotExistFound(){
	Hash* testHash = HashCreate(SIZE);
	HashInsert(testHash, 12);
    HashInsert(testHash, 23);
    HashInsert(testHash, 2);
    printf("Is Hush Not Exist Found: "); 
	if(HashIsFound(testHash, 5) == 0){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsReturnNumOfItems(){
	Hash* testHash = HashCreate(SIZE);
	HashInsert(testHash, 12);
    HashInsert(testHash, 23);
    HashInsert(testHash, 2);
    printf("Is Return Num of Items: "); 
	if(HashNumOfItems(testHash) == 3){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}

void IsReturnNumOfItemsEmptyHash(){
	Hash* testHash = HashCreate(SIZE);
    printf("Is Return Num of Items Empty Hash: "); 
	if(HashNumOfItems(testHash) == 0){
		printf("PASS\n");
		HashDestroy(testHash);
		return;
	}
	printf("FAIL\n");
	HashDestroy(testHash);
	return;
}
	
void MultipuleInsertandRemove(){

    int i;
    Hash* testHash = HashCreate(SIZE);
    for(i=0; i<SIZE; i++){
    
	    HashInsert(testHash, 2*i+SIZE);
    }
    
    HashPrint(testHash);
      for(i=0; i< SIZE/2 ; i++){
    
	    HashRemove(testHash, 2*i+16);
    }
    HashPrint(testHash);
      for(i=0; i< SIZE/2 ; i++){
    
	    HashInsert(testHash, (i*2));
    }
    HashPrint(testHash);
    return;
}
 
/* additional tests:
    DoubleDestroy
    IsReturnHashCapacity();
    IsReturnHashAverageCollisions();
    IsReturnHashMaxCollisions(); 
    NULL Tests
    */
int main(){

	IsCreate();
	
	IsInsert();
	IsInsertSameIndexNumber();
	IsInsertSameNumber();
	IsInsertNegativeNumber();
	IsInsertBeyondSize();
	IsInsertMultipleSameIndex();
	
	IsRemove();
	IsRemoveSameNumber();
	IsRemoveNotExistNumber();
	IsRemoveEmptyHash();
	
	IsHashFound();
	IsHashNotExistFound();
	
	IsReturnNumOfItems();
	IsReturnNumOfItemsEmptyHash();
	
	MultipuleInsertandRemove();
	
	
	
	
	return 0;
}

/*_________________BuildHeap Tests________________*/
