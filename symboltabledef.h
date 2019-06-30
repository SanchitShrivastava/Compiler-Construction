// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P


#ifndef SYMBOLTABLEDEF
#define SYMBOLTABLEDEF



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

struct list
{
	char* value;
	void* data;
	int offset;
	struct list* next;
};
struct hashtable
{
	int size;
	int offset;
	int slots;
	struct list** table;
	struct listnasm* head;
	struct listnasm* tail;
};
struct function_st
{
	int position;
	struct list* input;
	struct list* output;
	struct hashtable* variable;
};

struct listnasm
{
	char* name;
	char * type;
	struct listnasm* next;
};
struct listhash
{
	struct hashtable* h;
	int check;
	struct listhash* next;
};
typedef struct listhash listhash;
typedef struct listnasm listnasm;
typedef struct function_st function_st;
typedef struct list list;
typedef struct hashtable hashtable;
char** errorlist;
hashtable* func;
hashtable* globalvar;
hashtable* record;
hashtable* variable;

#endif
