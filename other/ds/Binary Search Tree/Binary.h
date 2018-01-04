#ifndef __MYBINARYTREE__
#define ___MYBINARYTREE__

#include "ADTDefs.h"
#include <stdlib.h>

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
} TreeTransverse; 

typedef struct Node Node;

typedef struct Tree Tree;

struct Tree{
	Node* root; 
	int magic;
};
/*Desc.: function to create a tree structure with pointer to the root.
Input: _
Output: pointer to the new tree.
Error: NULL pointer if allocation failed.*/
Tree* TreeCreate();
/*Desc.: function to destroy all tree leafs and root and then the tree itself.
Input: pointer to the tree.
Output: ___
Error: ___.*/
void TreeDestroy(Tree* _tree);
/*Desc.: function to insert a new leaf to the tree. the function checks the parameters and if the data is already in the tree and then create a new leaf in the right position.
Input: pointer to the tree and data to insert.
Output: pointer to the update tree.
Error: ADTErr errors if the tree is NULL orif the new alloction of leaf failed or if the data already exist .*/
ADTErr TreeInsert(Tree* _tree, int data);
/*Desc.: function to search if data exist in tree. returns 1 for positive or 0 if negative.
Input: pointer to the tree and data to search.
Output: returns 1 for positive or 0 if negative.
Error: return 0 if the tree is NULL .*/
int TreeIsDataFound(Tree* _tree, int _data, Find _find, context _Context);
/*Desc.: function to print the tree leafs by 3 options: PRE_ORDER, IN_ORDER, POST_ORDER.
Input: pointer to the tree to print;
Output: prints the data in the tree eafs in STDIN.
Error: not printing if tree is NULL .*/
void TreePrint(Tree* _tree, TreeTransverse _transverseMode);

#endif /*#ifndef __MYBINARYTREE__ */
