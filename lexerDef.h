// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef LEXERDEF 
#define LEXERDEF

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define Bufferlen 200

//structure for token
struct tokenInfo
{
	int lineNo;
	char* lexeme_value;
	int token_id;
	int status;
};

typedef struct tokenInfo tokenInfo;

//structure for hash function
struct node2 // node in the linkedlist of hashtable
{
	char* str;
	int index;
	struct node2* next;
};

typedef struct node2 node2;

struct linkedlist2 // linkedlist for the hashtable
{
	int size;
	struct node2* root;
};

typedef struct linkedlist2 linkedlist2;

struct hashtable_st //hashtable for searching eg. TK_MAIN and <singleorRecid>
{
	int size;
	linkedlist2 **arr;
};

typedef struct hashtable_st hashtable_st;

char* buffer0;
char* buffer1;
int lineNo;
int* currIndex;
hashtable_st* symbol_table;
int checkbuffer;
int showerror;
int showcomment;

#endif
