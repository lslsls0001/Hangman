#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "my_string.h"

MY_STRING my_string_init_default(void) {
	My_string* pMy_string = NULL;
	pMy_string = (My_string*)malloc(sizeof(My_string));
	if (NULL != pMy_string) {
		pMy_string->capacity = 7;
		pMy_string->size = 0;
		pMy_string->str = (char*)malloc(sizeof(char) * pMy_string->capacity);

		if (NULL == pMy_string->str) {
			free(pMy_string);
			pMy_string = NULL;
		}
		return pMy_string;
	}
	else {
		return NULL;
	}
}

MY_STRING my_string_init_c_string(const char* c_string) {
	int len = strlen(c_string);

	My_string* pMy_string = NULL;
	pMy_string = (My_string*)malloc(sizeof(My_string));
	if (NULL != pMy_string) {
		pMy_string->capacity = len + 1;
		pMy_string->size = len;
		pMy_string->str = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if (NULL != pMy_string->str) {
			int i;
			for (i = 0; *(c_string + i) != '\0'; i++) {
				pMy_string->str[i] = *(c_string + i);
			}
			pMy_string->str[i] = '\0';
			return pMy_string;
		}
		else {
			free(pMy_string);
			pMy_string = NULL;
			return pMy_string;
		}
	}
	else {
		return NULL;
	}
}

int my_string_get_capacity(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
	My_string* left_str = (My_string*)hLeft_string;
	My_string* right_str = (My_string*)hRight_string;
	int status = -2;

	if (NULL != left_str && NULL != right_str) {
		for (int i = 0; i <= left_str->size && i <= right_str->size; i++) {
			if (left_str->str[i] < right_str->str[i]) {
				status = -1;
				return status;
			}
			else if (left_str->str[i] > right_str->str[i]) {
				status = 1;
				return status;
			}
			else {
				if (i == left_str->size && i < right_str->size) {
					status = -1;
					return status;
				}
				if (i == right_str->size && i < left_str->size) {
					status = 1;
					return status;
				}
				if (i == right_str->size && i == left_str->size) {
					status = 0;
					return status;
				}
			}
		}
	}
	return status;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	My_string* pMy_string = (My_string*)hMy_string;
	
	char c;
	int len = 0;
	int flag = 0;

	while ((c = fgetc(fp)) != EOF ) {
		if (isspace(c)) {
			if (flag == 1) {
				ungetc(c,fp);
				pMy_string->size = len;
				return SUCCESS;
			}
			continue;
		}
		else {
			pMy_string->str[len] = c;
			//printf("%c", pMy_string->str[len]);
			len++;
			if (len == pMy_string->capacity) {
				char* temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
				if (NULL != temp) {
					for (int i = 0; i < len; i++) {
						temp[i] = pMy_string->str[i];
					}
					free(pMy_string->str);
					pMy_string->str = temp;
					pMy_string->capacity = pMy_string->capacity * 2;
				}
				else {
					return FAILURE;
				}
			}
			flag = 1;
		}
	};

	return FAILURE;

}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	My_string* pMy_string = (My_string*)hMy_string;

	int len;
	int status;
	int count = 0;

	for (len = 0; len < pMy_string->size; len++) {
		status = fputc(pMy_string->str[len], fp);
		if (status != EOF) {
			count++;
		}
	}

	if (count == pMy_string->size) {
		return SUCCESS;
	}
	else {
		return FAILURE;
	}
}

void my_string_destroy(My_string** pItem) {
	My_string* pMy_string = (My_string*)(*pItem);
	free(pMy_string->str);
	pMy_string->str = NULL;
	free(pMy_string);
	pMy_string = NULL;
	*pItem = NULL;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;

	if (pMy_string->size >= pMy_string->capacity) {
		temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
		if (temp == NULL) {
			return FAILURE;
		}
		for (int i = 0; i < pMy_string->capacity; i++) {
			temp[i] = pMy_string->str[i];
		}
		free(pMy_string->str);
		pMy_string->str = temp;
		temp = NULL;
		pMy_string->capacity *= 2;
	}
	pMy_string->str[pMy_string->size] = item;
	pMy_string->size++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size <= 0) {
		return FAILURE;
	}
	pMy_string->size--;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
	My_string* pMy_string = (My_string*)hMy_string;
	if (index < 0 || index >= pMy_string->capacity) {
		return NULL;
	}
	return &pMy_string->str[index];
}

