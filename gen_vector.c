#include <stdio.h>
#include <stdlib.h>
#include "gen_vector.h"

Status MyString_assign(Item_ptr phLeft, Item hRight) {
	My_string** phLeft_ass = (My_string**)phLeft;
	My_string* hRight_ass = (My_string*)hRight;
	Status sta = my_string_assignment(phLeft_ass, hRight_ass);
	return sta;
}

void MyString_destroy(Item_ptr phLeft) {
	My_string* pLeft = (My_string*)*phLeft;
	my_string_destroy(&pLeft); //free(pLeft);
	*phLeft = NULL;
}

G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item),void (*item_destroy)(Item_ptr)) {
	G_Vector* pVector = NULL;
	int i;
	pVector = (G_Vector*)malloc(sizeof(G_Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->item_assign = item_assign;
		pVector->item_destroy = item_destroy;
		pVector->myString = (Item_ptr)malloc(sizeof(void*)* pVector->capacity);
		if (pVector->myString == NULL) {
			free(pVector);
			pVector = NULL;
		}
		else {
			for (i = 0; i < pVector->capacity; ++i)
				pVector->myString[i] = NULL;
		}
	}
	return pVector;
}
//use vector
int g_vector_get_capacity(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->capacity;
}
int g_vector_get_size(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	return pVector->size;
}
Status g_vector_push_back(G_VECTOR hG_Vector, Item item) {
	G_Vector* pG_Vector = (G_Vector*)hG_Vector;
	Item_ptr temp;
	int i;
	if (pG_Vector->size >= pG_Vector->capacity) {
		temp = (Item_ptr)malloc(sizeof(Item) * 2* pG_Vector->capacity );
		if (temp == NULL) {
			return FAILURE;
		}

		for (i = 0; i < pG_Vector->capacity; ++i) {
			temp[i] = pG_Vector->myString[i];
		}

		pG_Vector->capacity *= 2;

		for (i = pG_Vector->size; i < pG_Vector->capacity; ++i) {
			temp[i] = NULL;
		}

		free(pG_Vector->myString);
		pG_Vector->myString = temp;
	}
	pG_Vector->item_assign(&pG_Vector->myString[pG_Vector->size],item);
	pG_Vector->size++;
	return SUCCESS;
}
Status g_vector_pop_back(G_VECTOR hG_Vector) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (pVector->size <= 0)
		return FAILURE;
	pVector->size--;
	return SUCCESS;
}
Item g_vector_at(G_VECTOR hG_Vector, int index) {
	G_Vector* pVector = (G_Vector*)hG_Vector;
	if (index < 0 || index >= pVector->size)
		return NULL;

	return pVector->myString[index];
}
//destroy
void g_vector_destroy(G_Vector** phG_Vector) {
	G_Vector* pVector = (G_Vector*)* phG_Vector;
	int i;

	for (i = 0; i < pVector->capacity; ++i) {
		if (pVector->myString[i] != NULL)
			pVector->item_destroy(&pVector->myString[i]);
	}
	free(pVector->myString);
	free(pVector);
	*phG_Vector = NULL;
}


/****************g_vector_array*******************/
G_VECTOR_ARRAY g_vector_array_init_default() {
	G_Vector_Array* pVector_array = NULL;
	pVector_array = (G_Vector_Array*)malloc(sizeof(G_Vector_Array));
	if (pVector_array != NULL) {
		for (int i = 0; i < 30; i++) {
			G_VECTOR vec = g_vector_init_default(MyString_assign, MyString_destroy);
			pVector_array->vector_array[i] = (G_Vector*)vec;
			if (pVector_array->vector_array[i] == NULL) {
				free(pVector_array);
				pVector_array = NULL;
			}
		}
	}
	return pVector_array;
}

void g_vector_array_destroy(G_VECTOR_ARRAY* phG_Vector_Array) {
	G_Vector_Array* pVector_array = (G_Vector_Array*)* phG_Vector_Array;
	int i;

	for (i = 0; i < 30; ++i) {
		g_vector_destroy(&pVector_array->vector_array[i]);
	}
	free(pVector_array);
	*phG_Vector_Array = NULL;
}
