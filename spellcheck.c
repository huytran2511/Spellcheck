/****************************
*****************************
Name: Huy Tran
Red ID: 818608122

CS-570
a01
spellcheck.c
*****************************
*****************************/

#include <string.h>
#include <ctype.h>
#include "dictionary.h"

int main(int argc, char **argv){
			
	// exit program if there are wrong number of arguments
	if(argc != 3){
		printf("wrong number of arguments! Please enter 2 file paths\n");
		return -1;
	}

	// open the text file to be checked for spelling
	FILE *fp1 = fopen(argv[1], "r");

	// open dictionary source text file
	FILE *fp2 = fopen(argv[2], "r");

	// exit program if both files don't exist
	if(fp1 == NULL && fp2 == NULL){
		printf("Both text files don't exist!\n");
		return -1;
	}	

	// exit program if text file to be checked for spelling doesn't exist
	if(fp1 == NULL){
		printf("Text file to be checked for spelling does not exist!\n");
		return -1;
	}

	// exit program if dictionary source file doesn't exist
	if(fp2 == NULL){
		printf("Dictionary source file does not exist!\n");
		return -1;
	}	
	
	/**************************************************
	READ DICTIONARY SOURCE TEXT FILE TO BUILD DICTENTRY
	**************************************************/

	// initialize an array to hold the lines reading in
	// with an appropriate size for anticipated length 
	char line2[50];
	
	const char *separators = "\n\r !\"#$%&()*+,-./0123456789:;<=>?@[\\]^_`{|}~";
							 
	// create the root for the dictionary tree
	struct dictentry *root =  malloc(sizeof(struct dictentry));
	int i;
	for(i = 0; i < Nchars; ++i)
		root->next[i] = NULL;
	root->isEndOfWord = false;
	
	// read each line to a char buffer
	while(fgets(line2, sizeof(line2), fp2) != NULL){
		// extract words from each line read in
		char *token2 = (char*)strtok(line2, separators);

		while(token2 != NULL){
			// insert the extracted tokens into the dictionary tree
			insert(root,token2,token2);

			// get the next token from the line_c buffer
			token2 = strtok(NULL, separators);
		}
	}

	// close the dictionary source text file stream
	fclose(fp2);

	/****************************************
	READ TEXT FILE TO BE CHECKED FOR SPELLING
	****************************************/

	// initialize an array to hold the lines reading in
	// with an appropriate size for anticipated length
	char line1[100];
	
	// read each line to a char buffer
	while(fgets(line1, sizeof(line1), fp1) != NULL){
		// extract words from each line read in
		char *token1 = (char*)strtok(line1, separators);
		
		while(token1 != NULL){
			// initialize char pointer and allocate memory
			char *temp = malloc(50);
			
			// use temp to hold a copy of the extracted tokens
			strcpy(temp,token1);
			
			// convert extracted tokens to lowercase because we want
			// to spell check with case-insensitive
			int i;
			for(i = 0; token1[i]; ++i){
				token1[i] = tolower(token1[i]);
			}
			
			// perform spell checks on the converted tokens and print out the 
			// misspelled words using the temp holding the original tokens
			if(find(root,token1,token1) == MISSPELLED){
				printf("%s\n", temp);
			}

			// get the next token from the line_c buffer						
			token1 = strtok(NULL, separators);

			//deallocates the memory for temp
			free(temp);
		}
	}

	// close the spell checking text file stream
	fclose(fp1);
	
	return 0;
}
