#include <stdio.h>
#include <stdlib.h>

#include "double.h"
#include "list_itr.h"
#include "list_functions.h"

#define MAGIC 0xddd
 
typedef struct Node Node;
 
struct Node
{
	void* m_data;

	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	size_t magic;
};

#define LIST_FIRST(L) ( (L)->m_head.m_next)
#define LIST_LAST(L)  ( (L)->m_tail.m_prev)
#define LIST_END(L)   (&(L)->m_tail)

#define IS_EMPTY(L)      (LIST_FIRST((L)) == LIST_END((L)))
#define IS_A_LIST(L)     ((L) && (L)->m_magicNum == LIST_MAGIC) 

static int IsNullList(const List* _list);
static int IsValidPara(const List* _list, PredicateFunc _predicateFunc, void* *_item);
static void InsertNode(Node* prev, Node* toInsert, Node* next);
static void RemoveNode(Node* prev, Node* next);
static int BubbleSortList(ListItr _begin, ListItr _end, LessFunction _less);
static void SwapIter(ListItr _begin, ListItr _next, void* valBegin, void* valNext);
void static Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd);
ListItr static CreateDupList(ListItr _begin, ListItr _end, EqualsFunction _equals);

/**********************************double.h API Functions************************************/

List* ListCreate(void){

	List* newList = malloc(sizeof(List));
	if(NULL == newList)
	{
		return NULL;
	}
	
	newList->m_head.m_next = &(newList->m_tail);
	newList->m_head.m_prev = NULL;
	newList->m_tail.m_next = NULL;
	newList->m_tail.m_prev = &(newList->m_head);
	newList->magic = MAGIC;
	
	return newList;
}

void ListDestroy(List** _list, UserActionFunc _destoryFunc){

	Node* temp;
	if(IsNullList(*_list))
	{
		return;
	}
	
	while((*_list)->m_head.m_next != &((*_list)->m_tail)) /*while loop until the list is empty */
	{
		if(_destoryFunc != NULL)
		{
			_destoryFunc((*_list)->m_head.m_next->m_data, NULL); 
			temp = (*_list)->m_head.m_next;
			free((*_list)->m_head.m_next);
			(*_list)->m_head.m_next = temp->m_next;
		}
		else
		{
			break;
		}
	}
	(*_list)->magic = 2;
	free(*_list);
	_list = NULL;
	return;
}
    
ListErrors ListPushHead(List* _list, void* _data){

	Node* newHead;
	if(IsNullList(_list))
	{
		return  LIST_UNINITIALIZED;
	}
	
	newHead= malloc(sizeof(Node));
	if (NULL == newHead)
	{
		return   LIST_ALLOCATION_FAILED;
	}
	newHead->m_data = _data;
	InsertNode(&(_list->m_head), newHead, _list->m_head.m_next); /*insert the new node between head and first node */
	return LIST_OK;

}
    
ListErrors ListPushTail(List* _list, void* _data){
	
	Node* newTail;
	if(IsNullList(_list))
	{
		return LIST_UNINITIALIZED;
	}
	
	newTail= malloc(sizeof(Node));
	if (NULL == newTail)
	{
		return  LIST_ALLOCATION_FAILED;
	}
	newTail->m_data = _data;
	InsertNode(_list->m_tail.m_prev, newTail, &(_list->m_tail)); /*insert the new node between tail and last node */
	return LIST_OK;
}

ListErrors ListPopHead(List* _list, void** _data){
	
	if(IsNullList(_list))
	{
		return LIST_UNINITIALIZED;
	}
	
	if(NULL == _data)
	{
		return  LIST_UNINITIALIZED;
	}
	
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return  ERR_LIST_IS_EMPTY;
	}
	
	(*_data) = _list->m_head.m_next->m_data;
	free(_list->m_head.m_next);
	RemoveNode((&_list->m_head), _list->m_head.m_next->m_next); /*change the pointers between the removed node */
	return  LIST_OK;
}

ListErrors ListPopTail(List* _list, void** _data){
    	
	if(IsNullList(_list))
	{
		return LIST_UNINITIALIZED;
	}
	
	if(NULL == _data){
		return LIST_UNINITIALIZED;
	}
	
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_LIST_IS_EMPTY;
	}
	
	(*_data) = _list->m_tail.m_prev->m_data;
	free(_list->m_tail.m_prev);
	RemoveNode(_list->m_tail.m_prev->m_prev, &(_list->m_tail));/*change the pointers between the removed node */	
	return LIST_OK;
}

size_t ListCountItems(const List* _list){

	size_t counter = 0;
	Node* nextNode = _list->m_head.m_next;
	
	if(IsNullList(_list) || nextNode == &(_list->m_tail))
	{
		return counter;
	}
	
	while(nextNode != &(_list->m_tail))
	{
		++counter;
		nextNode = nextNode->m_next;
	}
	return counter;
}

