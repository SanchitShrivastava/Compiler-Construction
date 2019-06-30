// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P



#include "ast.h"

char* LabelMap[] = {
	"PROGRAM_NODE",
	"function_node",
	"stmts_node",
	"typeDefinition_node",
	"fieldDefinition_node",
	"declaration_node",
	"assignentStmt_node",
	"singleOrRecId_node",
	"funCallStmt_node",
	"outputParameters_node",
	"inputParameters_node",
	"iterativeStmt_node",
	"conditionalStmt_node",
	"elsePart_node",
	"ioStmt1_node",
	"ioStmt2_node",
	"all_node1",
	"all_node2",
	"all_node3",
	"booleanExpression1_node",
	"booleanExpression2_node",
	"booleanExpression3_node",
	"datatype_node",
	"expPrime_node",
	"termPrime_node",
	"returnStmt_node"
};

/*
PROGRAM_NODE,
	"function_node",
	"typeDefinition_node",
	"fieldDefinition_node",
	"declaration_node",
	"assignentStmt_node",
	"singleOrRecId_node",
	"funCallStmt_node",
	"outputParameters_node",
	"inputParameters_node",
	"iterativeStmt_node",
	"conditionalStmt_node",
	"elsePart_node",
	"ioStmt1_node",
	"ioStmt2_node",
	"all_node1",
	"all_node2",
	"all_node3",
	"booleanExpression1_node",
	"booleanExpression2_node",
	"booleanExpression3_node",

	// Check this
	"expPrime_node",
	"termPrime_node",
	"returnStmt_node",
*/



Labeltype labels;

ASTM* post_ast_order(parser_pt* ptree){
	
	ASTM* tree = (ASTM*)malloc(sizeof(ASTM));
	post_order_util(ptree->root);
	tree->root = ptree->root->addr;
	return tree;
}


astNode* create_ast_node(Labeltype label,
						int leaf,
						astNode* parent,
						astNode* next,
						tokenInfo* lexicalTOKEN
						){

		astNode* nd = (astNode*)malloc( sizeof(astNode) );
		nd->label = label;
		nd->parent = parent;
		nd->concat = NULL;
		nd->next = next;
		nd->lexicalTOKEN = lexicalTOKEN;
		nd->child_list = NULL;
}


children* create_children_node(struct astNode* child_first,
								int no_siblings,
								struct astNode* child_last){

	children* chs = (children*)malloc( sizeof(children) );
	chs->child_first = child_first;
	chs->no_siblings=no_siblings;
	chs->child_last = child_last;
}

void add_parent_pointer(astNode* nd,children* chs)
{
	astNode* temp = chs->child_first;
	while(temp!=NULL)
	{
		temp->parent=nd;
		temp =temp->next;
	}
}

void add_ast_child(children* chs,astNode* addr)
{
	if(chs==NULL || addr==NULL)
	{
		if(chs == NULL){
			printf("help1\n");
		}
		else{
			printf("help2\n");
		}

		//printf("add_ast_child wrong!!\n");
		return;
	}
	if(chs->child_last==NULL)
	{
		chs->child_first = addr;
	}
	else
	{
		chs->child_last->next = addr;
	}
	chs->no_siblings++;
	chs->child_last = addr;
	
}

tokenInfo* create_tk_copy(tokenInfo* tk){
	if(tk == NULL){
		printf("Trying to copy NULL token\n");
		return NULL;
	}
	else{
		// create a copy of a token
		tokenInfo* copy = (tokenInfo*)malloc( sizeof(tokenInfo) );
		copy->lineNo = tk->lineNo;
		copy->lexeme_value = tk->lexeme_value;
		copy->token_id = tk->token_id;
		copy->status = tk->status;
		return copy;
	}
}

astNode* insert_at_head(astNode* node, astNode* list)
{

	if(node == NULL && list == NULL){
		printf("insert_at_head is wrong\n");
		return NULL;
	}

	if(node == NULL){
		return list;
	}

	node->concat=list;
	return node;
}

