#include <stdio.h>
#include <stdlib.h>

#include  "../../inc/bin_tree.h"

#define MAGIC_NUM 7377175

#define IS_A_TREE(T)     ((T) && (T)->m_test == MAGIC_NUM)
#define EMPTY_TREE(T) (T)->m_root.m_left 
#define END_OF_TREE(T) (T) 
#define IF_LEFT(T)     ((T)->M_LEFT)
#define IF_RIGHT(T)     ((T)->M_RIGHT)

typedef struct Node Node;

struct Node
{
   	void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct BSTree
{
	int m_test;
	Node m_root; 
	LessComparator m_less;	
};


typedef BSTreeItr (*Trav)(Node* _root, ActionFunction _action, void* _context);

void static destroyTree(Node* _root, void (*_destroyer)(void*));
static Node* CreateNode(void* _item);
static void insertNode(Node* _root, Node* _newNode, LessComparator _less, void* _item);
BSTreeItr static FindNextChild(Node* _curNode);
BSTreeItr static FindNextParent(Node* _curNode);
BSTreeItr static FindPrevChild(Node* _curNode);
BSTreeItr static FindPrevParent(Node* _curNode);
BSTreeItr static preOrder(Node* _root, ActionFunction _action, void* _context);
BSTreeItr static postOrder(Node* _root, ActionFunction _action, void* _context);
BSTreeItr static inOrder(Node* _root, ActionFunction _action, void* _context);
Trav TraverseFunc[3] = {preOrder, postOrder, inOrder};

/****************************************************************/
BSTree* BSTree_Create(LessComparator _less){

	BSTree* newTree;
	
	if(NULL == _less)
	{
		return NULL;
	}
	
	newTree = malloc(sizeof(BSTree));
	
	if(NULL != newTree)
	{
		newTree->m_less = _less;
		newTree->m_root.m_left = NULL;
		newTree->m_root.m_right = NULL;
		newTree->m_root.m_father = &newTree->m_root;
		newTree->m_test = MAGIC_NUM;
		return newTree;
	}
	
	return NULL;
}

/********************************************************************/
void BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void*)){

	if(!IS_A_TREE(_tree))
	{
		return;
	} 
	
	destroyTree(_tree->m_root.m_left, _destroyer);
	_tree->m_test = 0;
	free(_tree);
	return;

}

void static destroyTree(Node* _root, void (*_destroyer)(void*)){

	if(_root == NULL)
	{
		return;
	}
	
	destroyTree(_root->m_left, _destroyer);
	destroyTree(_root->m_right, _destroyer);
	
	if(NULL !=_destroyer)
	{
		_destroyer(_root->m_data);
	}
	free(_root);

}
/******************************************************************/

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item){
	
	Node* newNode;
	if((!IS_A_TREE(_tree)) || _item == NULL)
	{
		return NULL;
	}
	
	newNode = CreateNode(_item);
	
	if(!EMPTY_TREE(_tree))
	{
	     newNode->m_father = &_tree->m_root;
	    _tree->m_root.m_left = newNode;

	    return (BSTreeItr)newNode;
	} 

	insertNode(_tree->m_root.m_left, newNode, _tree->m_less, _item);
	
	return (BSTreeItr)newNode;
}

static Node* CreateNode(void* _item){

    Node* newNode = calloc(1 ,sizeof(Node));
	if(NULL == newNode){
		return NULL;
	}
	newNode->m_data = _item;
	return newNode;
}

static void insertNode(Node* _root, Node* _newNode, LessComparator _less, void* _item){

    if(_root->m_right == NULL && (!_less(_root->m_data, _item)))
	{
		_root->m_right = _newNode;
		_newNode->m_father=_root;
	}
	else if(_root->m_left == NULL && _less(_root->m_data, _item))
	{
		_root->m_left = _newNode;
		_newNode->m_father=_root;
	}
	else if (!_less(_root->m_data, _item))
	{
		insertNode(_root->m_right,_newNode, _less, _item);
	}	
	else
	{
		insertNode(_root->m_left, _newNode, _less, _item);
	}
	return;
}
	 
/***********************************************************************/
BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context){

	
	if ((!IS_A_TREE(_tree)) || !EMPTY_TREE(_tree) || NULL == _predicate || NULL == _context)
	{
        return NULL;
	}
	
	return BSTree_ForEach(_tree,BSTREE_TRAVERSAL_INORDER, _predicate, _context);

}

/********************************************************************/	
BSTreeItr BSTreeItr_Begin(const BSTree* _tree){

	Node* curNode;
	if((!IS_A_TREE(_tree)))
	{
		return NULL;
	}
	
	if(!EMPTY_TREE(_tree))
	{
		return NULL;
	}
	
	curNode = _tree->m_root.m_left;
	
	while(curNode->m_left != NULL)
	{
		curNode = curNode->m_left;
	}
	
	return (BSTreeItr)curNode;	

}
/********************************************************************/
BSTreeItr BSTreeItr_End(const BSTree* _tree){
	
	if((!IS_A_TREE(_tree)))
	{
		return NULL;
	}
	
	return (BSTreeItr)_tree->m_root.m_right;

}