int ListIsEmpty(const List* _list){

	return IsNullList(_list) || _list->m_head.m_next == &(_list->m_tail)? 1 : 0;

}

ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item){
	
	Node* nextNode = _list->m_head.m_next;
	
	if(!IsValidPara( _list, _predicateFunc, _item))
	{
		return LIST_UNINITIALIZED;
	}
	
	if(nextNode == &(_list->m_tail))
	{
		return ERR_LIST_IS_EMPTY;
	}
	
	while(nextNode != &(_list->m_tail))
	{
		if(_predicateFunc(nextNode->m_data, _context))
		{
			*_item = nextNode->m_data;
			break;
		}
		nextNode = nextNode->m_next;
	}
	
	return LIST_OK;
}

ListErrors FindFirstBackward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item){

	Node* prevNode = _list->m_tail.m_prev;
	if(!IsValidPara( _list, _predicateFunc, _item))
	{
		return LIST_UNINITIALIZED;
	}

	while( prevNode != &(_list->m_head))
	{
		if(_predicateFunc(prevNode->m_data, _context))
		{
			*_item = prevNode->m_data;
			break;
		}
		prevNode = prevNode->m_prev;
	}
	
	return LIST_OK;
}

size_t ListForEach(const List* _list, UserActionFunc _action, void* _context){

    Node* nextNode = _list->m_head.m_next;
    size_t i = 0;
    
	if(IsNullList(_list))
	{
		return 0;
	}
	
	while(nextNode != &(_list->m_tail))
    {
        if(_action(nextNode->m_data, _context) == 0)
        {
            break;   	
        }
        
        ++i;
        nextNode = nextNode->m_next;
    }
    
    return i;
}

/**********************************list_itr.h API Functions************************************/

ListItr ListItr_Begin(const List* _list){

	if(IsNullList(_list))
	{
		return  NULL;
	}
	
	return LIST_FIRST(_list);
	
}

ListItr ListItr_End(const List* _list){

	if(IsNullList(_list))
	{
		return  NULL;
	}
	
	return (void*)LIST_END(_list);
}

int ListItr_Equals(const ListItr _a, const ListItr _b){

	/*chck is either is tail*/
	return _a == _b? 1 : 0;

}

ListItr ListItr_Next(ListItr _itr){
	
	Node* temp = (Node*)_itr;
	
	if(temp->m_next == NULL)
	{
		return NULL;
	}
	
	return (void*)temp->m_next;

}

ListItr ListItr_Prev(ListItr _itr){
	
	Node* temp = (Node*)_itr;
	return temp = (temp->m_prev->m_prev == NULL ? _itr : temp->m_prev);
}

void* ListItr_Get(ListItr _itr){

	void* getVal;
	Node* temp = (Node*)_itr;
	
	getVal = (temp->m_next == NULL && temp->m_prev == NULL ? NULL : temp->m_data);
	
	return getVal;
	
}

void* ListItr_Set(ListItr _itr, void* _element){

	void* getVal;
	Node* temp = (Node*)_itr;
	
	if(temp->m_next == NULL)
	{
		return NULL;
	}
	
	getVal = temp->m_data;
	temp->m_data = _element;
	
	return getVal;

}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element){

	Node* newNode;
	Node* temp = (Node*)_itr;
	
	newNode= malloc(sizeof(Node));
	if (NULL == newNode)
	{
		return   NULL;
	}
	
	newNode->m_data = _element;
	InsertNode(temp->m_prev, newNode, temp);
	
	return newNode;

}

void* ListItr_Remove(ListItr _itr){

	void* getVal;
	Node* temp = (Node*)_itr;
	
	getVal = temp->m_data;
	RemoveNode(temp->m_prev, temp->m_next);
	free(_itr);
	
	return getVal;
}

/**********************************list_functions************************************/
ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context){

	void* value = NULL;
	if(NULL ==_predicate || NULL == _context)
	{
		return _end;
	}
	
	while(!ListItr_Equals(_begin, _end))
	{
		value = ListItr_Get(_begin);
		if(_predicate(value, _context))
		{
			return _begin;
		}
		_begin = ListItr_Next(_begin);
	}
	return _end;

}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context){

	void* value = NULL;
	size_t counter = 0;
	
	if(NULL ==_predicate || NULL == _context)
	{
		return counter;
	}
	
	while(!ListItr_Equals(_begin, _end))
	{	
		value = ListItr_Get(_begin);
		if(_predicate(value, _context))
		{
			++counter;
		}
		_begin = ListItr_Next(_begin);
	}
	return counter;
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context){

	void* value = NULL;
	
	if(NULL == _action)
	{
		return _begin;
	} 
	
	while(!ListItr_Equals(_begin, _end))
	{	
        value = ListItr_Get(_begin);
        if(_action(value, _context) == 0)
        {
            break;   		
        }
        _begin = ListItr_Next(_begin);
    }
    
    return  _begin;

}

void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less){
	
	if(NULL == _less)
	{
		return ;
	} 

	while(!ListItr_Equals(_begin, _end)){
	
		if(BubbleSortList(_begin, _end, _less) == 0)
		{
			return;
		}
		_end = ListItr_Prev(_end);
	}
	return;

}

