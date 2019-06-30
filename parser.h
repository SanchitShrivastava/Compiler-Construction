// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef PARSER
#define PARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "parserDef.h"
#include "lexer.h"

//grammar functions
void addinlinkedlist(linkedlist *ls,int val,int status);
void addinrules_st(Grammar *G,int val,int status,int i);
void addinlinkedlist3(linkedlist3 *ls,int ruleno);
void addrulenoinnon_terminals_st(Grammar *G,int ruleno,int i);
void addinnonterminals_st(Grammar *G,char* str);
void addinterminals_st(Grammar *G,char* str);
Grammar* createGrammar();
int handleremaining(Grammar *G,char *buf,int i,int ruleno);
void addtoGrammar(Grammar *G,char* buf);
Grammar* getgrammar(char* str);

FirstFollow* getfirstfollow(Grammar *G);
void calculateFirst(FirstFollow *FirstFollow,Grammar *G,int i);
void addinlinkedlist4(linkedlist4 *ls,int index);
void calculateFollow(FirstFollow *F,Grammar *G);
void freeFirstFollow(FirstFollow *F);
void freeGrammar(Grammar *G);
void printnonterminals(Grammar *G);
void printRules(Grammar *G);
//parser functions
int istopdollar(parser_stack* stack, Grammar* G);
int isempty(parser_stack* stack);
stack_node* top(parser_stack* stack);
void push(parser_stack* stack,int id, int status);
void push_production(parser_stack* pstack,linkedlist* rule,Grammar* G);
void pop(parser_stack* stack);
void printfirst(Grammar* G, table* T,tokenInfo* token,parser_stack* pstack);

parser_ptnode* parent(parser_ptnode* curr);
parser_ptnode* right(parser_ptnode* curr);
parser_ptnode* child(parser_ptnode* curr);
parser_ptnode* next_node(parser_ptnode* curr);
void add_child(parser_ptnode* par, parser_ptnode* child);

table* createParseTable(FirstFollow *F,Grammar *G);
linkedlist* get_rule(table* t,int non_terminal,int input,int *error,int *syn);
parser_ptnode* add_production(parser_ptnode* curr, linkedlist* rule, Grammar* G, int lineNo);
int checkifnull(FILE* fileptr);
void fprint_40_spaces(int len);
int check_length(int len);

void print_parse_nodes(parser_ptnode* curr, Grammar* G);
void printParseTree(parser_pt* ptree, Grammar* G);
void getptreenodes(parser_pt* curr, Grammar* G,int* counter);
void getptreenodeshelper(parser_ptnode* curr, Grammar* G,int* counter);

int check_eps(Grammar* G,FirstFollow *F,int index);
parser_pt* parseInputSourceCode(char *testcaseFile, table* T, Grammar* G,FirstFollow *F);

#endif
