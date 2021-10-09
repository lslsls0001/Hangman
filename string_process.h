#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

My_string* family_key_generation(My_string* My_word_string, My_string* Family_key_module, char letter);

int compare_family_key(My_string* family_key);

int Array_Max_Value(int* size);

int Array_Second_Max_Value(int* size);