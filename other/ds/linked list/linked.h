#ifndef __LINKED_H__
#define __LINKED_H__

typedef struct Person Person;

struct Person
{
	int 	m_id;
	char 	m_name[100];
	int 	m_age;
	Person* m_next;
};

/*Desc.: function to insert a head to a NULL or non-NULL linked list.
Input:  pointer to the current head and a pointer to the new head;
Output: pointer to the new head;
Error: no error return.*/
Person* ListInsertHead(Person* _head, Person* _p);
/*Desc.: function to remove an object as a head of a linked list by pointing the head pointer to the next object.
Input:  head pointer and p2p for the removed head.
Output: pointer to the new head.
Error: no error return.*/
Person* ListRemoveHead(Person* _head, Person** _item);
/*Desc.:function to insert an object to a sorted linked list by key. if the head pointer is NULL the object will become the head.
Input:  head pointer, pointer to the new object and the object key.
Output: head pointer.
Error: no error return.*/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);
/*Desc.:recursive function to insert an object to a sorted linked list by key. if the head pointer is NULL the object will become the head.
Input:  head pointer, pointer to the new object and the object key.
Output: head pointer.
Error: no error return.*/
Person* ListInsertByKeyRec(Person* _head, int key, Person* _p);
/*Desc.:function to remove an object from a sorted linked list by key. if the head pointer is NULL or if the key not found the function returns the head pointer to the untouched list.
Input:  head pointer, object key and p2p for the removed head.
Output: head pointer.
Error: no error return.*/
Person* ListRemoveByKey(Person* _head, int _key, Person** _p);
/*Desc.: recursive function to remove an object from a sorted linked list by key. if the head pointer is NULL or if the key not found the function returns the head pointer to the untouched list.
Input:  head pointer, object key and p2p for the removed head.
Output: head pointer.
Error: no error return.*/
Person* ListRemoveByKeyRec(Person* _head, int key, Person** _p);


Person* GetLast(Person* _head);
void PrintList(Person* _head);
#endif /* endif __LINKED_H__ */
