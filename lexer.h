// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef LEXER 
#define LEXER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lexerDef.h"

//lexer functions
void fill_symbol_table(hashtable_st* searchtable);
FILE* getStream(FILE* fp,char* buffer);
tokenInfo* getNextToken(FILE* fp, hashtable_st* search_table);
void errorhandler(int error,tokenInfo* newtoken);
int printcommentfree(char *testcaseFile);
int strCMP(char* str1,char* str2);

//hash functions

hashtable_st* createHastable(int size);
int hashfunction(int mod,char* str);
void addinlinkedlist2(linkedlist2* ls,char* str,int index);
void addinhashtable(hashtable_st *ht,char* str,int index);
int searchhashtable(hashtable_st *ht,char* str);

#endif
