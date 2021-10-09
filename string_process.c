#include <stdio.h>
#include <stdlib.h>
#include "string_process.h"

My_string* family_key_generation(My_string* My_word_string, My_string* Family_key_module, char letter) {

	int count = 0;
	while (count < My_word_string->size) {
		if (Family_key_module->str[count] == '_') {
			if (letter == My_word_string->str[count]) {
				Family_key_module->str[count] = letter;
			}
		}
		count++;
	}

	return Family_key_module;
}

int compare_family_key(My_string * family_key) {
	int count = 0;
	for (int i = 0; i < family_key->size; i++) {
		if (family_key->str[i] != '_') {
			count++;
		}
	}

	if (count == family_key->size) {
		return 1;
	}
	else {
		return 0;
	}
}

int Array_Max_Value(int* size) {

	int max = size[0];
	int i = 0;
	int subs = 0;
	for (i = 0; i < 150; i++)
	{
		if (max < size[i])
		{
			max = size[i];
			subs = i;
		}
	}

	return subs;
}

int Array_Second_Max_Value(int* size) {
	int max = size[0];
	int subsMax = Array_Max_Value(size);
	int i = 0;
	int subs = 0;
	if (subsMax == subs) {
		max = size[1];
		subs = 1;
		for (i = 1; i < 150; i++) {
			if (max < size[i]) {
				max = size[i];
				subs = i;
			}
		}
	}
	else {
		for (i = 0; i < 150; i++) {
			if (max < size[i]) {
				if (size[subsMax] == size[i]) {
					continue;
				}
				max = size[i];
				subs = i;
			}
		}
	}

	return subs;
}



