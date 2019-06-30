// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef SYMBOLTABLE
#define SYMBOLTABLE


#include "symboltabledef.h"

void printarray();
void errorlisttable();
hashtable* generatehashtable(int slots);
void insertelement1(char* value,function_st* data,hashtable* h,int position);
void insertelement2(char* value,void* data,hashtable* h,int offset);
void insertelement3(char* value,void* data,hashtable* h);
void* findelement(char* value,hashtable* h);
int function(int mod,char* str);
void fillsymboltable(astNode* root);
void fillsymboltable1(astNode* root);
void maintable(astNode* root);
void maintable1(astNode* root);
void printglobalvar(hashtable* h);
function_st* create_function_st_node();
void functiontable(astNode* root,char* name);
void functiontable1(astNode* root,char* name);
list* generatelist();
void printvar1(hashtable* h);
void recordprint();

list* fill_list(astNode* root,hashtable* h);
void fill_record(astNode* root);
void fill_variable(astNode* root,hashtable* h);
void printfunc();
void printvar(hashtable* h);
void printrecord();
void insertlist(char* name,char* type,hashtable* h);
listnasm* mainvariable();
listnasm* recordvarible(char *type);
void printnasmlist(listnasm* l);
listnasm* funclist();
listnasm* globalvariable();
int findoffset(char* value,hashtable* h);
void printsymboltable();
void verifysymboltable(astNode* root,char* c);
void whilecheck(astNode* root,listhash* li,char* c);
void traverse(astNode* root,hashtable* h,char* c);
void traverse1(astNode* root,listhash* l,char* c);
listhash* generatelisthash(hashtable* h);
void assignmentwhilecheck(astNode* root,listhash* l,char* c);
int justfind(char* value,hashtable* h);
void verifyallsymboltable(astNode* root);
void assignmentcheck(astNode* root,char* c);
void assignmentcheckutil(astNode* root,char* d,char* c);
void conditionalwhilecheck(astNode* root,listhash* l,char* c);
void io1whilecheck(astNode* root,listhash* l,char* c);
void funcwhilecheck(astNode* root,listhash* l,char* c);
void funccheck(astNode* root,char* c);
void io2check(astNode* root,char* c);
void io1check(astNode* root,char* c);
char* determinetype(int line,char* value,char* c);
char* determinetype1(char* value,char* c);
void conditionalcheck(astNode* root,char* c);
void matchformalinformal(list* l,astNode* root,char* c);
void functiontable0(astNode* root,char* name);
void maintable0(astNode* root);
void fillsymboltable0(astNode* root);
void fill_variable0(astNode* root,hashtable* h);
void functionsize();

#endif