/********************************************************************/
int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b){

	return _a == _b;

}

/********************************************************/
BSTreeItr BSTreeItr_Next(BSTreeItr _it){

	Node* curNode = _it;
	
	if(NULL == curNode)
	{
		return NULL;
	}
	
	if(curNode->m_right != NULL)
	{
		return FindNextChild(curNode);
	}
	else
	{
		return FindNextParent(curNode);
	}
}

BSTreeItr static FindNextChild(Node* _curNode){

	_curNode = _curNode->m_right;
	while(_curNode->m_left != NULL)
	{
		_curNode = _curNode->m_left;
	}
	
	return (BSTreeItr)_curNode;
}

BSTreeItr static FindNextParent(Node* _curNode){

	/*_curNode = _curNode->m_father;
*/	
	while(_curNode->m_father->m_right == _curNode)
	{
		_curNode = _curNode->m_father;
	}	
	
	/*TODO */
	return (BSTreeItr)_curNode->m_father;
}

/***************************************************************/

BSTreeItr BSTreeItr_Prev(BSTreeItr _it){

	Node* curNode = _it;
	
	if(NULL == curNode)
	{
		return NULL;
	}
	
	if(curNode->m_left != NULL)
	{
		return FindPrevChild(curNode);
	}
	else
	{
		return FindPrevParent(curNode);
	}
}

BSTreeItr static FindPrevChild(Node* _curNode){

	_curNode = _curNode->m_left;
	while(_curNode->m_right != NULL)
	{
		_curNode = _curNode->m_right;
	}
	
	return (BSTreeItr)_curNode;
}

BSTreeItr static FindPrevParent(Node* _curNode){

	BSTreeItr initialNode = _curNode;
	 
	_curNode = _curNode->m_father;
	while(_curNode->m_father->m_left == _curNode)
	{
		_curNode = _curNode->m_father;
	}
	
	if(_curNode->m_father->m_right == NULL)
	{
		return initialNode;
	}
	return (BSTreeItr)_curNode->m_father;
}
/*********************************************************************************/


/** 
 * @brief Removes element from tree
 * @details Remove element pointed to by _it and rearranges the tree so that it maintains binary search tree arrangement
 * Average/Worst time complexity O(?).
 *
 * @param _it : A tree iterator
 * @return removed item or null on failure
 */
void* BSTreeItr_Remove(BSTreeItr _it);

/************************************************************************************/
void* BSTreeItr_Get(BSTreeItr _it){
	
	Node* getVal= _it;
	
	if(_it != NULL)
	{
		return getVal->m_data;
	}

	return NULL;

}

/*********************************************************************************************************/

BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode, ActionFunction _action, void* _context){
	
	
	if ((!IS_A_TREE(_tree)) || _tree->m_root.m_left == NULL || 4 < _mode || 0 > _mode ||NULL == _action)
	{
        return NULL;
	}
	
	if(_mode == BSTREE_TRAVERSAL_PREORDER)
	{
		return preOrder(_tree->m_root.m_left, _action, _context);
	}
	
	if(_mode == BSTREE_TRAVERSAL_POSTORDER)
	{
		return postOrder(_tree->m_root.m_left, _action, _context);
	}
	
	if(_mode == BSTREE_TRAVERSAL_INORDER)
	{
		return inOrder(_tree->m_root.m_left, _action, _context);
	}

}

BSTreeItr static preOrder(Node* _root, ActionFunction _action, void* _context){
	
	void* value;
	
	if(NULL == _root)
	{
		return (BSTreeItr)_root;
	} 
	
	value = _root->m_data;
	if(_action(value, _context) == 0)
	{
		return (BSTreeItr)_root;
	} 
	preOrder(_root->m_left, _action, _context);
	preOrder(_root->m_right, _action, _context);
	
}
	
BSTreeItr static postOrder(Node* _root, ActionFunction _action, void* _context){
	
	void* value = NULL;
	
	if(NULL == _root)
	{
		return (BSTreeItr)_root;
	} 
	
	postOrder(_root->m_left, _action, _context);
	postOrder(_root->m_right, _action, _context);
	
	value = _root->m_data;
	if(_action(value, _context) == 0)
	{
		return (BSTreeItr)_root;
	} 
}
	
BSTreeItr static inOrder(Node* _root, ActionFunction _action, void* _context){
	
	void* value = NULL;
	
	if(NULL == _root)
	{
		return (BSTreeItr)_root;
	} 
	
	inOrder(_root->m_left, _action, _context);
	
	value = _root->m_data; 
	if(_action(value, _context) == 0)
	{
		return (BSTreeItr)_root;
	}
	
	inOrder(_root->m_right, _action, _context);
}	


