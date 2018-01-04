
/*            linked list API functions by Ido Naveh          */

# include <stdlib.h>
# include <stdio.h>
# include "linked.h"



Person* ListInsertHead(Person* _head, Person* _p){

    if(_head->m_id == _p->m_id)
    {
        return _head;
    }
	_p->m_next = _head;
	return _p;
}	

Person* ListRemoveHead(Person* _head, Person** _item){    
    
    if(NULL == _head)
    {
        return NULL;
    }
    else
    {    
    (*_item) = _head;
    _head = _head->m_next;
    }
    return _head;
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p){

    Person* curP;
    Person* preP;
    preP=_head;
    
    if(NULL == _head){
        _head = _p;
        return _head;
    }
    
    if(_head->m_id > _key)
    {
        curP =ListInsertHead(_head, _p);
        return curP;
    }
    
    curP = _head->m_next;
    
    while(curP != NULL)
    { 
        if(curP-> m_id > _key)
        {
           preP-> m_next = _p;
           _p-> m_next = curP;
           return _head;    
        } 
        
        preP= curP;
        curP = curP -> m_next;  
    }
     
    preP->m_next = _p;
    _p->m_next= NULL; 
    return _head;

}
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p){
     
    Person* preP;
     
    if(NULL == _head)
    {
      preP = _p;
      _p->m_next = NULL;
       return _head;     
    } 
      
    if(_head->m_id > _key)
    {
       _p->m_next = _head;
       _head = _p;
       return _head;     
    } 
    preP = _head;
    _head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
    return _head;
}

Person* ListRemoveByKey(Person* _head, int _key, Person** _p){
    
    Person* curP;
    Person* preP;
    preP = _head;
    curP = _head->m_next;
    
    if (preP == NULL){
    	(*_p) = _head;
        return _head;
    }
    
    if(_head->m_id == _key){
    	(*_p) = _head;
       _head = _head->m_next;
       return _head;
    }
    while(curP != NULL)
    {  
        if(curP->m_id == _key)
        {
           (*_p)= curP;
           preP->m_next = curP->m_next;
           return _head; 
        } 
        
        preP= curP;
        curP = curP -> m_next;  
    }
    return _head;
}
    
Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p){ 
        
    if(NULL == _head)
    {
       (*_p) = _head;
       return _head;     
    } 
      
    if(_head->m_id == _key)
    {
       (*_p)= _head;
       _head =_head->m_next;
       return _head;    
    }  
    
    _head->m_next = ListRemoveByKeyRec(_head->m_next, _key, _p);
    
    return _head;
}

Person* GetLast(Person* _head){

	if(NULL == _head)
    {
       return _head;     
    }
     
	if(_head->m_next == NULL)
    {
       return _head;    
    }  
    _head = GetLast(_head->m_next);
    return _head;

}


void PrintList(Person* _head){

    if ( _head == NULL)
        return;
        
    else {
        printf("%3d",_head->m_id);
        PrintList(_head->m_next); 
    }
}
