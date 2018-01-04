#include <stdio.h>
#include <stdlib.h>

#include "Binary.h"

#define MAGIC 7377175
 
struct Node
{
    int m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

/**********************************************/	
static Node* CreateNode(int m_data){
	
	Node* newNode = calloc(1 ,sizeof(Node));
	if(NULL == newNode){
		return NULL;
	}
	newNode->m_data = m_data;
	return newNode;
}

static Node* Search(Node* _root, int m_data){
	
	if(_root == NULL)
	{
		return _root;
	}
	
	if(_root->m_data == m_data){
		return _root;
	}
	else if (_root->m_data < m_data)
	{
		_root = Search(_root->m_right, m_data);
	}	
	else if(_root->m_data > m_data)
	{
		_root = Search(_root->m_left, m_data);
	}
}

static void Insert(Node* _root, Node* _newNode, int m_data){

	if(_root->m_right == NULL && _root->m_data < m_data)
	{
		_root->m_right = _newNode;
		_newNode->m_father=_root;
	}
	else if(_root->m_left == NULL && _root->m_data > m_data)
	{
		_root->m_left = _newNode;
		_newNode->m_father=_root;
	}
	else if (_root->m_data < m_data)
	{
		Insert(_root->m_right,_newNode, m_data);
	}	
	else
	{
		Insert(_root->m_left, _newNode, m_data);
	}
	return; 
}

static void DestroyNodes(Node* _root){

	if(_root->m_left != NULL)
	{
		DestroyNodes(_root->m_left);
	}
	if(_root->m_right != NULL)
	{
		DestroyNodes(_root->m_right);
	}
	free(_root);
	return;
}

static void printPostorder(Node* _root){
    if (_root == NULL){
        return;
	} 
    printPostorder(_root->m_left);
    printPostorder(_root->m_right);
    printf("  %3d  ", _root->m_data);
}
 
static void printInorder(Node* _root){

	if (_root == NULL){
          return;
	}
    printInorder(_root->m_left);
    printf("  %3d  ", _root->m_data);   
    printInorder(_root->m_right);
    return;
}
 
static void printPreorder(Node* _root){

    if (_root == NULL){
          return;
	}
	printf("  %3d  ", _root->m_data);  
	printPreorder(_root->m_left);  
	printPreorder(_root->m_right);
	return;
}  

/************************************************************/

Tree* TreeCreate(){

	Tree* newTree = malloc(sizeof(Tree));
	if(NULL == newTree){
		return NULL;
	}
	newTree->root = NULL;
	newTree->magic = MAGIC;
	return newTree;
}

void TreeDestroy(Tree* _tree){
	
	if(NULL == _tree)
	{
		return;
	}
	
	if(_tree->magic == MAGIC){
	    DestroyNodes(_tree->root);
	    _tree->magic = 0;
	    free(_tree);
	}
	return;	
}

ADTErr TreeInsert(Tree* _tree, int data){

	Node* newNode;

	if( NULL == _tree){
		return ERR_NOT_INITIALIZED;
	}
	
	if(_tree->root == NULL){
		newNode = CreateNode(data);
		_tree->root = newNode;
		return ERR_OK;
	}

	if(Search(_tree->root, data) != NULL ){
		return ERR_DUPLICATE_VALUE;
	}
	
	newNode = CreateNode(data);	
	Insert(_tree->root, newNode, data);
	return ERR_OK;
	
}

int TreeIsDataFound(Tree* _tree, int _data){

	if(Search(_tree->root, _data) == NULL){
		return 0;
	}
	return 1;
}

void TreePrint(Tree* _tree, TreeTransverse _transverseMode){
	
	if(_transverseMode == PRE_ORDER){
		printPreorder(_tree->root);
	}
	if(_transverseMode == IN_ORDER){
		printInorder(_tree->root);
	}
	if(_transverseMode == POST_ORDER){
		printPostorder(_tree->root);
	}
	printf("\n");
	return;
}

/***************************************************************/