void ast_rule(parser_ptnode* node){

	int rule_no = node->rule_no;
	// printf("%d\n",rule_no);
	switch(rule_no){

		case 1 :{
				// create node
				labels = PROGRAM_NODE;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;
				children* chs = create_children_node(NULL,0,NULL);
				
				// printf("a\n");
				add_ast_child(chs,node->children_first->addr);
				add_ast_child(chs,node->children_first->sibling->addr);
				
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				break;
				}
				
		case 2 :{
				node->addr = node->children_first->sibling->addr;
				break;
				}
				
		case 3 :{
				node->addr = insert_at_head(node->children_first->addr,node->children_last->addr);
				break;
				}
		case 4 :{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
		case 5 :
				{
				labels = function_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;
				children* chs = create_children_node(NULL,0,NULL);
				
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				add_ast_child(chs,create_ast_node(-1,1,NULL,NULL,token_copy));
				
				add_ast_child(chs,node->children_first->sibling->addr);
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->addr);
				
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				break;
				}
				
		case 6	:
		case 7	:
				node->addr = node->children_first->sibling->sibling->sibling->sibling->addr;
				break;
				
		
		case 8	:
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
		
		
		case 9	:{
				labels = datatype_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				children* chs = create_children_node(NULL,0,NULL);
				
				add_ast_child(chs,node->children_first->addr);
				
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->token);
				// printf("%s\n",token_copy->lexeme_value);
				add_ast_child(chs,create_ast_node(-1,1,NULL,NULL,token_copy));
				
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				
				node->addr = insert_at_head(nd,node->children_first->sibling->sibling->addr);
				break;
				}
		
		case 10	:
		case 11	:
				node->addr = node->children_first->addr;
				break;
				
				
		case 12	:
		case 13	:
				{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				node->addr = create_ast_node(-1,1,NULL,NULL,token_copy);
				break;
				}
		case 14	:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->token);
				node->addr = create_ast_node(-1,1,NULL,NULL,token_copy);
				break;
				}
				
		case 15	:{
				node->addr = node->children_first->sibling->addr;
				break;
				}
				
		case 16	:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
				
		case 17	:{

				labels = stmts_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				children* chs = create_children_node(NULL,0,NULL);

				// tds
				add_ast_child(chs,node->children_first->addr);
				// decs
				add_ast_child(chs,node->children_first->sibling->addr);
				// ots
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				// rstmt
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->addr);

				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				node->addr = nd;
				break;
				}
				
		case 18	:{
				node->addr = insert_at_head(node->children_first->addr,node->children_first->sibling->addr);
				break;
				}
				
		case 19	:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				//printf("test\n");
				break;
				}
				
		case 20	:{
				labels = typeDefinition_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				children* chs = create_children_node(NULL,0,NULL);
				
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->token);
				add_ast_child(chs,create_ast_node(-1,1,NULL,NULL,token_copy));
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				node->addr = nd;
				break;
				}
				
		case 21	:{
				astNode* temp = insert_at_head(node->children_first->sibling->addr,node->children_first->sibling->sibling->addr);
				node->addr = insert_at_head(node->children_first->addr,temp);
				break;
				}
				
		case 22	:{
				labels = fieldDefinition_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				children* chs = create_children_node(NULL,0,NULL);
				
				add_ast_child(chs,node->children_first->sibling->addr);
				
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->sibling->sibling->token);
				add_ast_child(chs,create_ast_node(-1,1,NULL,NULL,token_copy));
				
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				node->addr = nd;
				break;
				}
				
		case 23	:{
				node->addr = insert_at_head(node->children_first->addr,node->children_first->sibling->addr);
				break;
				}
				
		case 24	:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
				
		case 25	:{
				node->addr = insert_at_head(node->children_first->addr,node->children_first->sibling->addr);
				break;
				}
				
		case 26	:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
				
		case 27	:{
				labels = declaration_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				children* chs = create_children_node(NULL,0,NULL);
				
				add_ast_child(chs,node->children_first->sibling->addr);
				// if(node->children_first->sibling->addr==NULL)
				// 	printf("1\n");
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->sibling->sibling->token);
				add_ast_child(chs,create_ast_node(-1,1,NULL,NULL,token_copy));
				
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->addr);
				// if(node->children_first->sibling->sibling->sibling->sibling->sibling->addr==NULL)
				// 	printf("2\n");
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				node->addr = nd;
				break;
				}
				
		case 28	:
		case 29	:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				node->addr = create_ast_node(-1,1,NULL,NULL,token_copy);
				break;
				}
				
		case 30	:{
				node->addr = insert_at_head(node->children_first->addr,node->children_first->sibling->addr);
				break;
				}
				
		case 31	:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
		case 32 :
		case 33 :
		case 34 :
		case 35 :
		case 36 :{
				// push up the pointer
				node->addr = node->children_first->addr;
				break;
				}
		case 37 :{
				// create node
				labels = assignentStmt_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;
				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// singleOrRecId
				add_ast_child(chs,node->children_first->addr);
				
				// for "=" create an ast node
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);

				// arithmetic expression
				add_ast_child(chs,node->children_first->sibling->sibling->addr);

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 38 :{
				// create node
				labels = singleOrRecId_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// for TK_ID create an ast node
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);
				// new_24
				add_ast_child(chs,node->children_last->addr);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 39:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
		case 40:{
				// create node
				astNode* nd = create_ast_node(-1,1,NULL,NULL,NULL);
				node->addr = nd;

				// for TK_FIELDID create a copy
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->token);
				nd->lexicalTOKEN = token_copy;
				break;
				}
		case 41:{
				// create node
				labels = funCallStmt_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// outputParameters
				add_ast_child(chs, node->children_first->addr);
				// TK_FUNID
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->sibling->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);
				// inputParameters
				add_ast_child(chs, node->children_first->sibling->sibling->sibling->sibling->sibling->addr);

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 42:{
				// create node
				labels = outputParameters_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// idlist
				add_ast_child(chs, node->children_first->sibling->addr);
				// equal lexeme
				tokenInfo* token_copy = create_tk_copy(node->children_first->sibling->sibling->sibling->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 43:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
		case 44:{
				// create node
				labels = inputParameters_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// idList
				add_ast_child(chs,node->children_first->sibling->addr);

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 45:{
				// create node
				labels = iterativeStmt_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// booleanExpression
				add_ast_child(chs,node->children_first->sibling->sibling->addr);

				// concat stmt with otherstmts
				insert_at_head(node->children_first->sibling->sibling->sibling->sibling->addr,
								node->children_first->sibling->sibling->sibling->sibling->sibling->addr);

				// add the child
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->addr);
				nd->start_while=node->children_first->token->lineNo;
				// endwhile number
				nd->end_while = node->children_first->sibling->sibling->sibling->sibling->sibling->sibling->token->lineNo;

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 46:
				{
				// create node
				labels = conditionalStmt_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// booleanExpression
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				//  concat stmt with otherstmts
				insert_at_head(node->children_first->sibling->sibling->sibling->sibling->sibling->addr,
								node->children_first->sibling->sibling->sibling->sibling->sibling->sibling->addr);

				// add the child
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->sibling->addr);
				
				// elsepart
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->sibling->sibling->sibling->addr);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 47:{
				// create node
				labels = elsePart_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// concat stmts with otherStmts
				insert_at_head(node->children_first->sibling->addr,
								node->children_first->sibling->sibling->addr);

				// add the child
				add_ast_child(chs,node->children_first->sibling->addr);

				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 48:{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}

		case 49:{
				// create node
				labels = ioStmt1_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// <singleOrRecId>
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 50:{
				// create node
				labels = ioStmt2_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// <all>
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 51:{
				// create node
				labels = all_node1;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// TK_ID
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);

				// new_24
				add_ast_child(chs,node->children_first->sibling->addr);
								
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		case 52:{
				// create node
				labels = all_node2;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// TK_NUM
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}
		case 53:{
				// create node
				labels = all_node3;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				// create children
				children* chs = create_children_node(NULL,0,NULL);

				// TK_RNUM
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				add_ast_child(chs,leaf);
				
				// join parent to children
				nd->child_list = chs;

				// add parent link
				add_parent_pointer(nd,chs);
				break;
				}

		/* Aman AST */
		case 54:{
				node->addr=node->children_last->addr;
				break;
				}
		case 55:{
				node->addr=node->children_last->addr;
				break;
				}
		case 56 :{
				node->addr=node->parent->inh_addr;
				break;
				}
		case 57:{
				node->addr=node->children_last->addr;
				break;
				}
		case 58:{
				node->addr=node->children_last->addr;
				break;
				}
		case 59 :{
				node->addr=node->parent->inh_addr;
				break;
				}
		case 60:{
				node->addr=node->children_first->sibling->addr;
				break;
				}
		case 61:{
				node->addr=node->children_first->addr;
				break;
				}
		case 62:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* nd = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr=nd;
				break;
				}
		case 63:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* nd = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr=nd;
				break;
				}
		case 64:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* nd = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr=nd;
				break;
				}
		case 65:{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* nd = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr=nd;
				break;
				}

		/*Sanchit AST*/
		case 66 :{
				labels = booleanExpression1_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				children* chs = create_children_node(NULL,0,NULL);


				add_ast_child(chs,node->children_first->sibling->addr);
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->addr);
				add_ast_child(chs,node->children_first->sibling->sibling->sibling->sibling->sibling->addr);
				nd->child_list = chs;

				add_parent_pointer(nd,chs);
				break;
				}

		case 67 :{
				labels = booleanExpression2_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				children* chs = create_children_node(NULL,0,NULL);


				add_ast_child(chs,node->children_first->addr);
				add_ast_child(chs,node->children_first->sibling->addr);
				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				nd->child_list = chs;

				add_parent_pointer(nd,chs);
				break;
				}

		case 68 :{
				labels = booleanExpression3_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				children* chs = create_children_node(NULL,0,NULL);

				add_ast_child(chs,node->children_first->sibling->sibling->addr);
				nd->child_list = chs;

				add_parent_pointer(nd,chs);
				break;
				}
		case 69 :
		case 70 :
		case 71 :
		case 72 :
		case 73 :
		case 74 :
		case 75 :
		case 76 :
		case 77 :
		case 78 :
		case 79 :{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* nd = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr = nd;
				break;
				}
		case 80 :{
				labels = returnStmt_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,NULL);
				node->addr = nd;

				children* chs = create_children_node(NULL,0,NULL);
				nd->end_while=node->children_first->token->lineNo;
				add_ast_child(chs,node->children_first->sibling->addr);
				nd->child_list = chs;
				nd->end_while=node->children_first->token->lineNo;
				add_parent_pointer(nd,chs);
				break;
				}
		case 81 :{
				node->addr = node->children_first->sibling->addr;
				break;
				}
		case 82 :{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
		case 83 :{
				tokenInfo* token_copy = create_tk_copy(node->children_first->token);
				astNode* leaf = create_ast_node(-1,1,NULL,NULL,token_copy);
				node->addr = insert_at_head(leaf,node->children_first->sibling->addr);
				break;
				}
		case 84 :{
				node->addr = node->children_first->sibling->addr;
				break;
				}
		case 85 :{
				node->addr = create_ast_node(-2,1,NULL,NULL,NULL);
				break;
				}
	}
}

