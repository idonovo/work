#include <stdio.h>
#include <stdlib.h>

#include "double.h"

#define MAGIC 7377175
 
typedef struct Node Node;
 
struct Node
{
	int m_data;

	Node* m_next;
	Node* m_prev;
};

struct List
{
	Node m_head;
	Node m_tail;
	size_t magic;
};

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

List* ListCreate(void){

	List* newList = malloc(sizeof(List));
	if(NULL == newList){
		return NULL;
	}
	newList->m_head.m_next = &(newList->m_tail);
	newList->m_head.m_prev = NULL;
	newList->m_tail.m_next = NULL;
	newList->m_tail.m_prev = &(newList->m_head);
	newList->magic = MAGIC;
	return newList;
}

void ListDestroy(List* _list){

	if(NULL == _list)
	{
		return;
	}
	
	if(_list->magic == MAGIC)
	{
		while(_list->m_head.m_next != &(_list->m_tail)) /*while loop until the list is empty */
		{
			free(_list->m_head.m_next);
			_list->m_head.m_next = _list->m_head.m_next->m_next;
		}
		free(_list);
	}
	return;
}

ADTErr ListPushHead(List* _list,int _data){

	Node* newHead;
	if(NULL == _list){
		return ERR_NOT_INITIALIZED;
	}
	
	 newHead= malloc(sizeof(Node));
	if (NULL == newHead)
	{
		return  ERR_ALLOCATION_FAILED;
	}
	newHead->m_data = _data;
	InsertNode(&(_list->m_head), newHead, _list->m_head.m_next); /*insert the new node between head and first node */

	return ERR_OK;

}
ADTErr ListPushTail(List* _list, int _data){
	
	Node* newTail;
	if(NULL == _list){
		return ERR_NOT_INITIALIZED;
	}
	
	newTail= malloc(sizeof(Node));
	if (NULL == newTail)
	{
		return  ERR_ALLOCATION_FAILED;
	}
	newTail->m_data = _data;
	InsertNode(_list->m_tail.m_prev, newTail, &(_list->m_tail) ); /*insert the new node between tail and last node */
	return ERR_OK;
}

ADTErr ListPopHead(List* _list,int* _data){
	
	if (NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(NULL == _data)
	{
		return  ERR_ALLOCATION_FAILED;
	}
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}
	(*_data) = _list->m_head.m_next->m_data;
	free(_list->m_head.m_next);
	RemoveNode((&_list->m_head), _list->m_head.m_next->m_next); /*change the pointers between the removed node */
	
	return  ERR_OK;
}
ADTErr ListPopTail(List* _list,int* _data){
	
	if (NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(NULL == _data){
		return ERR_NOT_INITIALIZED;
	}
	if(_list->m_head.m_next == &(_list->m_tail))
	{
		return ERR_UNDERFLOW;
	}
	
	(*_data) = _list->m_head.m_next->m_data;
	free(_list->m_tail.m_prev);
	RemoveNode(_list->m_tail.m_prev->m_prev, &(_list->m_tail));/*change the pointers between the removed node */
	
	
	return  ERR_OK;
}
size_t ListCountItems(List* _list){

	size_t counter=0;
	
	if (NULL == _list)
	{
		return counter;
	}
	while(_list->m_head.m_next != &(_list->m_tail))
	{
		counter++;
		_list->m_head.m_next = _list->m_head.m_next->m_next;
	}
	return counter;
}

int ListIsEmpty(List* _list){

	if (NULL == _list || _list->m_head.m_next == &(_list->m_tail))
	{
		return 0;
	}
	return 1;
}

void ListPrint(List* _list){
	
	Node* newHead =_list->m_head.m_next;
	
	if(NULL != _list){
		while(newHead->m_next != &(_list->m_tail))
		{
		printf("  %3d  ", newHead->m_next->m_data);
		newHead->m_next = newHead->m_next->m_next;
		}
	}
	printf("\n");
	return;
}
	
	


