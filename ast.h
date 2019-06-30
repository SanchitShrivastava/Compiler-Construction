// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#ifndef AST 
#define AST

#include "astDef.h"
#include "parserDef.h"


ASTM* post_ast_order(parser_pt* ptree);
astNode* create_ast_node(Labeltype label,
						int leaf,
						astNode* parent,
						astNode* next,
						tokenInfo* lexicalTOKEN
						);
children* create_children_node(struct astNode* child_first,
								int no_siblings,
								struct astNode* child_last);
void add_parent_pointer(astNode* nd,children* chs);
void add_ast_child(children* chs,astNode* addr);
tokenInfo* create_tk_copy(tokenInfo* tk);
astNode* insert_at_head(astNode* node, astNode* list);
void ast_rule(parser_ptnode* node);
void post_order_util(parser_ptnode* node);
void ast_rule_inh(parser_ptnode* node);
void print_ast_tree(ASTM* tree);
void print_ast_util(astNode* node);
void getastnodes(ASTM* node,int* counter);
void getastnodeshelper(astNode* node,int* counter);
#endif
