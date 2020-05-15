#include <string.h>
#include "dictionary.h"

/**********************
FUNCTION TO SPELL CHECK
**********************/

// This function will check if the words from the text file matches the words in
// the dictionary tree. If it does, return CORRECT. If it doesn't, return MISSPELLED
ResultType find(struct dictentry *dictnode, const char *word, const char *targetword){
	
	if(*word != '\0'){
		dictnode = dictnode->next[*word - 'a'];
		// if the end of path of the dictionary tree is reached
		// meaning word is invalid therfore misspelled
		if(dictnode == NULL)
			return MISSPELLED;	
		// recursive call with next node and next character
		return find(dictnode, ++word, targetword);

	}

	// if isEndOfWord flag is true, the word matches, if not
	// it is misspelled
	if(dictnode->isEndOfWord)
		return CORRECT;
	else 
		return MISSPELLED;

	//return BADCHARS;
}

/************************************************
FUNCTION TO INSERT WORDS INTO THE DICTIONARY TREE
************************************************/

// This function will insert words into the dictionary tree, if not present,
// and return ADDED and mark the isEndOfWord flag as true
ResultType insert(struct dictentry *dictnode, const char *characters, const char *targetword){

	if(*characters != '\0'){
		int i;
		// create a new node if there is no path in the dictionary tree
		if(dictnode->next[*characters - 'a'] == NULL){
			dictnode->next[*characters - 'a'] = malloc(sizeof(struct dictentry));
			for(i = 0; i < Nchars; ++i)
				dictnode->next[*characters - 'a']->next[i] = NULL;
			dictnode->next[*characters - 'a']->isEndOfWord = false;
		}
				
		// recursive call with the next node and next character
		dictnode = dictnode->next[*characters - 'a'];
		return insert(dictnode, ++characters, targetword);
	}
	
	// when word is inserted, isEndOfWord flag is true and return ADDED
	dictnode->isEndOfWord = true;
	return ADDED;

	//return EXISTS;
}


