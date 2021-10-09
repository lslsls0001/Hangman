#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "gen_vector.h"

typedef struct avlTreeNode AVLTreeNode;

struct avlTreeNode {
	My_string* family_key;
	int height;
	G_Vector* pVector;
	AVLTreeNode* pLeftTree;
	AVLTreeNode* pRightTree;
};

//create a AVL tree node.
AVLTreeNode* AVLTree_init_default(My_string* family_key, My_string* my_word);

//get the tree height
int AVLTree_height(AVLTreeNode* pTree);

//pre order to search AVL tree non size
void preorder_AVLTree(AVLTreeNode* pTree, int* size, G_VECTOR vector);

//in order to search AVL tree
void inorder_AVLTree(AVLTreeNode* pTree);

//search a family key
AVLTreeNode* AVLTree_search(AVLTreeNode* pTree, My_string* family_key);

//left left case, right rotation
AVLTreeNode* left_left_rightRotation(AVLTreeNode* pTree);

//right right case, left rotation
AVLTreeNode* right_right_leftRotation(AVLTreeNode* pTree);

//left right case, left-to-right rotation
AVLTreeNode* left_right_leftRightRotation(AVLTreeNode* pTree);

//right left case, right-to-left rotation
AVLTreeNode* right_left_rightLeftRotation(AVLTreeNode* pTree);

//insert a node to AVL tree
AVLTreeNode* AVLTree_insert(AVLTreeNode* pTree, My_string* family_key, My_string* my_word);

//destory a node in AVLTree
void destroy_AVLTree(AVLTreeNode* pTree);
