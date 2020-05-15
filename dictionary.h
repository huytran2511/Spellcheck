#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Nchars 27 /* a-z + ' */

struct dictentry
{
	bool isEndOfWord;
	struct dictentry *next[Nchars];
};

typedef enum {
	CORRECT,
	MISSPELLED,
	BADCHARS,
	ADDED,
	EXISTS
} ResultType;


ResultType find(struct dictentry *dictnode, const char *word, const char *targetword);

ResultType insert(struct dictentry *dictnode, const char *characters, const char *targetword);

#endif
