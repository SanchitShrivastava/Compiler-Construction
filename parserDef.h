// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef PARSERDEF 
#define PARSERDEF

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lexerDef.h"
#include "astDef.h"

//Grammar Structure
struct node //node use in linkedlist 
{
	int val;
	int status;
	struct node* next;
};
typedef struct node node;

struct linkedlist // linkedlist used in rules_st
{
	int size;
	int ruleno;
	struct node* root;
};
typedef struct linkedlist linkedlist;

struct rules_st // structure for storing rules in form of array of linkedlist of numbers.
{
	int size;
	int capacity;
	struct linkedlist **arr;

};
typedef struct rules_st rules_st;

struct node3
{
	int ruleno;
	struct node3 *next;	
};

typedef struct node3 node3;

struct linkedlist3
{
	int size;
	struct node3* root;
};

typedef struct linkedlist3 linkedlist3;

struct single_non_terminal_st //structure for one non-terminal 
{
	linkedlist3 *rule_nos;
	char* str;
};

typedef struct single_non_terminal_st single_non_terminal_st;

struct non_terminals_st // structure for nonterminals
{
	int size;
	int capacity;
	struct single_non_terminal_st **arr;
};

typedef struct non_terminals_st non_terminals_st;

struct terminals_st // structure for terminals
{
	int size;
	int capacity;
	char **arr; 
};

typedef struct terminals_st terminals_st;


// Structute Definitions for STACK
struct stack_node 
{
	int id;
	int status;
	struct stack_node* next;
};

typedef struct stack_node stack_node;


struct parser_stack{
	int size;
	struct stack_node* head;
};
typedef struct parser_stack parser_stack;


struct node4
{
	int index;
	struct node4* next;
};

struct linkedlist4
{
	int size;
	struct node4* root;
};

struct ffl
{
	int size;
	struct linkedlist4 **arr;
};

struct FirstFollow
{
	struct ffl *first;
	struct ffl *follow;
};

struct Grammar
{
	non_terminals_st *nonterminals;
	terminals_st *terminals;
	int start;
	int eps;
	rules_st *rules;
	hashtable_st *searchtable;
};
typedef struct Grammar Grammar;

typedef struct FirstFollow FirstFollow;
typedef struct ffl ffl;
typedef struct linkedlist4 linkedlist4;
typedef struct node4 node4;

// Structure Definitions for PARSE TREE
struct parser_ptnode{
	
	char parent_symbol[200];
	char node_symbol[200];
	int valueofnum;
	struct parser_ptnode* parent;
	struct parser_ptnode* children_first;
	struct parser_ptnode* children_last;
	tokenInfo* token;
	int isleafnode;
	struct parser_ptnode* sibling;


	// For AST Creation
	int rule_no;
	astNode* addr;
	astNode* inh_addr;
};
typedef struct parser_ptnode parser_ptnode;

struct parser_pt{
	parser_ptnode* root;
};
typedef struct parser_pt parser_pt;


// Structure Definition for Parse Table
struct ruleused
{
	int status;
	linkedlist *l;
};
typedef struct ruleused ruleused;

struct table
{
	int row;
	int column;
	ruleused **arr;
};
typedef struct table table;

#endif
