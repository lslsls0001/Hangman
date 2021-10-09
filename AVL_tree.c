#include <stdio.h>
#include <stdlib.h>
#include "AVL_tree.h"

#define HEIGHT(pTree) ((pTree==NULL) ? 0:(((AVLTreeNode*)(pTree))->height))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

//create a AVL tree node.
AVLTreeNode* AVLTree_init_default(My_string* family_key, My_string* my_word) {
	AVLTreeNode* treeNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
	if (treeNode == NULL) {
		return NULL;
	}
	else {
		treeNode->family_key = NULL;
		my_string_assignment(&(treeNode->family_key), family_key);
		treeNode->height = 0;
		treeNode->pVector = (G_Vector*)g_vector_init_default(MyString_assign, MyString_destroy);
		g_vector_push_back(treeNode->pVector, my_word);
		treeNode->pLeftTree = NULL;
		treeNode->pRightTree = NULL;

		return treeNode;
	}
}

//get the tree height
int AVLTree_height(AVLTreeNode* pTree) {
	return HEIGHT(pTree);
}

//pre order to search AVL tree with size
void preorder_AVLTree(AVLTreeNode* pTree, int* size, G_VECTOR vector) {
	G_Vector* vec = (G_Vector*)vector;
	if (pTree != NULL) {
		printf("%s\t%d\n", pTree->family_key->str, pTree->pVector->size);
		size[vec->size] = pTree->pVector->size;
		g_vector_push_back(vector, pTree->family_key);
		preorder_AVLTree(pTree->pLeftTree,size,vector);
		preorder_AVLTree(pTree->pRightTree,size,vector);
	}
}

//in order to search AVL tree
void inorder_AVLTree(AVLTreeNode* pTree) {
	if (pTree != NULL) {
		inorder_AVLTree(pTree->pLeftTree);
		printf("%s\t%d\n", pTree->family_key->str, pTree->pVector->size);
		inorder_AVLTree(pTree->pRightTree);
	}
}

//search a family key
AVLTreeNode* AVLTree_search(AVLTreeNode* pTree, My_string* family_key) {
	if (pTree == NULL || my_string_compare(pTree->family_key, family_key) == 0) {
		return pTree;
	}
	if (my_string_compare(pTree->family_key, family_key) == 1) {
		return AVLTree_search(pTree->pLeftTree, family_key);
	}
	else {
		return AVLTree_search(pTree->pRightTree, family_key);
	}
}

//left left case, right rotation
AVLTreeNode* left_left_rightRotation(AVLTreeNode* pTree) {
	AVLTreeNode* pSubTree;

	pSubTree = pTree->pLeftTree;
	pTree->pLeftTree = pSubTree->pRightTree;
	pSubTree->pRightTree = pTree;

	pTree->height = MAX(HEIGHT(pTree->pLeftTree), HEIGHT(pTree->pRightTree)) + 1;
	pSubTree->height = MAX(HEIGHT(pSubTree->pLeftTree), pTree->height) + 1;

	return pSubTree;
}

//right right case, left rotation
AVLTreeNode* right_right_leftRotation(AVLTreeNode* pTree) {
	AVLTreeNode* pSubTree;

	pSubTree = pTree->pRightTree;
	pTree->pRightTree = pSubTree->pLeftTree;
	pSubTree->pLeftTree = pTree;

	pTree->height = MAX(HEIGHT(pTree->pLeftTree), HEIGHT(pTree->pRightTree)) + 1;
	pSubTree->height = MAX(HEIGHT(pSubTree->pRightTree), pTree->height) + 1;

	return pSubTree;
}

//left right case, left-to-right rotation
AVLTreeNode* left_right_leftRightRotation(AVLTreeNode* pTree) {
	
	pTree->pLeftTree = right_right_leftRotation(pTree->pLeftTree);

	return left_left_rightRotation(pTree);
}

//right left case, right-to-left rotation
AVLTreeNode* right_left_rightLeftRotation(AVLTreeNode* pTree) {

	pTree->pRightTree = left_left_rightRotation(pTree->pRightTree);

	return right_right_leftRotation(pTree);
}

//insert a node to AVL tree
AVLTreeNode* AVLTree_insert(AVLTreeNode* pTree, My_string* family_key, My_string* my_word) {
	
	if (pTree == NULL) {
		pTree = AVLTree_init_default(family_key, my_word);
		if (pTree == NULL) {
			printf("fail to create a AVLTree node!\n");
			return NULL;
		}
	}
	else if (my_string_compare(pTree->family_key, family_key) == 1) {
		pTree->pLeftTree = AVLTree_insert(pTree->pLeftTree, family_key, my_word);
		if (HEIGHT(pTree->pLeftTree) - HEIGHT(pTree->pRightTree) == 2) {
			if (my_string_compare(pTree->pLeftTree->family_key, family_key) == 1) {
				pTree = left_left_rightRotation(pTree);
			}
			else {
				pTree = left_right_leftRightRotation(pTree);
			}
		}
	}
	else if (my_string_compare(pTree->family_key, family_key) == -1) {
		pTree->pRightTree = AVLTree_insert(pTree->pRightTree, family_key, my_word);
		if (HEIGHT(pTree->pRightTree) - HEIGHT(pTree->pLeftTree) == 2) {
			if (my_string_compare(pTree->pRightTree->family_key, family_key) == -1) {
				pTree = right_right_leftRotation(pTree);
			}
			else {
				pTree = right_left_rightLeftRotation(pTree);
			}
		}
	}
	else {
		//printf("insert failure happens, system can not insert a node with the same family key!");
		g_vector_push_back(pTree->pVector, my_word);
	}

	pTree->height = MAX(HEIGHT(pTree->pLeftTree), HEIGHT(pTree->pRightTree)) + 1;

	return pTree;
}

//destory a node in AVLTree
void destroy_AVLTree(AVLTreeNode* pTree) {
	if (pTree == NULL) {
		return;
	}

	if (pTree->pLeftTree != NULL) {
		destroy_AVLTree(pTree->pLeftTree);
	}

	if (pTree->pRightTree != NULL) {
		destroy_AVLTree(pTree->pRightTree);
	}

	my_string_destroy(&pTree->family_key);
	g_vector_destroy(&pTree->pVector);
	pTree->pLeftTree = NULL;
	pTree->pRightTree = NULL;
	free(pTree);
	pTree = NULL;
}
