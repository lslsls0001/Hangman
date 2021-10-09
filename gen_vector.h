#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

typedef void* G_VECTOR;

typedef void* G_VECTOR_ARRAY;

struct g_vector {
	int size;
	int capacity;
	Item_ptr myString;
	Status(*item_assign)(Item_ptr, Item);
	void (*item_destroy)(Item_ptr);
};

typedef struct g_vector G_Vector;

struct g_vector_array {
	G_Vector* vector_array[30];
};

typedef struct g_vector_array G_Vector_Array;

//init
G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item),void (*item_destroy)(Item_ptr));

//use vector
int g_vector_get_capacity(G_VECTOR hG_Vector);
int g_vector_get_size(G_VECTOR hG_Vector);
Status g_vector_push_back(G_VECTOR hG_Vector, Item item);  //insert new item
Status g_vector_pop_back(G_VECTOR hG_Vector);
Item g_vector_at(G_VECTOR hG_Vector, int index);
//destroy
void g_vector_destroy(G_Vector** phG_Vector); 

Status MyString_assign(Item_ptr, Item);
void MyString_destroy(Item_ptr);

//init for g_vector_array
G_VECTOR_ARRAY g_vector_array_init_default(void);

//destroy for g_vector_array
void g_vector_array_destroy(G_VECTOR_ARRAY* phG_Vector_Array);
