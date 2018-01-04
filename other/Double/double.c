#include <stdio.h>
#include <stdlib.h>

#include "double.h"

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

static int IsNullList(const List* _list);
static int IsValidPara(const List* _list, PredicateFunc _predicateFunc, void* *_item);
static void InsertNode(Node* prev, Node* toInsert, Node* next);
static void RemoveNode(Node* prev, Node* next);

/**********************************API Functions************************************/

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
	(*_list)->magic = 1;
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
	
	(*_data) = _list->m_head.m_next->m_data;
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

	prev->m_next = next;
	next->m_prev = prev;
	
	return;
}