static int BubbleSortList(ListItr _begin, ListItr _end, LessFunction _less){

	void* valBegin = NULL;
	void* valNext = NULL;
	size_t counter = 0;
	ListItr next =ListItr_Next(_begin);
	
	
	while(!ListItr_Equals(_begin, NULL) && (!ListItr_Equals(next, _end)))
	{
		valBegin = ListItr_Get(_begin); 
		valNext = ListItr_Get(next);
		if(!_less(valBegin, valNext))
		{
			SwapIter(_begin , next, valBegin, valNext);
			counter++;
		}	
		_begin =ListItr_Next(_begin);
		next =ListItr_Next(_begin);
	}
	
	return counter;
}

static void SwapIter(ListItr _begin, ListItr _next, void* valBegin, void* valNext){

	ListItr_Set(_begin, valNext);
	ListItr_Set(_next, valBegin);	
	
	return;
}


ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end){
	
	Node* left = (Node*)_begin;
	Node* right= (Node*)_end;
	Node* destNode= (Node*)_dest;

	left->m_prev = right->m_next;
	destNode->m_prev = left;
	destNode->m_next = NULL;
	left->m_next = destNode;
	
	return (void*)destNode;

}

List* ListItr_Cut(ListItr _begin, ListItr _end){
	
	List* newList;
	Node* start = (Node*)_begin;
	Node* end= (Node*)_end;
	
	newList = ListCreate();
	if(newList == NULL)
	{
		return NULL;
	}
	
	start->m_prev = end->m_next;
	
	newList->m_head.m_next = start;
	end->m_next= &newList->m_tail;
	
	return newList;

}

ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd, ListItr _secondBegin, ListItr _secondEnd, LessFunction _less){
		
	ListItr start = _firstBegin;
	
	Merge(_destBegin, _firstBegin, _firstEnd);
	Merge(_destBegin, _secondBegin, _secondEnd);
    		
	if(NULL != _less)
	{
	    _destBegin = ListItr_Next(_destBegin);
	    start = ListItr_Prev(start);
	    ListItr_Sort(start, _destBegin, _less);
	}
	
	return _destBegin;		
}

void static Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd){

    void* value;
    ListItr temp;
    
    while(!ListItr_Equals(_firstBegin, _firstEnd))
	{	
        value = ListItr_Get(_firstBegin);
        ListItr_InsertBefore(_destBegin, value);
        temp = _firstBegin;
        _firstBegin = ListItr_Next(_firstBegin);
        ListItr_Remove(temp);
    }
    value = ListItr_Get(_firstBegin);
    ListItr_InsertBefore(_destBegin, value);
    ListItr_Remove(_firstBegin);
    
    return;
}

List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals){
    
    ListItr endDupList = _begin;
    ListItr beginDupList = NULL;
    
    if(NULL == _equals)
    {
        return NULL;
    }
    
    beginDupList = CreateDupList(_begin, _end, _equals);
    
    if(beginDupList !=endDupList)
    {
        endDupList= ListItr_Prev(endDupList);
        return ListItr_Cut(beginDupList, endDupList);
    }

    return NULL; 
}

ListItr static CreateDupList(ListItr _begin, ListItr _end, EqualsFunction _equals){

    void* beginVal = NULL;
    void* nextVal = NULL;
    ListItr endDupList = _begin;
    ListItr beginDupList = _begin;
    ListItr next = ListItr_Next(_begin);
    size_t counter =0;
    
    if(NULL == _equals)
    {
        return NULL;
    }
    
    while(!ListItr_Equals(next, _end))
	{	
        beginVal = ListItr_Get(_begin);
        nextVal = ListItr_Get(next);
        if(_equals(beginVal, nextVal) == 0)
        {
            ListItr_Remove(next);
            ListItr_InsertBefore(endDupList, nextVal);
            ++counter;  
        }
        _begin = ListItr_Next(_begin);
        next = ListItr_Next(_begin);
    }
    
    while(counter != 0)
    {
        beginDupList = ListItr_Prev(beginDupList);
        --counter;
    }

    return beginDupList;
}

/******************************* static functions ********************/

static int IsNullList(const List* _list){
    
    return NULL ==_list || _list->magic != MAGIC ? 1 : 0;
 
}

static int IsValidPara(const List* _list, PredicateFunc _predicateFunc, void* *_item){

	if(IsNullList(_list))
	{
		return 0;
	}
	
	if(NULL == _predicateFunc)
	{
		return 0;
	}
	
	if(NULL == _item)
	{
		return 0;
	}
	
	return 1;
}
	
static void InsertNode(Node* prev, Node* toInsert, Node* next){

	prev->m_next = toInsert;
	next->m_prev = toInsert;
	toInsert->m_next = next;
	toInsert->m_prev = prev;
	
	return;
}

static void RemoveNode(Node* prev, Node* next){
    
    if(prev != NULL && next != NULL)
    {
        prev->m_next = next;
	    next->m_prev = prev;
    }
	return;
}