void post_order_util(parser_ptnode* node){

	// base
	if(node == NULL){
		return;
	}

	// traverse children
	parser_ptnode* ptr = node->children_first;
	if(node->rule_no==54 || node->rule_no==55 || node->rule_no==57 || node->rule_no==58)
	{
		while(ptr!=NULL && ptr ->sibling != NULL){
			post_order_util(ptr);
			ptr = ptr->sibling;
		}

		// if the node was a terminal - 
		if(node->isleafnode == 1){
			return ;
		}
		else{
			// create according to ast rule
			ast_rule_inh(node);
			post_order_util(ptr);
			ast_rule(node);
		}
	}
	else
	{
		while(ptr != NULL){
			post_order_util(ptr);
			ptr = ptr->sibling;
		}

		// if the node was a terminal - 
		if(node->isleafnode == 1){
			return ;
		}
		else{
			// create according to ast rule
			ast_rule(node);
		}
	}
}

void ast_rule_inh(parser_ptnode* node){

	int rule_no = node->rule_no;

	switch(rule_no){
		case 54 :
		{

				node->inh_addr=node->children_first->addr;
				break;
			}
		case 55	 :
		{
			labels = expPrime_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,node->token);
				node->inh_addr=nd;
				children* chs = create_children_node(NULL,0,NULL);
				add_ast_child(chs,node->parent->inh_addr);
				add_ast_child(chs,node->children_first->addr);
				add_ast_child(chs,node->children_first->sibling->addr);
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				break;
			}
		case 57 :
		{
				node->inh_addr=node->children_first->addr;
				break;
			}
		case 58	 :
		{
				labels = termPrime_node;
				astNode* nd = create_ast_node(labels,0,NULL,NULL,node->token);
				node->inh_addr=nd;
				children* chs = create_children_node(NULL,0,NULL);
				add_ast_child(chs,node->parent->inh_addr);
				add_ast_child(chs,node->children_first->addr);
				add_ast_child(chs,node->children_first->sibling->addr);
				nd->child_list = chs;
				add_parent_pointer(nd,chs);
				break;
			}
	}



}


