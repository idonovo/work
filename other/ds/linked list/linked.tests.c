/*            linked list API functions tests - by Ido Naveh            */       

# include <stdio.h>
# include <stdlib.h>

# include "linked.h"

#define SIZE 10
#define INVALIDKEY 15

/* _________________ListInsertHead Tests________*/

void Ishead(Person* _head, Person* _p){
    
    Person* test= ListInsertHead(_head, _p);
    printf("Is head test:");
    if(test-> m_id != SIZE){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;

}

void Istail(Person* _head, Person* _p){
    
    Person* test1= ListInsertHead(_head, _p);
    Person* test2 = test1->m_next;
    printf("Is tail test:");
    if(test2-> m_id != SIZE+1){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}

void SameKey(Person* _head, Person* _p){
    
    Person* test1= ListInsertHead(_head, _p);
    printf("Is reject same key:");
    if(test1->m_next != NULL){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}
/* _________________ListInsertHead Tests________*/

void IsReturnHead(Person* _head, Person* _p){
    
    Person** item;
    Person* test1= ListInsertHead(_head, _p);
    Person* test2= ListRemoveHead(_p, item);
   
    printf("Is return head test:");
    if(item = NULL){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}

void IsHeadRemoved(Person* _head, Person* _p, Person** _item){
    
    Person* test1= ListInsertHead(_head, _p);
    Person* test2= ListRemoveHead(_p, _item);
   
    printf("Is head removed test:");
    if(test2->m_id !=_head->m_id ){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}

void IsHeadNULL(Person* _head, Person* _p, Person** _item){
    
    Person* test1;
    Person* test2;
    
    test1 = ListInsertHead(_head, _p);
    _p = NULL;
    test2 = ListRemoveHead(_p, _item);
   
    printf("Is head removed test:");
    if(test2 != NULL ){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}

/* _________________InsertByKey Tests_______________________________*/
void IsInsertByKey(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKey(_x, _z->m_id, _z);
    printf("Is insert by key test: pass\n");
    PrintList(test1);
    printf("\n");
    return;
}

void IsInsertFirst(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKey(_x, _z->m_id, _z);
    printf("Is insert by key first test: pass\n");
    PrintList(test1);
    printf("\n");
    return;
}

void IsInsertLast(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKey(_x, _z->m_id, _z);
    printf("Is insert by key last test: pass\n");
    PrintList(test1);
    printf("\n");
    return;
}

void IsInsertNULLHead(Person* _head){
   
    Person* test1 = NULL;
    Person* test2 = ListInsertByKey(test1, _head->m_id, _head);   
    printf("Is insert by key NULL head test:");
    if(test2->m_id != _head->m_id){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}

/* _________________InsertByKeyRec Tests_______________________________*/

void IsInsertByKeyRec(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKeyRec(_x, _z->m_id, _z);
    
    printf("Is insert by key rec. test: pass\n");
    PrintList(test1);
    printf("\n");
    return;
}

void IsInsertFirstRec(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKeyRec(_x, _z->m_id, _z);
    printf("Is insert first rec. test: pass\n");
    PrintList(test1);
    printf("\n");
    return;
}

void IsInsertLastRec(Person* _head, Person* _p, Person* _x, Person* _z){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x);    
    test1 = ListInsertByKeyRec(_x, _z->m_id, _z);
    printf("Is insert by key rec. last test: pass\n");
    PrintList(test1); 
    printf("\n");
    return;
}

void IsInsertRecNULLHead(Person* _head){
   
    Person* test1 = NULL;
    Person* test2 = ListInsertByKeyRec(test1, _head->m_id, _head);   
    printf("Is insert by key rec. NULL head test:");
    if(test2->m_id != _head->m_id){
        printf("fail\n");
        return;
    }
    printf("pass\n");
    return;
}


/* _________________RemoveByKey Tests_______________________________*/
void IsRemoveByKey(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove by key test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKey(_x, _p->m_id, _item);
    PrintList(test1);
    printf("\n");
    return;
}

void IsRemoveByKeyFirst(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove by key first test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKey(_x, _x->m_id, _item);
    PrintList(test1);
    printf("\n");
    return;
}

void IsRemoveByKeyLast(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove by key last test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKey(_x, _head->m_id, _item);
    PrintList(test1);
    printf("\n");
    return;
}

void IsRemovInvalidKey(Person* _head, Person* _p, Person* _x, Person** _item){

    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove invalid key test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKey(_x, INVALIDKEY , _item);
    PrintList(test1);
    printf("\n");
    return;

}
/* _________________RemoveByKeyRec Tests_______________________________*/
void IsRemoveByKeyRec(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove by key rec. test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKeyRec(_x, _p->m_id, _item);
    PrintList(test1);
    printf("\n");
    return;
}

void IsRemoveByKeyFirstRec(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove by key first rec. test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKeyRec(_x, _x->m_id, _item);
    PrintList(test1);
    printf("\n");
    return;
}

void IsRemoveLastRec(Person* _head, Person* _p, Person* _x, Person** _item){
    
    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); ;
    printf("Is remove by key rec. last test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKeyRec(_x, _head->m_id, _item);
    PrintList(test1);
    printf("\n");
}

void IsRemovInvalidKeyrec(Person* _head, Person* _p, Person* _x, Person** _item){

    Person* test1 = ListInsertHead(_head, _p);
    test1 = ListInsertHead(_p, _x); 
    printf("Is remove invalid key rec. test: pass\n");
    PrintList(test1);
    printf("\n");
    test1 = ListRemoveByKeyRec(_x, INVALIDKEY , _item);
    PrintList(test1);
    printf("\n");
    return;

}

void IsGetLast(Person* _head, Person* _p, Person* _x){
 	
 	Person* test1 = ListInsertHead(_head, _p);
 	Person* test2;
    test1 = ListInsertHead(_p, _x);
    test2 = GetLast(test1);
    printf("Is Get Last rec. test: pass\n");
    PrintList(test1);
    printf("\n%d\n", test2->m_id);
}

int main(){
    
    int i;
    Person** item =malloc(sizeof(Person)); 
    Person* array[5];
    for(i=0; i<4; i++){
        array[i] = malloc(sizeof(Person));
        array[i]->m_id = SIZE+i;
        array[i]->m_next= NULL;
    }
    array[4] = malloc(sizeof(Person));
    array[4]->m_id = SIZE;
    array[4]->m_next= NULL;
    
    Ishead(array[1], array[0]);
    Istail(array[1], array[0]);
    SameKey(array[4], array[0]);

    IsReturnHead(array[1], array[0]);  
    IsHeadRemoved(array[1], array[0], item); 
    IsHeadNULL(array[1], array[0], item);

    IsInsertByKey(array[3], array[1], array[4], array[2]);
    IsInsertFirst(array[3], array[2], array[1],array[4]);
    IsInsertLast(array[2], array[1], array[4],array[3]);
    IsInsertNULLHead(array[0]);
    
    IsInsertByKeyRec(array[3], array[1], array[4], array[2]);
    IsInsertFirstRec(array[3], array[2], array[1],array[4]);
    IsInsertLastRec(array[2], array[1], array[4],array[3]); 
    
    IsRemoveByKey(array[3], array[1], array[4], item);
    IsRemoveByKeyFirst(array[3], array[1], array[4], item);
    IsRemoveByKeyLast(array[3], array[1], array[4], item);
    IsRemovInvalidKey(array[3], array[1], array[4], item);
    
    IsRemoveByKeyRec(array[3], array[1], array[4], item);
    IsRemoveByKeyFirstRec(array[3], array[1], array[4], item);
    IsRemoveLastRec(array[3], array[1], array[4], item);
    IsRemovInvalidKeyrec(array[3], array[1], array[4], item);
    IsGetLast(array[3], array[1], array[4]);
    
    for(i=0; i<5; i++){
        free(array[i]);
    }   
    free(item);

    return 0;

}

















