#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"
#include "codegen.h"

int maxNumFields=0;
int loopnum=0;
int ifnum=0;
int relnum=0;


char* StringMap[] = {
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


void printNewline(FILE*fp)
{
	fprintf(fp,"_PrintNewLine:\n\
section .data\n\
.nl\t\t db\t\t10\n\
section .text\n\
\t\tpush\t\tecx\n\
\t\tpush\t\tedx\n\
\t\tmov\t\tecx, .nl\n\
\t\tmov\t\tedx, 1\n\
\t\t;print the string\n\
\t\tpush\t\teax\n\
\t\tpush\t\tebx\n\
\t\tmov\t\teax,4\n\
\t\tmov\t\tebx,1\n\
\t\tint\t\t0x80\n\
\t\tpop\t\tebx\n\
\t\tpop\t\teax\n\
\t\tpop\t\tedx\n\
\t\tpop\t\tecx\n\
\t\tret\n");
}


void printDecimalNumber(FILE* fp)
{
	fprintf(fp,"_DecimalPrint:\n\
section\t\t.bss\n\
.decstr\t\tresb\t\t10\n\
.ct1\t\tresd\t\t1\n\
section .text\n\
\t\tpushad\n\
\t\tmov\t\t dword[.ct1],0\n\
\t\tmov\t\t edi,.decstr\n\
\t\tadd\t\t edi,9\n\
\t\txor\t\t edx,edx\t\n\
.whileNotZero:\n\
\t\tmov\t\t ebx,10\t\n\
\t\tdiv\t\t ebx\t\n\
\t\tadd\t\t edx,'0'\n\
\t\tmov\t\t byte[edi],dl\n\
\t\tdec\t\t edi\n\
\t\tinc\t\t dword[.ct1] \n\
\t\txor\t\t edx,edx\n\
\t\tcmp\t\t eax,0\n\
\t\tjne\t\t .whileNotZero\n\
\t\tinc\t\t edi\n\
\t\tmov\t\t ecx, edi\t \n\
\t\tmov\t\t edx, [.ct1]\n\
\t\tmov\t\t eax, 4\n\
\t\tmov\t\t ebx, 1\n\
\t\tint\t\t 0x80\n\
\t\tpopad\n\
\t\tret\n");
}

void printNegPos(FILE*fp)
{
fprintf(fp,"_NegPosPrint:\n\
section .data\n\
\t\tminus db '-'\n\
section .text\n\
\t\tpushad\n\
\t\tcmp eax, 0000h\n\
\t\tjge X1\n\
\t\tneg eax\n\
\t\tpush eax\n\
\t\tmov eax,4\n\
\t\tmov ebx, 1\n\
\t\tmov ecx, minus\n\
\t\tmov edx, 1\n\
\t\tint 80h\n\
\t\tpop eax\n\
\t\tX1:\n\
\t\tcall _DecimalPrint\n\
\t\tpopad\n\
\t\tret\n");
}

void takeUserInput(FILE* fp)
{
	fprintf(fp,"_UserInput:\n\
section .bss\n\
buffer\tresb\t120\n\
intg\tresd\t1\n\
isneg\tresb\t1\t\n\
section .text\n\
\t\tpushad\t\t\n\
\t\tmov\tesi, buffer\n\
\t\tmov\tedi, 0\t\n\
.loop1:\t\n\
\t\tmov\teax, 03\t\n\
\t\tmov\tebx, 0\t\n\
\t\tmov\tecx, esi\n\
\t\tmov\tedx, 1\t\n\
\t\tint\t0x80\t\n\
\t\tcmp\tbyte[esi], 0\n\
\t\tje\t .parse\n\
\t\tcmp\tbyte[esi], 10\n\
\t\tje\t .parse\n\
\t\tinc\tesi\n\
\t\tinc\tedi\t\n\
\t\tjmp\t.loop1\n\
.parse:\n\
\t\tmov\tesi, buffer\t\n\
\t\tmov\tecx, edi\t\n\
\t\tmov\tdword[intg], 0\n\
\t\tmov\tbyte[isneg], 0\n\
.negativ:\t\n \
\t\tcmp\tbyte[esi], '-'\n\
\t\tjne\t.loop\n\
\t\tinc\tesi\n\
\t\tinc\tbyte[isneg]\n\
.loop:\t  mov\tebx, 0\n\
\t\tmov\tbl, byte[esi]\t\n \
\t\tcmp\tbl, 10\t\n  \
\t\tje\t .done\t\n\
\t\tcmp\tbl, '0'\n\
\t\tjb\t .done\n\
\t\tcmp\tbl, '9'\n\
\t\tja\t .done\t\n\
\t\tmov\tedx, 10\n\
\t\tmov\teax, dword[intg]\n\
\t\tmul\tedx\t\n \
\t\tsub\tbl, '0'\n\
\t\tadd\teax, ebx\n\
\t\tmov\tdword[intg], eax\n\
\t\tinc\tesi\n\
\t\tloop    .loop\n\
.done:\n  \
\t\tcmp\tbyte[isneg], 0\n\
\t\tje\t .return\n\
\t\tneg\teax\n\
\t\tmov\tdword [intg], eax\n\
.return:\n\
\t\tpopad\n\
\t\tmov\teax, [intg]\n\
\t\tret\n");
}

void DeclareglobalVariablesInBss(FILE* fp)
{
	listnasm* globalvar = globalvariable();
	listnasm* head=globalvar;
	int count;

	while(head!=NULL)
	{

		if( strcmp(head->type,"int") == 0 || strcmp(head->type,"real") == 0 )
		{
			fprintf(fp,"%s resd %d\n",head->name,1);			
		}
		else
		{

			count=0;
			listnasm* fields = recordvarible(head->type);
			listnasm* temp=fields;
			while(temp!=NULL)
			{
				fprintf(fp,"%s.%s resd %d\n",head->name,temp->name,1);
				temp=temp->next;
				count++;
			}
			if(count>maxNumFields)
			{
				maxNumFields=count;
			}
		}
		head=head->next;
	}
}


void DeclaremainVariablesInBss(FILE* fp)
{
	int count=0;
	listnasm* mainvar = mainvariable();
	listnasm* head=mainvar;

	while(head!=NULL)
	{

		if(head->type == NULL){
			printf("Hey TYPE is NULL !!!\n");
		}

		if( strcmp(head->type,"int") == 0 || strcmp(head->type,"real") == 0 )
		{
			//printf("we_main\n");
			fprintf(fp,"%s resd %d\n",head->name,1);			
		}
		else
		{
			count=0;
			listnasm* fields = recordvarible(head->type);
			listnasm* temp=fields;
			while(temp!=NULL)
			{

				fprintf(fp,"%s.%s resd %d\n",head->name,temp->name,1);
				temp=temp->next;
				count++;

			}
		}
		if(count>maxNumFields)
		{
			maxNumFields=count;
		}
		head=head->next;
	}
}

int findarithmetic(FILE *fp,astNode* stmt)
{

	int num_fields;

	int gora = stmt->label;
	int tinker = stmt->label;
	if( gora > 0 ){
	}
	else{
	}

	if(stmt->label == singleOrRecId_node){

		// variables and records
		if( stmt->child_list->child_first->next == NULL ){

			char* name = stmt->child_list->child_first->lexicalTOKEN->lexeme_value;
			char* type = (char*)findelement(name,variable);

			if(type == NULL){
				type = (char*)findelement(name,globalvar);
			}

			// variables
			if(strcmp(type,"int") == 0 || strcmp(type,"real") == 0 ){
				fprintf(fp,"push dword[%s]\n",name);
				return 1;
			}
			// records
			else{

				listnasm* head = recordvarible(type);
				listnasm* temp = head;

				int counter = 0;
				while(temp != NULL){
					fprintf(fp,"push dword[%s.%s]\n",name,temp->name);
					temp = temp->next;
					counter += 1;
				}
				return counter;
			}
		}
		// single record.field
		else{
			char* name = stmt->child_list->child_first->lexicalTOKEN->lexeme_value;
			char* type = (char*)findelement(name,variable);

			if(type == NULL){
				type = (char*)findelement(name,globalvar);
			}

			fprintf(fp,"push dword[%s.%s]\n",name, stmt->child_list->child_first->next->lexicalTOKEN->lexeme_value);   //if record types are also allowed change here
			return 1;
		}
	}
	// TK_ID
	// either from <var> or from <all>
	else if( (tinker == -1 && stmt->lexicalTOKEN->token_id == 11) ||
			 (stmt->label == all_node1 && stmt->child_list->child_first->lexicalTOKEN->token_id == 11)
				){

		//printf("ffg\n");

		char* name;
		char* type;

		// from all_node1
		if(stmt->label == all_node1 && stmt->child_list->child_first->lexicalTOKEN->token_id == 11){

			name = stmt->child_list->child_first->lexicalTOKEN->lexeme_value;
			type = (char*)findelement(name,variable);

			if(type == NULL){
				type = (char*)findelement(name,globalvar);
			}

		}
		// if from <var>
		else{
			name = stmt->lexicalTOKEN->lexeme_value;
			type = (char*)findelement(name,variable);

			if(type == NULL){
				type = (char*)findelement(name,globalvar);
			}
		}

		// int or real
		if( strcmp(type,"int") == 0 || strcmp(type,"real") == 0 ){
			//printf("dfgh\n");
			fprintf(fp,"push dword[%s]\n",name);
			return 1;
		}
		// record (not required)
		else{
			listnasm* head = recordvarible(type);
			listnasm* temp = head;

			int counter = 0;
			while(temp != NULL){
				fprintf(fp,"push dword[%s.%s]\n",name,temp->name);
				temp = temp->next;
				counter += 1;
			}
			return counter;
		}

	}
	// TK_NUM
	// either from <all> or from <var>
	else if( (stmt->label == all_node2 && stmt->child_list->child_first->lexicalTOKEN->token_id == 37)  ||  
			 (tinker == -1 && stmt->lexicalTOKEN->token_id == 37) ) {
		
		//printf("lalala\n");

		// from <var>
		if(tinker == -1 && stmt->lexicalTOKEN->token_id == 37){
			fprintf(fp,"mov eax,%s\npush eax\n",stmt->lexicalTOKEN->lexeme_value);
		}
		// from <all>
		else{
			fprintf(fp,"mov eax,%s\npush eax\n",stmt->child_list->child_first->lexicalTOKEN->lexeme_value);
		}

		return 1;
	}
	// TK_MUL or TK_DIV
	else if(stmt->label == termPrime_node){

		
		astNode* operation = stmt->child_list->child_first->next;
		int token_id = operation->lexicalTOKEN->token_id;

		// TK_MUL
		if( token_id == 39){

			astNode* field1 = stmt->child_list->child_first;
			astNode* field2 = operation->next;

			int num1 = findarithmetic(fp,field1);
			int num2 = findarithmetic(fp,field2);

			if(num1 == 1 && num2 == 1){
				fprintf(fp,"pop ebx\npop eax\nimul ebx\npush eax\n");
				return 1;
			}
			else if( num1 > 1 && num2 == 1 ){

				fprintf(fp,"pop ebx\n");

				int i;
				for(i = 0; i<num1; i++){
					fprintf(fp,"pop eax\nimul eax,ebx\nmov dword[.bufferop1 + %d],eax\n",4*i);
				}

				for(i = num1-1; i >= 0; i--){
					fprintf(fp,"push dword[.bufferop1 + %d]\n",4*i);
				}

				return num1;

			}
			else if(num2 > 1 && num1 == 1){

				int i;
				for(i = 0; i < num2; i++){
				 fprintf(fp,"pop dword[.bufferop1 + %d]\n",4*i);
				}

				fprintf(fp,"pop ebx\n");
				
				for(i = num2-1;i >= 0;i--){
					fprintf(fp,"mov eax,dword[.bufferop1 + %d]\nimul eax,ebx\npush eax",4*i);
				}
				
				return num2;
			}

		}
		// TK_DIV
		else if(token_id == 40){

			astNode* field1 = stmt->child_list->child_first;
			astNode* field2 = operation->next;

			int num1 = findarithmetic(fp,field1);
			int num2 = findarithmetic(fp,field2);

			if(num1 == 1 && num2 == 1){
				fprintf(fp,"pop ebx\npop eax\npush edx\nmov edx,0\nidiv ebx\npop edx\npush eax\n");
				return 1;
			}
			else if(num1 > 1 && num2 == 1){

				fprintf(fp,"pop ebx\n");

				int i;
				for(i = 0;i < num1;i++){
					fprintf(fp,"pop eax\npush edx\nmov edx,0\nidiv ebx\npop edx\nmov dword[.bufferop1 + %d],eax\n",4*i);
				}
			
				for(i = num1-1;i >= 0;i--){
					fprintf(fp,"push dword[.bufferop1 + %d]\n",4*i);
				}
				
				return num1;
			}
			else{

				if(num2 > 1 && num1 == 1){
					printf("Cannot divide number by record, returning -1\n");					
				}
				else{
					printf("Cannot divide record by record, returning -1\n");
				}
				return -1;
			}

		}

	}
	// TK_PLUS OR TK_MINUS
	else if(stmt->label == expPrime_node){

		astNode* operation = stmt->child_list->child_first->next;
		int token_id = operation->lexicalTOKEN->token_id;

		// TK_PLUS
		if( token_id == 41){

			astNode* field1 = stmt->child_list->child_first;
			astNode* field2 = operation->next;

			int num1 = findarithmetic(fp,field1);
			int num2 = findarithmetic(fp,field2);

			if(num1 == 1 && num2 == 1){
				fprintf(fp,"pop ebx\npop eax\nadd eax,ebx\npush eax\n");
				return 	1;
			}
			else if( num1 > 1 && num2 > 1){

				int i;
				for(i = num1-1;i >= 0; i--){
					fprintf(fp, "pop dword[.bufferop1+%d]\n",4*i );
				}
				
				for(i = num2-1;i >= 0; i--){
					fprintf(fp, "pop eax\nadd eax, dword[.bufferop1+%d]\nmov dword[.bufferop1+%d], eax\n",4*i ,4*i);
				}
				
				for(i = 0;i < num1; i++){
					fprintf(fp,"push dword[.bufferop1+%d]\n", 4*i);
				}

				return num1;
			}
			else{
				printf("Cannot add record and number, returning -1\n");
				return -1;
			}

		}
		// TK_MINUS
		else if(token_id == 42){

			// binary code
			astNode* field1 = stmt->child_list->child_first;
			astNode* field2 = operation->next;

			int num1 = findarithmetic(fp,field1);
			int num2 = findarithmetic(fp,field2);

			if(num1 == 1 && num2 == 1){
				fprintf(fp,"pop ebx\npop eax\nsub eax,ebx\npush eax\n");
				return 	1;
			}
			else if( num1 > 1 && num2 > 1){

				int i;
				for(i = num1-1;i >= 0; i--){
					fprintf(fp, "pop dword[.bufferop1+%d]\n",4*i );
				}
				
				for(i = num2-1;i >= 0; i--){
					fprintf(fp, "pop eax\nsub eax, dword[.bufferop1+%d]\nmov dword[.bufferop1+%d], eax\n",4*i,4*i );
				}

				for(i = 0;i < num1; i++){
					fprintf(fp,"push dword[.bufferop1+%d]\n", 4*i);
				}

				return num1;
			}
			else{
				printf("Cannot subtract record and number, returning -1\n");
				return -1;
			}
		}

	}
	

}

void booleanfinder(FILE *fp,astNode* stmt)
{
	if(stmt->label == booleanExpression1_node)
	{
		astNode* logicalop = stmt->child_list->child_first->next;
		char* value = logicalop->lexicalTOKEN->lexeme_value;
		if(strcmp(value,"&&&")==0)
		{
			booleanfinder(fp,stmt->child_list->child_first);
			booleanfinder(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\nand eax, ebx\npush eax\n");
		}
		else if(strcmp(value,"@@@")==0)
		{
			booleanfinder(fp,stmt->child_list->child_first);
			booleanfinder(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\nor eax, ebx\npush eax\n");
		}
	}
	else if(stmt->label == booleanExpression2_node)
	{

		astNode* relationalop = stmt->child_list->child_first->next;
		char* value = relationalop->lexicalTOKEN->lexeme_value;
		if(strcmp(value,"<")==0)
		{
			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njl .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
		else if(strcmp(value,">")==0)
		{
			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njg .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
		else if(strcmp(value,"<=")==0)
		{

			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);

			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njle .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
		else if(strcmp(value,">=")==0)
		{
			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njge .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
		else if(strcmp(value,"!=")==0)
		{
			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\njne .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
		else if(strcmp(value,"==")==0)
		{
			findarithmetic(fp,stmt->child_list->child_first);
			findarithmetic(fp,stmt->child_list->child_first->next->next);
			fprintf(fp,"pop ebx\npop eax\npush 0ffffh\ncmp eax,ebx\nje .rel%d\npop eax\npush 0000h\n.rel%d:\n",relnum,relnum);
			relnum++;
		}
	}
	else if(stmt->label == booleanExpression3_node)
	{
		booleanfinder(fp,stmt->child_list->child_first);
		fprintf(fp,"pop eax\nnot eax\npush eax\n");
	}
}




void generatecode(FILE* fp,astNode* stmt)
{
	Labeltype id = stmt->label;
	if(id == iterativeStmt_node)
	{
		fprintf(fp,".loop%d:\n",loopnum);
		astNode* boolexp=stmt->child_list->child_first;
		booleanfinder(fp,boolexp);
		fprintf(fp,"pop eax\ncmp eax,0000h\nje .endloop%d\n", loopnum);
		int x = loopnum;
		loopnum+=1;
		astNode* stmt=boolexp->next;
		while(stmt!=NULL && stmt->label!=-2)
		{
			generatecode(fp,stmt);
			stmt=stmt->concat;
		}
		fprintf(fp,"jmp .loop%d\n",x);
		fprintf(fp,".endloop%d:\n",x);
	}
	else if(id == conditionalStmt_node)
	{
		astNode* boolexp=stmt->child_list->child_first;
		booleanfinder(fp,boolexp);
		fprintf(fp,"pop eax\ncmp eax,0000h\nje .elsepart%d\n", ifnum);
		int x = ifnum;
		ifnum+=1;
		astNode* stmt3=boolexp->next;
		while(stmt3!=NULL && stmt3->label!=-2)
		{
			generatecode(fp,stmt3);
			stmt3=stmt3->concat;
		}

		fprintf(fp,"jmp .endif%d\n", x);
		fprintf(fp,".elsepart%d:\n", x);
		astNode* stmt2=boolexp->next->next->child_list->child_first;
		while(stmt2!=NULL && stmt2->label!=-2)
		{
			generatecode(fp,stmt2);
			stmt2=stmt2->concat;
		}

		fprintf(fp,".endif%d:\n", x);
	}
	else if(id == ioStmt1_node)	//read
	{
		astNode* sord=stmt->child_list->child_first;
		astNode* new24= sord->child_list->child_first->next;

		int er = new24->label;
		if(er ==-2)
 		{
 			char* value=sord->child_list->child_first->lexicalTOKEN->lexeme_value;
 			
 			char* ls=(char*)findelement(value,variable);
 			if(ls==NULL)
 			{
 				ls = (char*)findelement(value,globalvar);
 			}
 			
 			if(strcmp(ls,"int")==0 || strcmp(ls,"real")==0)
 			{
 				fprintf(fp,"call _UserInput\nmov dword[%s], eax\n",value);
 			}
 			else
 			{
 				listnasm* lsn=recordvarible(ls);
 				listnasm* head=lsn;
 				while(head!=NULL)
 				{
 					fprintf(fp,"call _UserInput\nmov dword[%s.%s], eax\n",value,head->name );
 					head=head->next;
 				}
 			}
 			
 		}
	 	else
	 	{
	 		//printf("sasdsadasdsahaboy\n");
	 		fprintf(fp,"call _UserInput\nmov dword[%s.%s], eax\n",sord->child_list->child_first->lexicalTOKEN->lexeme_value,new24->lexicalTOKEN->lexeme_value );
	 	}
	}

	else if(id == ioStmt2_node) //write
	{
		astNode* sord=stmt->child_list->child_first;
		astNode* new24= sord->child_list->child_first->next;

		//printf("qwqw\n");

		int erer = new24->label;
		if(erer==-2)
 		{
 			//printf("asasas\n");

 			//printf("shaboy\n");
 			char* value=sord->child_list->child_first->lexicalTOKEN->lexeme_value;
 			//printf("%s\n",value );
 			char* ls = (char*)findelement(value,variable);
 			if(ls==NULL)
 			{
 				ls=(char*)findelement(value,globalvar);
 				//ls=(char*)findelement(value,variable);
 			}

 			// printf("%s %s\n",value,ls);

 			//printf("%s\n",ls );
 			if(strcmp(ls,"int")==0 || strcmp(ls,"real")==0)
 			{
 				fprintf(fp,"mov eax, dword[%s]\ncall _NegPosPrint\ncall _PrintNewLine\n",value);
 			}
 			else
 			{
 				listnasm* lsn=recordvarible(ls);
 				listnasm* head=lsn;
 				while(head!=NULL)
 				{
 					fprintf(fp,"mov eax,dword[%s.%s]\ncall _NegPosPrint\ncall _PrintNewLine\n",value,head->name );
 					head=head->next;
 				}
 			}
 		}
	 	else
	 	{
	 		fprintf(fp,"mov eax, dword[%s.%s]\ncall _NegPosPrint\ncall _PrintNewLine\n",sord->child_list->child_first->lexicalTOKEN->lexeme_value,new24->lexicalTOKEN->lexeme_value );
	 	}

	}
	else if(id == assignentStmt_node)
	{
		//astNode* ae = stmt->child_list->child_first->next->next;

		astNode* sord = stmt->child_list->child_first;
		// printf("label : %s\n", StringMap[sord->label] );
		astNode* equal = sord->next;
		// if(equal->label == -1){
		// 	printf("aman\n");
		// }
		//printf("label : %s\n", StringMap[equal->label] );
		astNode* ae = equal->next;
		// if(ae == NULL){
		// 	printf("asas\n");
		// }
		// else{
		// 	printf("qwqw %d\n",ae->label);
		// }

		// printf("label : %s\n", StringMap[ae->label] );
	
		int noField = findarithmetic(fp,ae);
		//printf("%d\n",noField );
		
		if(noField==1)
		{
			astNode* sord = stmt->child_list->child_first;
			astNode* new24= sord->child_list->child_first->next;

			char* value = sord->child_list->child_first->lexicalTOKEN->lexeme_value;

			int qw = new24->label;
			if( qw == -2){
				fprintf(fp,"pop eax\nmov dword[%s],eax\n",value); //if record types are also allowed change here
			}
			else{
				fprintf(fp,"pop eax\nmov dword[%s.%s],eax\n",value, new24->lexicalTOKEN->lexeme_value);
			}
		}
		else
		{
			astNode* sord = stmt->child_list->child_first;
			char* value = sord->child_list->child_first->lexicalTOKEN->lexeme_value;
			char* ls=(char*)findelement(value,variable);

			if(ls == NULL){
				ls = (char*)findelement(value,globalvar);
			}

			listnasm* lsn=recordvarible(ls);
			listnasm* head=lsn;
			listnasm* arr[maxNumFields+1];
			int m=0;
			int count =0;
			for(m=0;m<maxNumFields+1;m++)
			{
				arr[m]=NULL;
			}
			while(head!=NULL)
			{
				arr[count] = head;
				head = head->next;
				count++;
			}
			while(count>0)
			{
				fprintf(fp,"pop eax\nmov dword[%s.%s],eax\n",value,arr[count-1]->name);
				count--;
			}
		}
	}
	return;
}




void codegenerator(FILE* fp, ASTM* tree){
	
	//printf("y1\n");
	printNewline(fp);
	//printf("y2\n");
	takeUserInput(fp);
	//printf("y3\n");
	printDecimalNumber(fp);
	//printf("y4\n");
	printNegPos(fp);
	//printf("y5\n");

	fprintf(fp, "global _start\n_start:\nsection .bss\n");

	//bss section
	DeclareglobalVariablesInBss(fp);
	//printf("y7\n");
	DeclaremainVariablesInBss(fp);
	//printf("y9\n");

	fprintf(fp,".bufferop1\tresd\t%d\n", maxNumFields); //used for computations on record identifiers

	//text section
	fprintf(fp, "section .text\n");


	//printf("y10\n");

	//fclose(fp);
	

	astNode* stmts = tree->root->child_list->child_first->next;
	//printf("y11\n");

	
	astNode* otherstmts = stmts->child_list->child_first->next->next;
	//printf("y12\n");

	int i;
	astNode* temp = otherstmts;
	while(temp!=NULL && temp->label!=-2)
	{
		//printf("yo\n");
		//printf("label : %s\n", StringMap[temp->label] );	
		generatecode(fp,temp);
		temp = temp->concat;
	}
	fprintf(fp,"mov\tebx, 0\nmov\teax, 1\nint\t0x80\n");
	fclose(fp);
	return;

	
}