void getastnodes(ASTM* node,int* counter)
{
	getastnodeshelper(node->root,counter);
}

void getastnodeshelper(astNode* node,int* counter){

	if(node == NULL){
		return;
	}
	else{
		
		if(node->child_list == NULL){
			
			if(node->label!=-1){
				(*counter)++;
				//printf("node label %s\n",LabelMap[node->label]);
			}
			else
			{
				(*counter)++;
				//printf("node label %s \n",node->lexicalTOKEN->lexeme_value);
			}
		}
		else
		{
			astNode* temp = node->child_list->child_first;

			if(temp != NULL){
				getastnodeshelper(temp,counter);
			}

			if(node->label!=-1){
				(*counter)++;
				//printf("node label %s\n",LabelMap[node->label]);
			}
			else
			{
				(*counter)++;
				//printf("node label %s \n",node->lexicalTOKEN->lexeme_value);
			}

			if(temp != NULL){
				temp = temp->next;
				while(temp!=NULL)
				{
					getastnodeshelper(temp,counter);
					temp = temp->next;
				}
			}
		}
	}
	if(node->concat!=NULL)
	{
		//printf("check1\n");
		getastnodeshelper(node->concat,counter);
	}
}






void print_ast_tree(ASTM* tree){
	print_ast_util(tree->root);
}
void print_ast_util(astNode* node){
	int label = 0;
	int label2 = 0;
	if(node == NULL){
		return;
	}
	else{
		//printf("lsd");
		if(node->child_list == NULL){
			label = node->label;
			if(label>=0){
				char* child = "NULL";
				char* sibling = "NULL";
				if(node->next!=NULL)
				{
					label2 = node->next->label;
					if(label2>=0)
					{
						sibling = LabelMap[node->next->label];
					}
				}
				if(node->parent!=NULL)
				{
					label2 = node->parent->label;
					if(label2>=0)
					{
						printf("\n%s 	---- 	%s 	%s 	%s\n",LabelMap[node->label],LabelMap[node->parent->label],child,sibling);
					}
					else
					{
						printf("\n%s 	---- 	%s 	---- %s\n",LabelMap[node->label],child,sibling);
					}
				}
				else
				{
					printf("\n%s 	---- 	%s 	---- %s\n",LabelMap[node->label],child,sibling);
				}
				
			}
			else if(label==-1)
			{
				char* sibling = "NULL";
				if(node->next!=NULL )
				{
					label2 = node->next->label;
					if(label2>=0)
					{
						sibling = LabelMap[node->next->label];
					}
				}
				if(node->parent!=NULL)
				{
					label2 = node->parent->label;
					if(label2>=0)
					{
					printf("\n---- 	%s 	%s	---- 	%s\n",node->lexicalTOKEN->lexeme_value,LabelMap[node->parent->label],sibling);
					}
					else
					{
						printf("\n---- 	%s 	----	---- 	%s\n",node->lexicalTOKEN->lexeme_value,sibling);

					}
				}
				else
				{
					printf("\n---- 	%s 	----	---- 	%s\n",node->lexicalTOKEN->lexeme_value,sibling);
				}
				

			}
		}
		else
		{
			astNode* temp = node->child_list->child_first;

			if(temp != NULL){
				print_ast_util(temp);
			}
			label = node->label;
			if(label>=0){
				char* child = "NULL";
				char* sibling = "NULL";
				if(node->child_list->child_first!=NULL)
				{
					label2 = node->child_list->child_first->label;
					if(label2>=0)
					{
						child = LabelMap[node->child_list->child_first->label];
					}
				}
				if(node->next!=NULL)
				{
					label2 = node->next->label;
					if(label2>=0)
					{
						sibling = LabelMap[node->next->label];
					}
					
				}
				if(node->parent!=NULL)
				{
					label2 = node->parent->label;
					if(label2>=0)
					{
						printf("\n%s 	---- 	%s 	%s 	%s\n",LabelMap[node->label],LabelMap[node->parent->label],child,sibling);
					}
					else
					{
						printf("\n%s 	---- 	%s 	---- %s\n",LabelMap[node->label],child,sibling);
					}
				}
				else
				{
					printf("\n%s 	---- 	%s 	---- %s\n",LabelMap[node->label],child,sibling);
				}
				
			}
			else if(label ==-1)
			{
				char* sibling = "NULL";
				if(node->next!=NULL )
				{
					label2 = node->next->label;
					if(label2>=0)
					{
						sibling = LabelMap[node->next->label];
					}
				}
				if(node->parent!=NULL)
				{
					label2 = node->parent->label;
					if(label2>=0)
					{
					printf("\n---- 	%s 	%s	---- 	%s\n",node->lexicalTOKEN->lexeme_value,LabelMap[node->parent->label],sibling);
					}
					else
					{
						printf("\n---- 	%s 	----	---- 	%s\n",node->lexicalTOKEN->lexeme_value,sibling);
					}
				}
				else
				{
					printf("\n---- 	%s 	----	---- 	%s\n",node->lexicalTOKEN->lexeme_value,sibling);
				}
				

			}

			if(temp != NULL){
				temp = temp->next;
				while(temp!=NULL)
				{
					print_ast_util(temp);
					temp = temp->next;
				}
			}
		}
	}
	if(node->concat!=NULL)
	{
		print_ast_util(node->concat);
	}
}