char* my_string_c_str(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;

	if (pMy_string->size >= pMy_string->capacity) {
		temp = (char*)malloc(sizeof(char) * (pMy_string->size + 1));
		if (temp == NULL) {
			return NULL;
		}
		for (int i = 0; i < pMy_string->capacity; i++) {
			temp[i] = pMy_string->str[i];
		}
		free(pMy_string->str);
		pMy_string->str = temp;
		temp = NULL;
		pMy_string->capacity = pMy_string->size + 1;
	}
	pMy_string->str[pMy_string->size] = '\0';
	return &pMy_string->str[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	My_string* pMy_string_res = (My_string*)hResult;
	My_string* pMy_string_app = (My_string*)hAppend;
	char* temp;
	int len = pMy_string_res->size + pMy_string_app->size;

	if (len > 0 && len < pMy_string_res->capacity) {
		for (int i = pMy_string_res->size; i < len; i++) {
			pMy_string_res->str[i] = pMy_string_app->str[i - pMy_string_res->size];
		}
		pMy_string_res->str[len] = '\0';
		pMy_string_res->size = len;
		return SUCCESS;
	}
	else if (len >= pMy_string_res->capacity) {

		temp = (char*)malloc(sizeof(char) * (len + 1));
		if(temp == NULL) {
			return FAILURE;
		}
		for (int i = 0; i < len; i++) {
			if (i < pMy_string_res->size && i >= 0) {
				temp[i] = pMy_string_res->str[i];
			}
			if (i >= pMy_string_res->size && i < len) {
				temp[i] = pMy_string_app->str[i - pMy_string_res->size];
			}
		}

		temp[len] = '\0';
		free(pMy_string_res->str);
		pMy_string_res->str = temp;
		temp = NULL;
		pMy_string_res->size = len;
		pMy_string_res->capacity = len + 1;
		return SUCCESS;
	}
	else {
		return FAILURE;
	}
}

Boolean my_string_empty(MY_STRING hMy_string) {
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size <= 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

Status my_string_assignment(My_string** pLeft, My_string* Right) {
	My_string* pLeft_string = (My_string*)*pLeft;
	My_string* pRight_string = (My_string*)Right;
	if (pLeft_string == NULL) {
		pLeft_string = (My_string*)malloc(sizeof(My_string));
		if (pLeft_string == NULL) {
			printf("Failed to assign\n");
			pLeft_string = NULL;
			pLeft = NULL;
			return FAILURE;
		}
		else {
			pLeft_string->size = pRight_string->size;
			pLeft_string->capacity = pRight_string->capacity;
			pLeft_string->str = (char*)malloc(sizeof(char)* pLeft_string->capacity);

			for (int i = 0; i < pLeft_string->size; i++) {
				pLeft_string->str[i] = pRight_string->str[i];
			}
	
			pLeft_string->str[pLeft_string->size] = '\0';
		}
	}
	else {
		pLeft_string->size = pRight_string->size;
		pLeft_string->capacity = pRight_string->capacity;
		free(pLeft_string->str);
		pLeft_string->str = (char*)malloc(sizeof(char) * pLeft_string->capacity);
		if (pLeft_string->str == NULL) {
			printf("assign string failure!");
			return FAILURE;
		}

		for (int i = 0; i < pLeft_string->size; i++) {
			pLeft_string->str[i] = pRight_string->str[i];
		}
		
		pLeft_string->str[pLeft_string->size] = '\0';
	}
	*pLeft = pLeft_string;
	return SUCCESS;
}



