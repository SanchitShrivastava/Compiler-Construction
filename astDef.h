// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P


#ifndef ASTDEF
#define ASTDEF

#include <stdio.h>
#include <stdlib.h>
#include "lexerDef.h"

//List of all possible Labels
enum Labeltype{
	PROGRAM_NODE,
	function_node,
	stmts_node,
	typeDefinition_node,
	fieldDefinition_node,
	declaration_node,
	assignentStmt_node,
	singleOrRecId_node,
	funCallStmt_node,
	outputParameters_node,
	inputParameters_node,
	iterativeStmt_node,
	conditionalStmt_node,
	elsePart_node,
	ioStmt1_node,
	ioStmt2_node,
	all_node1,
	all_node2,
	all_node3,
	booleanExpression1_node,
	booleanExpression2_node,
	booleanExpression3_node,
	datatype_node,
	expPrime_node,
	termPrime_node,
	returnStmt_node,
};
typedef enum Labeltype Labeltype;

struct children{
	//Linked list of Children
	struct astNode* child_first;
	int no_siblings;
	struct astNode* child_last;
}; 
typedef struct children children;

struct astNode{

	//For Non-Leaf Nodes
	Labeltype label;
	
	//Whether leaf node or not
	int leaf;
	
	//Pointer to parent node
	struct astNode* parent;

	// Children pointer
	children* child_list; 

	// Sibling
	struct astNode* next; 

	//If it's a leaf node
	tokenInfo* lexicalTOKEN; 
	
	//For compressing list -- i.e concatenation purpose
	struct astNode* concat;
	int start_while;
	int end_while;

	//For symbol Table
	// struct symTableTreeNode* current_scope;
	
	//For Type checking purposes
	// Tokentype nodeType;
	
	//For funid node
	struct typeList* return_parameters;
	
	//For printing errors
	int line_no;
	
	//For checking Recursion
	struct astNode* parent_function;
	
	//For string Length
	int str_length;
	
	//For IR generation
	
	char* name;
	//struct tuple* tuple;
	char* str;
	int* val;
};
typedef struct astNode astNode;


//AST
struct ast{
	astNode* root;		
};
typedef struct ast ASTM;


struct typeList{
	struct typeListNode* head;
	struct typeListNode* last;
	int no_siblings;	
};
typedef struct typeList TypeList;

struct typeListNode{
	struct typeListNode* next;
	//Tokentype type;
};
typedef struct typeListNode TypeNode;

#endif