#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "AVL_tree.h"
#include "string_process.h"

int main(int argc, char* argv[]) {

	char playAgain = 'Y';
	while (playAgain == 'Y' || playAgain == 'y') {
		/*********************************init_setup****************************************/
		//file open and init My_String
		FILE* fread = NULL;

		fread = fopen("dictionary.txt", "r");
		if (fread == NULL)
		{
			perror("mistake happens when open file!");
			return(-1);
		}

		MY_STRING hMy_string = NULL;
		hMy_string = my_string_init_default();

		//init vector array
		G_VECTOR_ARRAY hG_Vector_Array = NULL;
		hG_Vector_Array = g_vector_array_init_default();
		G_Vector_Array* hG_vector_array = (G_Vector_Array*)hG_Vector_Array;

		if (hG_vector_array == NULL) {
			printf("Can not creat a vector array\n");
			exit(1);
		}

		//assign the word of each length to associated word family

		while (my_string_extraction(hMy_string, fread)) {
			My_string* pMy_string = (My_string*)hMy_string;
			g_vector_push_back(hG_vector_array->vector_array[pMy_string->size], pMy_string);
		}

		//print each word on screen, one by one line
		/*for (int i = 1; i < 30; ++i) {
			int count = 0;
			while (count < g_vector_get_size(hG_vector_array->vector_array[i])) {
				printf("%s\n", ((My_string*)g_vector_at(hG_vector_array->vector_array[i], count))->str);
				count++;
			}
		}*/

		for (int i = 1; i < 30; i++) {
			printf("The word length = %d, word family size = %d\n", i, g_vector_get_size(hG_vector_array->vector_array[i]));
		}

		/****************************** The Hangman Game Begins *******************************************/

		printf("****************************************************************************\n");
		printf("************************** The Hangman Game Begins *************************\n");
		printf("****************************************************************************\n");
		printf("\n");
		printf("Please input a word length between 1 and 29 (avoid 23/25/26/27), system will let you know your input is vaild or not!\n");	//remind user to select the word length
		printf("\n");

		//input the word length.
		int wordLength;
		printf("The word length = ");
		while (scanf("%d", &wordLength) == 0 || wordLength < 2 || wordLength > 29 || wordLength == 23
			|| wordLength == 25 || wordLength == 26 || wordLength == 27) { //if input is a number then scanf function should return 1, otherwise 0;
			while (getchar() != '\n');     //if input a character, then getchar() to remove the chracter, otherwise will be dead loop.

			printf("Your input is not a correct number, please input again:\n");
			printf("\n");
			printf("The word length = ");
		}
		printf("What you enter is: %d\n", wordLength);

		printf("\n");
		printf("Please input a guess number between 1 and 26, system will let you know your input is vaild or not!\n");	//remind user to enter the guess number
		printf("\n");

		//input the number of guess
		int guessNum;
		printf("The guess number = ");
		while (scanf("%d", &guessNum) == 0 || guessNum < 1 || guessNum > 26) { //if input is a number then scanf function should return 1, otherwise 0;
			while (getchar() != '\n');

			printf("Your input is not a correct number, please input again:\n");
			printf("\n");
			printf("The guess number = ");
		}
		printf("What you enter is: %d\n", guessNum);

		printf("\n");
		printf("Please confirm you want to see how many words remaining or not, system will let you know your input is vaild or not!\n");	//remind user to select whether he/she wants to see how many words remaining.
		printf("\n");

		//ask user whether he/she wants to see the words remaining
		char wordRemaining;
		printf("Wether you want to see total number of words remaining after each guess? (Y/N)");
		while (getchar() != '\n');
		while (scanf("%c", &wordRemaining) == 0 || (wordRemaining != 'Y' && wordRemaining != 'y' && wordRemaining != 'N' && wordRemaining != 'n')) {

			while (getchar() != '\n');

			printf("Your input is not a correct character, please input again:");
			printf("\n");
			printf("Wether you want to see total number of words remaining after each guess? (Y/N)");
		}
		printf("What you enter is: %c\n", wordRemaining);

		printf("\n");

		/***********build the family key, create node in AVL tree, tree self balance, and return************/

		int family_key_status = 0; //to judege the family key (with '_' means 0 or without '_' means 1).

		My_string* usedLetter = my_string_init_c_string(":"); // create a string to store the used letter.

		G_Vector* selectedVector = hG_vector_array->vector_array[wordLength]; //This is the word family vector with certain word length.

		int subsMax = 0; //init the subscript of the max size of family_key array.

		//create a family_key_module to store the init characters of family key "_______"
		char* family_key_module = (char*)malloc(sizeof(char) * (wordLength + 1));
		if (family_key_module == NULL) {
			printf("family_key_module creates failure!");
		}
		int i;
		for (i = 0; i < wordLength; i++) {
			family_key_module[i] = '_';
		}
		family_key_module[i] = '\0';

		My_string* Family_key_module = (My_string*)my_string_init_c_string(family_key_module); //'\0' is added.

		My_string* Family_key_init = (My_string*)my_string_init_c_string(family_key_module); //store the init value of family key

		int family_key_size[300] = { 0 }; //store the init size value of family key array

		G_VECTOR family_key_vector = g_vector_init_default(MyString_assign, MyString_destroy); //create a family key vector to store all family key string

		G_VECTOR target_vector = g_vector_init_default(MyString_assign, MyString_destroy); //create a target vector to store the target family key string
		//*************One game begins with certain word length*******************.
		while (guessNum != 0 && family_key_status != 1) {
			//step 1: ask user which letter he/she want to guess 

			char letter;
			printf("Please enter the letter you want to guess:");
			while (getchar() != '\n');
			while (!(scanf("%c", &letter) == 1 && ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')))) {

				while (getchar() != '\n');

				printf("Your input is not a correct character, please input again:\n");
				printf("\n");
				printf("The letter is:");
			}
			printf("What you enter is %c\n", letter);

			printf("\n");

			//step 2: guessNum minus one
			guessNum = guessNum - 1;
			//printf("You have %d guesses left.\n", guessNum);

			//step 3: An character array to store the letters user chooses.
			
			my_string_push_back(usedLetter, letter);

			printf("Used letters:\t");

			for (int i = 1; i < usedLetter->size; i++) {
				printf("%c\t", usedLetter->str[i]);
			}

			printf("\n");

			//if letter is upper case, then it should be stored as lower case.
			if (letter >= 'A' && letter <= 'Z') {
				letter = letter + 32;
			}

			//step 4:create a tree node here, add more nodes if family keys are different, input the word one by one, rotate the node if subtree height is larger than 1

			int count = 0;
			AVLTreeNode* pTree = NULL;
			My_string* My_word_input = NULL; //create a new My_string to store the key word;

			while (count < selectedVector->size) {
				My_string* My_word = (My_string*)g_vector_at(selectedVector, count);

				//copy the My_word string to My_word_input string.
				my_string_assignment(&My_word_input, My_word);

				//generate the family key
				Family_key_module = family_key_generation(My_word, Family_key_module, letter);

				//printf("%s: %s\n", My_word_input->str, Family_key_module->str); // print each word and associated family key.

				//put My_word_input object and Family_key into AVLTree_insert
				//if family key is equal, copy the My_word_input string to proper Node, if not equal, create a new treeNode, then rotate as necessary.
				pTree = AVLTree_insert(pTree, Family_key_module, My_word_input);
	
				my_string_assignment(&Family_key_module, Family_key_init); //reinit the Family_key_module to generate a next family key

				count++;
			}

			//step 5:preorder search the whole AVL tree, collect the family key and size of each family key.

			preorder_AVLTree(pTree, family_key_size, family_key_vector); //output the family key with size
			G_Vector* family_key_vec = (G_Vector*)family_key_vector;

			//step 6: collect all family_key size in an array, then pick the one with maximum size.

			subsMax = Array_Max_Value(family_key_size);

			//if only one Node in pTree, and the family key of this node without target letter, meaning no target letter found in this search.
			//if (family_key_vec->size == 1 && my_string_compare(family_key_vec->myString[subsMax], Family_key_init) == 0) {
			//	printf("I am sorry, there were no %c's in the word!\n", letter);
			//}

			//if more than one Node in pTree, but the Max number of Node is the family key without target letter, then should pick the second Max.
			//if (family_key_vec->size > 1 && my_string_compare(family_key_vec->myString[subsMax], Family_key_init) == 0) {
				//pick the subscript of the Max element.
			//	subsMax = Array_Second_Max_Value(family_key_size);
			//}

			//if more than one Node in pTree, and the Max number of Node is the family key with the target letter
			//if (family_key_vec->size > 1 && my_string_compare(family_key_vec->myString[subsMax], Family_key_init) != 0) {
			//	subsMax = subsMax;
			//	guessNum = guessNum + 1; // if user guess the right letter, then the guessNum will be resotre, this statement can be removed!!
			//}

			//make sure we choose the one with max size, including the one without any target letter for evil Hangman purpose
			if (my_string_compare(family_key_vec->myString[subsMax], Family_key_init) == 0) {
				subsMax = subsMax;
			}

			//step 7: create a new family_key_module, and copy the target vector array to selectedVector.
			//create a new family_key_module.
			int j;
			for (j = 0; j < ((My_string*)family_key_vec->myString[subsMax])->size; j++) {
				family_key_module[j] = ((My_string*)family_key_vec->myString[subsMax])->str[j];
			}
			family_key_module[j] = '\0';

			my_string_destroy(&Family_key_module);//delete the old Family_key_module
			Family_key_module = (My_string*)my_string_init_c_string(family_key_module);

			my_string_destroy(&Family_key_init);//delete the old Family_key_init
			Family_key_init = (My_string*)my_string_init_c_string(family_key_module);

			//copy the target vector to the new one.
			AVLTreeNode* pTreeSub = AVLTree_search(pTree, family_key_vec->myString[subsMax]);

			//destory the G_VECTOR target_vector

			G_Vector* target_vector_des = (G_Vector*)target_vector;
			g_vector_destroy(&target_vector_des);

			target_vector = g_vector_init_default(MyString_assign, MyString_destroy);
			G_Vector* target_vec = (G_Vector*)target_vector;
			for (int i = 0; i < pTreeSub->pVector->size; i++) {

				g_vector_push_back(target_vec, pTreeSub->pVector->myString[i]);
			}
			selectedVector = target_vec;

			//step 8, show the user option, judge the family_key_status, and destory the tree.
			//show the how many words remaining or not
			if (wordRemaining == 'Y' || wordRemaining == 'y') {
				printf("The computer has %d possibilities remaining.\n", family_key_size[subsMax]);
				printf("The family key that system selected is: %s\n", Family_key_init->str);  //print the family key that system selected.
			}

			printf("You have %d guesses left.\n", guessNum); // tell the user how many guessNum he/she can use to guess a correct letter.

			//compare the each bit of family_key with '_', if no '_', then game finish.
			family_key_status = compare_family_key(family_key_vec->myString[subsMax]);

			if (family_key_status == 1) {
				printf("Congratulation!!!, you win the game! The word you choose is: %s\n", ((My_string*)(family_key_vec->myString[subsMax]))->str);
				g_vector_destroy(&selectedVector);
				my_string_destroy(&Family_key_module);
				my_string_destroy(&Family_key_init);
			}

			//if user did not guess the correct word and the guess number is equal to 0, say sorry to him/her.
			if (family_key_status != 1 && guessNum == 0) {
				printf("I am sorry, you have run out of all guesses!!!\n");
				printf("The word system selected is: %s\n", ((My_string*)(selectedVector->myString[0]))->str); //system randomly chooses the first string of MyString as the correct word!
				g_vector_destroy(&selectedVector);
				my_string_destroy(&Family_key_module);
				my_string_destroy(&Family_key_init);
			}

			//destory the My_string* My_word_input 
			my_string_destroy(&My_word_input);

			//destory the temp vector and size collection

			G_Vector* family_key_vector_des = (G_Vector*)family_key_vector;
			g_vector_destroy(&family_key_vector_des);
			family_key_vector = g_vector_init_default(MyString_assign, MyString_destroy); //then create a new family_key_vector

			//destory the AVLTree
			destroy_AVLTree(pTree);

			//family_key_size clear to 0;
			for (int i = 0; i < 300; i++) {
				family_key_size[i] = 0;
			}
		}

		//destory the vector array, close file.
		g_vector_array_destroy(&hG_Vector_Array);

		G_Vector* family_key_vector_final = (G_Vector*)family_key_vector;
		g_vector_destroy(&family_key_vector_final);

		My_string* hMy_string_des = (My_string*)hMy_string;
		my_string_destroy(&hMy_string_des);

		my_string_destroy(&usedLetter);

		fclose(fread);

		free(family_key_module);

		//ask user whether he/she wants to play the game again?
		printf("Do you want to play the game again?(Y/N)\n");
		while (getchar() != '\n');
		while (scanf("%c", &playAgain) == 0 || (playAgain != 'Y' && playAgain != 'y' && playAgain != 'N' && playAgain != 'n')) {

			while (getchar() != '\n');

			printf("Your input is not a correct character, please input again:");
			printf("\n");
			printf("Do you want to play the game again?(Y/N)\n");
		}
		printf("What you enter is: %c\n", playAgain);

		printf("\n");

		if (playAgain == 'N' || playAgain == 'n') {
			break;
		}
	}
	
	return 0;
}
