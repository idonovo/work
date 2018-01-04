#ifndef __DOUBLE_H__
#define __DOUBLE_H__

#include <stdlib.h>
#include "ADTDefs.h"

typedef struct List List;

/*Desc.: function to create a double linked list structure with const. head and tail nodes.
Input: _
Output: pointer to the new list.
Error: NULL pointer if allocation failed.*/
List* ListCreate(void);

/*Desc.: function to a double linked list.
Input:  pointer to the the list.
Output: -.
Error: the list have a magic number to check if the destroy succeed.*/
void ListDestroy(List* _list);

/*Desc.: function to insert a new object from the head of the list by creating a new node and initialized the node with data from the user.
Input:  pointer to the list and int data. 
Output: if unsertion succeeded ERR_OK;
Error:  if the list or the new node are NULL - ERR_NOT_INITIALIZED*/
ADTErr ListPushHead(List* _list,int _data);


/*- same as above but from the tail */
ADTErr ListPushTail(List* _list,int _data);

/*Desc.: function to delete the head object from the list band return its data to an int pointer.  
Input:  pointer to the list and a pointer to assign the deleted data.
Output: pointer to the new head;
Error:  if the list or the pointer are NULL - ERR_NOT_INITIALIZED*/
ADTErr ListPopHead(List* _list,int* _data);

/*- same as above but from the tail */
ADTErr ListPopTail(List* _list,int* _data);

/*Desc.:function to count the items in the list.
Input:  pointer to the list;
Output: size_t counter of items.
Error:  no error (the function returns 0 if there are no items or if the list is NULL) */
size_t ListCountItems(List* _list);

/*Desc.:bolean function tcheck wetther the list is empty.
Input:  pointer to the list.
Output: bolean variable - 0 for empty or 1 for not empty.
Error: Error:  no error (the function returns 0 if there are no items or if the list is NULL) */
int ListIsEmpty(List* _list);

void ListPrint(List* _list);
#endif /* endif __DOUBLE_H__ */
