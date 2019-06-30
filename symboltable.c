
// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#include "symboltable.h"
#define INT 2
#define REAL 4
hashtable* generatehashtable(int slots)
{
	hashtable* h=(hashtable*)malloc(sizeof(hashtable));
	h->size=0;
	h->offset=0;
	h->slots=slots;
	h->table=(list**)malloc(sizeof(list*)*slots);
	h->head=NULL;
	h->tail=NULL;
	int i;
	for(i=0;i<slots;i++)
	{
		h->table[i]=NULL;
	}
	return h;
}
void errorlisttable()
{
	errorlist=(char**)malloc(sizeof(char*)*200);
	int i=0;
	for(i=0;i<200;i++)
	{
		errorlist[i]=NULL;
	}
}
void printarray()
{
	int i;
	for(i=0;i<200;i++)
	{
		if(errorlist[i]!=NULL)
			printf("%s\n",errorlist[i]);
	}
}
void insertlist(char* name,char* type,hashtable* h)
{
	listnasm* temp=(listnasm*)malloc(sizeof(listnasm));
	temp->name=name;
	temp->type=type;
	temp->next=NULL;
	if(h->tail==NULL)
	{
		h->head=temp;
		h->tail=temp;
	}
	else
	{
		h->tail->next=temp;
		h->tail=temp;
	}
}
void insertelement1(char* value,function_st* data,hashtable* h,int position)
{
	int index=function(h->slots,value);
	list* temp=(list*)malloc(sizeof(list));
	temp->value=value;
	temp->data=data;
	((function_st*)temp->data)->position=position;
	temp->next=h->table[index];
	h->table[index]=temp;
	h->size++;
}

void insertelement2(char* value,void* data,hashtable* h,int offset)
{
	// printf("checc\n\n");
	int index=function(h->slots,value);
	list* temp=(list*)malloc(sizeof(list));
	temp->value=value;
	temp->data=data;
	temp->offset=h->offset;
	h->offset=h->offset+offset;
	temp->next=h->table[index];
	h->table[index]=temp;
	h->size++;
}
void insertelement3(char* value,void* data,hashtable* h)
{
	int index=function(h->slots,value);
	list* temp=(list*)malloc(sizeof(list));
	temp->value=value;
	temp->data=data;
	temp->next=h->table[index];
	h->table[index]=temp;
	h->size++;
}

void* findelement(char* value,hashtable* h)
{
	int index=function(h->slots,value);
	list* temp=h->table[index];
	while(temp!=NULL && strcmp(value,temp->value)!=0)
	{
		temp=temp->next;
	}
	if(temp==NULL)
		return NULL;
	else
		return temp->data;
}
int findoffset(char* value,hashtable* h)
{
	int index=function(h->slots,value);
	list* temp=h->table[index];
	while(temp!=NULL && strcmp(value,temp->value)!=0)
	{
		temp=temp->next;
	}
	if(temp==NULL)
		return -1;
	else
		return temp->offset;
}
int justfind(char* value,hashtable* h)
{
	int index=function(h->slots,value);
	list* temp=h->table[index];
	while(temp!=NULL && strcmp(value,temp->value)!=0)
	{
		temp=temp->next;
	}
	if(temp==NULL)
		return 0;
	else
		return 1;
}
int function(int mod,char* str)
{
	int i=0;
	int val = 0;
	while(str[i]!='\0')
	{
		val = (val + str[i])%mod;
		i++;
	}
	i=0;
	while(str[i]!='\0')
	{
		i++;
	}
	return val;
}



void fillsymboltable1(astNode* root)
{
	if(root==NULL)
		return;
	astNode* temp=root->child_list->child_first;
	while(temp->concat!=NULL)
	{
	// 	//printf("%s\n",temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		insertlist(temp->child_list->child_first->lexicalTOKEN->lexeme_value,NULL,func);
		functiontable1(temp,temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		temp=temp->concat;
	}
	temp=root->child_list->child_first->next;
	maintable1(temp);
}
void fillsymboltable(astNode* root)
{
	if(root==NULL)
		return;
	astNode* temp=root->child_list->child_first;
	while(temp->concat!=NULL)
	{
	// 	//printf("%s\n",temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		functiontable(temp,temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		temp=temp->concat;
	}
	temp=root->child_list->child_first->next;
	maintable(temp);
}
void fillsymboltable0(astNode* root)
{
	if(root==NULL)
		return;
	astNode* temp=root->child_list->child_first;
	while(temp->concat!=NULL)
	{
	// 	//printf("%s\n",temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		functiontable0(temp,temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		temp=temp->concat;
	}
	temp=root->child_list->child_first->next;
	maintable0(temp);
}
void maintable(astNode* root)
{
	// fill_record(root->child_list->child_first);
	fill_variable(root->child_list->child_first->next,variable);
}
void maintable0(astNode* root)
{
	// fill_record(root->child_list->child_first);
	fill_variable0(root->child_list->child_first->next,variable);
}
void maintable1(astNode* root)
{
	fill_record(root->child_list->child_first);
	// fill_variable(root->child_list->child_first->next,variable);
}
function_st* create_function_st_node()
{
	function_st* temp=(function_st*)malloc(sizeof(function_st));
	temp->input=NULL;
	temp->output=NULL;
	temp->variable=generatehashtable(10);
	temp->position=0;
}
void functiontable(astNode* root,char* name)
{
	function_st* temp=(function_st*)findelement(name,func);
	// insertelement1(name,temp,func,func->size);
	temp->input=fill_list(root->child_list->child_first->next,temp->variable);
	temp->output=fill_list(root->child_list->child_first->next->next,temp->variable);
	// if(root->child_list->child_first->next->next->next->child_list->child_first==NULL)
	// 		printf("maybe\n");
	// fill_record(root->child_list->child_first->next->next->next->child_list->child_first);
	fill_variable(root->child_list->child_first->next->next->next->child_list->child_first->next,temp->variable);
	matchformalinformal(temp->output,root->child_list->child_first->next->next->next->child_list->child_first->next->next->next->child_list->child_first,name);
}
void functiontable0(astNode* root,char* name)
{
	function_st* temp=(function_st*)findelement(name,func);
	// insertelement1(name,temp,func,func->size);
	// temp->input=fill_list(root->child_list->child_first->next,temp->variable);
	// temp->output=fill_list(root->child_list->child_first->next->next,temp->variable);
	// if(root->child_list->child_first->next->next->next->child_list->child_first==NULL)
	// 		printf("maybe\n");
	// fill_record(root->child_list->child_first->next->next->next->child_list->child_first);
	fill_variable0(root->child_list->child_first->next->next->next->child_list->child_first->next,temp->variable);
	// matchformalinformal(temp->output,root->child_list->child_first->next->next->next->child_list->child_first->next->next->next->child_list->child_first,name);
}
void matchformalinformal(list* l,astNode* root,char* c)
{
	astNode* zx=root;

	while(l!=NULL && (root!=NULL && root->label!=-2))
	{

		char* e=root->lexicalTOKEN->lexeme_value;
		char* d=determinetype(root->lexicalTOKEN->lineNo,e,c);

		if(d!=NULL)
		{
			if(strcmp((char*)l->data,d)!=0)
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: The type %s of variable %s returned does not match with the type %s of the formal output parameter %s\n",root->lexicalTOKEN->lineNo,d,e,(char*)l->data,l->value);
				errorlist[root->lexicalTOKEN->lineNo]=xx;
			}
		}

		l=l->next;
		root=root->concat;
	}

	if(l==NULL && !(root!=NULL && root->label!=-2))
	{

	}
	else
	{
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Line %d: The number of return parametrs at function call %s is incorrect\n",zx->lexicalTOKEN->lineNo,c);
		errorlist[zx->lexicalTOKEN->lineNo]=xx;
	}
}
void functiontable1(astNode* root,char* name)
{
	if(findelement(name,func)!=NULL)
	{
		printf("Error1\n");
		return;
	}
	function_st* temp=create_function_st_node();
	insertelement1(name,temp,func,func->size);
	fill_record(root->child_list->child_first->next->next->next->child_list->child_first);
}
list* generatelist()
{
	list* temp=(list*)malloc(sizeof(list));
	temp->value=NULL;
	temp->data=NULL;
	temp->next=NULL;
	temp->offset=0;
	return temp;
}
list* fill_list(astNode* root,hashtable* h)
{
	list *temp=generatelist();
	list* temp1=temp;
	// printf("%d label\n", root->label);
	char i[4]="int";
	char r[5]="real";
	while(root->concat!=NULL)
	{
		// printf("%s gogog \n", root->child_list->child_first->lexicalTOKEN->lexeme_value);
		temp->next=generatelist();
		temp=temp->next;
		temp->value=root->child_list->child_first->next->lexicalTOKEN->lexeme_value;
		temp->data=(void*)root->child_list->child_first->lexicalTOKEN->lexeme_value;
		if(findelement(temp->value,globalvar))
		{
			char* xx=(char*)malloc(sizeof(char*)*50);
			sprintf(xx,"Line %d: Variable %s being a global variable, cannot be declared more than once\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp->value);
			errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
		}
		if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,i)==0)
			insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,(void*)root->child_list->child_first->lexicalTOKEN->lexeme_value,h,INT);
		else if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,r)==0)
			insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,(void*)root->child_list->child_first->lexicalTOKEN->lexeme_value,h,REAL);
		else if(findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record)!=NULL)
		{
			// printf("blame\n");
			insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,(void*)root->child_list->child_first->lexicalTOKEN->lexeme_value,h,((hashtable*)findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record))->offset);
		}
		else
		{
			printf("Error2\n");
		}

		root=root->concat;
	}
	return temp1->next;
}
void fill_record(astNode* root)
{
	astNode* subroot=NULL;
	hashtable* temp=NULL;
	char i[4]="int";
	char r[5]="real";
	while(root->concat!=NULL)
	{
		if(findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record))
		{
			printf("Error6\n");
		}
		else
		{
			insertlist(root->child_list->child_first->lexicalTOKEN->lexeme_value,NULL,record);
			temp=generatehashtable(5);
			insertelement3(root->child_list->child_first->lexicalTOKEN->lexeme_value,temp,record);
			subroot=root->child_list->child_first->next;
			while(subroot->concat!=NULL)
			{
				// printf("checkasdfasdfasdfasdf\n");
				if(findelement(subroot->child_list->child_first->next->lexicalTOKEN->lexeme_value,temp))
					printf("Error7\n");
				else
				{
					insertlist(subroot->child_list->child_first->next->lexicalTOKEN->lexeme_value,subroot->child_list->child_first->lexicalTOKEN->lexeme_value,temp);
					if(strcmp(subroot->child_list->child_first->lexicalTOKEN->lexeme_value,i)==0)
						insertelement2(subroot->child_list->child_first->next->lexicalTOKEN->lexeme_value,subroot->child_list->child_first->lexicalTOKEN->lexeme_value,temp,INT);
					else if(strcmp(subroot->child_list->child_first->lexicalTOKEN->lexeme_value,r)==0)
						insertelement2(subroot->child_list->child_first->next->lexicalTOKEN->lexeme_value,subroot->child_list->child_first->lexicalTOKEN->lexeme_value,temp,REAL);
					else
						printf("Error3\n");
				}
				subroot=subroot->concat;
			}
			root=root->concat;
		}
	}
}

void fill_variable(astNode* root,hashtable* h)
{
	char i[4]="int";
	// printf("%s\n",i);
	char r[5]="real";
	while(root->concat!=NULL)
	{
		// printf("%s\n",root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
		
		if(root->child_list->child_first->next->next->lexicalTOKEN->lexeme_value!=NULL)
		{
			
		}
		else
		{
			if(findelement(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,globalvar))
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: Variable %s being a global variable, cannot be declared more than once\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
				errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
			}
			else if(findelement(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,h))
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: The identifier %s is declared more than once\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
				errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
			}
			else
			{		
				insertlist(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,h);
				if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,i)==0)
				{
					// printf("test\n\n\n\n");
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,h,INT);
				}
				else if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,r)==0)
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,h,REAL);
				else if(findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record)!=NULL)
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,h,((hashtable*)findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record))->offset);
				else
					printf("Error5\n");
			}
		}
		root=root->concat;
	}
}

void fill_variable0(astNode* root,hashtable* h)
{
	char i[4]="int";
	// printf("%s\n",i);
	char r[5]="real";
	while(root->concat!=NULL)
	{
		// printf("%s\n",root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
		if(findelement(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,globalvar))
		{
			char* xx=(char*)malloc(sizeof(char*)*50);	
			sprintf(xx,"Line %d: Variable %s being a global variable, cannot be declared more than once\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
			errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
		}
		else if(findelement(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,h))
		{
			char* xx=(char*)malloc(sizeof(char*)*50);	
			sprintf(xx,"Line %d: The identifier %s is declared more than once\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,root->child_list->child_first->next->lexicalTOKEN->lexeme_value);
			errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
		}
		else
		{
			if(root->child_list->child_first->next->next->lexicalTOKEN->lexeme_value!=NULL)
			{
				insertlist(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,globalvar);
				if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,i)==0)
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,globalvar,INT);
				else if(strcmp(root->child_list->child_first->lexicalTOKEN->lexeme_value,r)==0)
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,globalvar,REAL);
				else if(findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record)!=NULL)
					insertelement2(root->child_list->child_first->next->lexicalTOKEN->lexeme_value,root->child_list->child_first->lexicalTOKEN->lexeme_value,globalvar,((hashtable*)findelement(root->child_list->child_first->lexicalTOKEN->lexeme_value,record))->offset);
				else
					printf("Error4\n");
			}
		}
		root=root->concat;
	}
}

void printfunc()
{
	int i=0;
	for(i=0;i<func->slots;i++)
	{
		list* temp=func->table[i];
		while(temp!=NULL)
		{
			printf("%s Function Name ",temp->value);
			function_st* temp1=(function_st*)temp->data;
			printf("%d Position\n",temp1->position);
			list* input=temp1->input;
			while(input!=NULL)
			{
				// printf("check\n");
				printf("%s Input Parameter name ",input->value);
				printf("%s Type \n",(char*)input->data);
				// printf("%d Offset\n",input->offset);
				input=input->next;
			}
			input=temp1->output;
			while(input!=NULL)
			{
				printf("%s Output Parameter name ",input->value);
				printf("%s Type \n",(char*)input->data);
				// printf("%d Offset\n",input->offset);
				input=input->next;
			}
			printvar(temp1->variable);
			temp=temp->next;

		}
	}
}
void printvar(hashtable* h)
{
	int i=0;
	for(i=0;i<h->slots;i++)
	{
		list* temp=h->table[i];
		while(temp!=NULL)
		{
			printf("%s Variable name ",temp->value);
			printf("%s Type ",(char*)temp->data );
			printf("%d Offset\n",temp->offset);
			temp=temp->next;

		}
	}
}





void printglobalvar(hashtable* h)
{
	int i=0;
	for(i=0;i<h->slots;i++)
	{
		list* temp=h->table[i];
		while(temp!=NULL)
		{
			printf("%s 	",temp->value);
			printf("%s  ",(char*)temp->data );
			printf("%d \n",temp->offset);
			temp=temp->next;

		}
	}
}



void printrecord()
{
	int i=0;
	for(i=0;i<record->slots;i++)
	{
		list* temp=record->table[i];
		while(temp!=NULL)
		{
			printf("%s Record Type\n",temp->value);
			printvar((hashtable*)temp->data);
			temp=temp->next;

		}
	}
}

void recordprint()
{
	int i=0;
	for(i=0;i<record->slots;i++)
	{
		list* temp=record->table[i];
		while(temp!=NULL)
		{
			printf("%s 	",temp->value);
			printvar1((hashtable*)temp->data);
			temp=temp->next;

		}
	}
}

void printvar1(hashtable* h)
{
	int i=0;
	for(i=0;i<h->slots;i++)
	{
		list* temp=h->table[i];
		while(temp!=NULL)
		{
			//printf("%s Variable name ",temp->value);
			printf("%s , ",(char*)temp->data );
			//printf("%d Offset\n",temp->offset);
			temp=temp->next;

		}
	}
		printf("%d \n",h->offset);

}


listnasm* mainvariable()
{
	return variable->head;
}
listnasm* globalvariable()
{
	return globalvar->head;
}

listnasm* recordvarible(char* type)
{
	hashtable* h=(hashtable*)findelement(type,record);
	return h->head;
}
listnasm* funclist()
{
	return func->head;
}

void printnasmlist(listnasm* l)
{
	while(l!=NULL)
	{
		printf("Name= %s\n",l->name);
		if(l->type!=NULL)
		{
			printf("Type=%s\n", l->type);
			if(strcmp(l->type,"int")!=0 && strcmp(l->type,"real")!=0)
				printnasmlist(recordvarible(l->type));
		}
		l=l->next;
	}
}

void printsymboltable()
{
	listnasm* l=funclist();
	listnasm* l1;
	listnasm* l2;
	function_st* h;
	list* temp;
	while(l!=NULL)
	{
		h=(function_st*)findelement(l->name,func);
		temp=h->input;
		while(temp!=NULL)
		{
			printf("%s\t",temp->value);
			if(strcmp((char*)temp->data,"int")==0 || strcmp((char*)temp->data,"real")==0)
				printf("%s\t",(char*)temp->data);
			else
			{
				l1=recordvarible((char*)temp->data);
				while(l1->next!=NULL)
				{
					printf("%sx",l1->type);
					l1=l1->next;
				}
				printf("%s ",l1->type);
			}
			printf("%s\t",l->name);
			printf("%d\n\n",findoffset(temp->value,h->variable));
			temp=temp->next;
		}
		temp=h->output;
		while(temp!=NULL)
		{
			printf("%s\t",temp->value);
			if(strcmp((char*)temp->data,"int")==0 || strcmp((char*)temp->data,"real")==0)
				printf("%s\t",(char*)temp->data);
			else
			{
				l1=recordvarible((char*)temp->data);
				while(l1->next!=NULL)
				{
					printf("%sx",l1->type);
					l1=l1->next;
				}
				printf("%s\t",l1->type);
			}
			printf("%s\t",l->name);
			printf("%d\n\n",findoffset(temp->value,h->variable));
			temp=temp->next;
		}
		l2=h->variable->head;
		while(l2!=NULL)
		{
			printf("%s\t",l2->name);
			if(strcmp(l2->type,"int")==0 || strcmp(l2->type,"real")==0)
				printf("%s\t",l2->type);
			else
			{
				l1=recordvarible(l2->type);
				while(l1->next!=NULL)
				{
					printf("%sx",l1->type);
					l1=l1->next;
				}
				printf("%s\t",l1->type);
			}
			printf("%s\t",l->name);
			printf("%d\n\n",findoffset(l2->name,h->variable));
			l2=l2->next;
		}
		l=l->next;
	}
	l=globalvariable();
	while(l!=NULL)
	{
		printf("%s\t",l->name);
		if(strcmp(l->type,"int")==0 || strcmp(l->type,"real")==0)
			printf("%s\t",l->type);
		else
		{
			l1=recordvarible(l->type);
			while(l1->next!=NULL)
			{
				printf("%sx",l1->type);
				l1=l1->next;
			}
			printf("%s\t",l1->type);
		}
		printf("global\n\n");
		l=l->next;
	}
	l=mainvariable();
	while(l!=NULL)
	{
		printf("%s\t",l->name);
		if(strcmp(l->type,"int")==0 || strcmp(l->type,"real")==0)
			printf("%s\t",l->type);
		else
		{
			l1=recordvarible(l->type);
			while(l1->next!=NULL)
			{
				printf("%sx",l1->type);
				l1=l1->next;
			}
			printf("%s\t",l1->type);
		}
		printf("_main\t");
		printf("%d\n\n",findoffset(l->name,variable));
		l=l->next;
	}
				
}


void functionsize()
{
	listnasm* l=funclist();
	listnasm* l1;
	listnasm* l2;
	function_st* h;
	list* temp;
	while(l!=NULL)
	{
		h=(function_st*)findelement(l->name,func);
		
		printf("\n%s 		%d\n",l->name,h->variable->offset);
		l=l->next;
	}	
				
}

void verifyallsymboltable(astNode* root)
{

	if(root==NULL)
		return;
	astNode* temp=root->child_list->child_first;
	while(temp->concat!=NULL)
	{
		// printf("asdfa\n\n\n\n\n");
		verifysymboltable(temp->child_list->child_first->next->next->next,temp->child_list->child_first->lexicalTOKEN->lexeme_value);
		temp=temp->concat;
	}
	// printf("asdfa\n\n\n\n\n");
	temp=root->child_list->child_first->next;
	verifysymboltable(temp,NULL);
}
void verifysymboltable(astNode* root,char* c)
{
	root=root->child_list->child_first->next->next;
	listhash* l=NULL;
	// printf("sdfasdf\n\n\n\n");
	while(root!=NULL && root->label!=-2)
	{
		// printf("%s\n\n\n\n",c);
		// printf("sdfasdf\n\n\n\n");
		if(root->label==assignentStmt_node)
		{
			// printf("sdfasdf\n\n\n\n");
			assignmentcheck(root,c);
		}
		else if(root->label==iterativeStmt_node)
		{
			whilecheck(root,l,c);
		}
		else if(root->label==conditionalStmt_node)
		{
			// printf("%s conditionalwhilecheck\n\n\n\n",c);
			conditionalwhilecheck(root,l,c);
		}
		else if(root->label==ioStmt1_node)
		{
			// printf("%s\n\n\n\n",c);
			io1check(root,c);
		}
		else if(root->label==ioStmt2_node)
		{
			io2check(root,c);
			// printf("%sqqqqqq\n\n\n\n",c);
		}
		else if(root->label==funCallStmt_node)
		{
			funccheck(root,c);
		}
		root=root->concat;
	}
}
void conditionalcheck(astNode* root,char* c)
{

}
listhash* generatelisthash(hashtable* h)
{
	listhash* l=(listhash*)malloc(sizeof(listhash));
	l->h=h;
	l->check=0;
	l->next=NULL;
	return l;
}
void whilecheck(astNode* root,listhash* li,char* c)
{
	// printf("%d endwhile\n\n\n\n",root->end_while);
	listhash* l=generatelisthash(generatehashtable(10));
	l->next=li;
	traverse(root->child_list->child_first->child_list->child_first,l->h,c);
	astNode* temp=root->child_list->child_first->next;
	while(temp!=NULL && temp->label!=-2)
	{
		traverse1(temp,l,c);
		temp=temp->concat;
	}
	if(l->check==0)
	{
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Lines %d-%d: None of the variables participating in the iterations of the while loop gets updated\n",root->start_while,root->end_while);
		errorlist[root->start_while]=xx;
	}
}
void traverse1(astNode* root,listhash* l,char* c)
{
	// printf("justchecking %s\n\n\n\n\n",c);
	if(root->label==assignentStmt_node)
	{
		// printf("%d\n",l->check );
		assignmentwhilecheck(root,l,c);
		// printf("%d\n",l->check );
	}
	else if(root->label==iterativeStmt_node)
	{
		whilecheck(root,l,c);
	}
	else if(root->label==conditionalStmt_node)
	{
		conditionalwhilecheck(root,l,c);
	}
	else if(root->label==ioStmt1_node)
	{
		io1whilecheck(root,l,c);
	}
	else if(root->label==ioStmt1_node)
	{
		io2check(root,c);
	}
	else if(root->label==funCallStmt_node)
	{
		// printf("%s\n",c);
		funcwhilecheck(root,l,c);
		// printf("%d\n",l->check );
		// printf("%s\n",c);
	}

}
void funcwhilecheck(astNode* root,listhash* l,char* c)
{
	astNode* temp=root->child_list->child_first->child_list->child_first;
	while(temp==NULL || temp->label==-2)
	{
		while(l!=NULL)
		{
			if(l->check==0)
			{
				if(justfind(temp->lexicalTOKEN->lexeme_value,l->h)==1)
				{
					l->check=1;
				}
			}
			l=l->next;
		}
		temp=temp->concat;
	}
	funccheck(root,c);
}

void funccheck(astNode* root,char* c)
{
	char* temp=root->child_list->child_first->next->lexicalTOKEN->lexeme_value;
	// printf("%s\n\n\n\n\n",temp);
	function_st* zz=(function_st*)findelement(temp,func);
	if(zz==NULL)
	{
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Line %d: The function %s is undefined.\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp);
		errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
	}
	else
	{
		if(c!=NULL)
		{
			function_st* yy=(function_st*)findelement(c,func);
			if(zz->position>=yy->position)
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: The function %s is undefined.\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp);
				errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
			}
		}
	}
	function_st* temp1=(function_st*)findelement(temp,func);
	astNode* temp2=root->child_list->child_first->child_list->child_first;
	list* temp3=temp1->output;
	while(temp3!=NULL && (temp2!=NULL && temp2->label!=-2))
	{
		// printf("%s\n\n\n\n\n",(char*)temp3->data);
		char* zzz=(char*)temp3->data;
		char* yyy=determinetype(temp2->lexicalTOKEN->lineNo,temp2->lexicalTOKEN->lexeme_value,c);
		if(yyy!=NULL)
		{
			if(strcmp(zzz,yyy)!=0)
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: Type mismatch %s %s and %s %s\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp3->value,zzz,temp2->lexicalTOKEN->lexeme_value,yyy);
				errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
			}
		}
		temp3=temp3->next;
		temp2=temp2->concat;
	}
	if(temp3==NULL && !(temp2!=NULL && temp2->label!=-2))
	{

	}
	else
	{
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Line %d: The number of output parametrs at function call %s is incorrect\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp);
		errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
	}
	temp3=temp1->input;
	temp2=root->child_list->child_first->next->next->child_list->child_first;
	// printf("%s\n\n\n\n\n",temp);
	while(temp3!=NULL && (temp2!=NULL && temp2->label!=-2))
	{
		// printf("%s\n\n\n\n\n",(char*)temp3->data);
		char* zzz=(char*)temp3->data;
		char* yyy=determinetype(temp2->lexicalTOKEN->lineNo,temp2->lexicalTOKEN->lexeme_value,c);
		if(yyy!=NULL)
		{
			if(strcmp(zzz,yyy)!=0)
			{
				char* xx=(char*)malloc(sizeof(char*)*50);
				sprintf(xx,"Line %d: Type mismatch %s %s and %s %s\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp3->value,zzz,temp2->lexicalTOKEN->lexeme_value,yyy);
				errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
			}
		}
		temp3=temp3->next;
		temp2=temp2->concat;
	}
	if(temp3==NULL && !(temp2!=NULL && temp2->label!=-2))
	{

	}
	else
	{
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Line %d: The number of input parametrs at function call %s is incorrect\n",root->child_list->child_first->next->lexicalTOKEN->lineNo,temp);
		errorlist[root->child_list->child_first->next->lexicalTOKEN->lineNo]=xx;
	}
}


void conditionalwhilecheck(astNode* root,listhash* l,char* c)
{
	astNode* temp=root->child_list->child_first->next;
	while(temp!=NULL && temp->label!=-2)
	{

		traverse1(temp,l,c);
		// printf("onestatement\n\n\n\n\n");
		temp=temp->concat;
	}
	temp=root->child_list->child_first->next->next;	
	if(temp==NULL || temp->label==-2)
		return ;
	traverse1(temp->child_list->child_first,l,c);
	temp=temp->child_list->child_first->next;
	while(temp!=NULL && temp->label!=-2)
	{
		traverse1(temp,l,c);
		temp=temp->concat;
	}
}
void io1whilecheck(astNode* root,listhash* l,char* c)
{
	// printf("%s\n\n\n\n",c);
	astNode* temp=root->child_list->child_first->child_list->child_first;
	// printf("%s\n\n\n\n",c);
	if(temp->next==NULL || temp->next->label==-2)
	{
		// printf("%s\n\n\n\n",c);
		while(l!=NULL)
		{
			if(l->check==0)
			{
				if(justfind(temp->lexicalTOKEN->lexeme_value,l->h)==1)
				{
					l->check=1;
				}
			}
			l=l->next;
		}
	}
	// printf("%s\n\n\n\n",c);
	io1check(root,c);	
}
void io1check(astNode* root,char* c)
{
	// printf("%s\n\n\n\n",c);	
	char* d=root->child_list->child_first->child_list->child_first->lexicalTOKEN->lexeme_value;
	// printf("%s\n\n\n\n",c);
	char* e=determinetype(root->child_list->child_first->child_list->child_first->lexicalTOKEN->lineNo,d,c);
	// printf("%s\n\n\n\n",e);
	if(root->child_list->child_first->child_list->child_first->next!=NULL && root->child_list->child_first->child_list->child_first->next->label!=-2)
	{
		// printf("%s\n\n\n\n",c);
		char* f=root->child_list->child_first->child_list->child_first->next->lexicalTOKEN->lexeme_value;
		// printf("%s\n\n\n\n",c);
		char* g=determinetype1(f,e);
		// printf("%s\n\n\n\n",g);
	}
}
void io2check(astNode* root,char* c)
{
	// printf("%s\n\n\n\n",c);	
	char* d=root->child_list->child_first->child_list->child_first->lexicalTOKEN->lexeme_value;
	// printf("%s\n\n\n\n",c);
	char* e=determinetype(root->child_list->child_first->child_list->child_first->lexicalTOKEN->lineNo,d,c);
	// printf("%s\n\n\n\n",e);
	if(root->child_list->child_first->child_list->child_first->next!=NULL && root->child_list->child_first->child_list->child_first->next->label!=-2)
	{
		// printf("%s\n\n\n\n",c);
		char* f=root->child_list->child_first->child_list->child_first->next->lexicalTOKEN->lexeme_value;
		// printf("%s\n\n\n\n",c);
		char* g=determinetype1(f,e);
		// printf("%s\n\n\n\n",g);
	}
}
void assignmentwhilecheck(astNode* root,listhash* l,char* c)
{
	astNode* temp=root->child_list->child_first->child_list->child_first;
	if(temp->next==NULL || temp->next->label==-2)
	{
		while(l!=NULL)
		{
			if(l->check==0)
			{
				if(justfind(temp->lexicalTOKEN->lexeme_value,l->h)==1)
				{
					l->check=1;
				}
			}
			l=l->next;
		}

	}
	// printf("%sasd\n\n\n\n", c);
	assignmentcheck(root,c);
}
void assignmentcheck(astNode* root,char* c)
{
	// printf("sdfasdf\n\n\n\n");
	astNode* temp=root->child_list->child_first->child_list->child_first;
	char* d;
	if(temp->next==NULL || temp->next->label==-2)
	{
		// printf("sdfasdf\n\n\n\n");
		d=determinetype(temp->lexicalTOKEN->lineNo,temp->lexicalTOKEN->lexeme_value,c);
		// printf("%s\n\n\n\n",d);
	}
	else
	{
		d=determinetype1(temp->next->lexicalTOKEN->lexeme_value,determinetype(temp->lexicalTOKEN->lineNo,temp->lexicalTOKEN->lexeme_value,c));
	}
	// printf("sdfasdf\n\n\n\n");
	assignmentcheckutil(root->child_list->child_first->next->next,d,c);
	// printf("%ssddddd\n\n\n\n",d);
}
void assignmentcheckutil(astNode* root,char* d,char* c)
{
	if(root==NULL)
		return ;
	// printf("%ssddasdfsa\n\n\n\n",d);
	if(root->child_list->child_first->next==NULL || root->child_list->child_first->next->label==-2)
	{
		// printf("%s\n\n\n\n",root->child_list->child_first->lexicalTOKEN->lexeme_value);
		return ;
	}
	// printf("%s\n\n\n\n",d);
	char* z=root->child_list->child_first->next->lexicalTOKEN->lexeme_value;
	// printf("%s\n\n\n\n",z);
	char* y=root->child_list->child_first->next->lexicalTOKEN->lexeme_value;
	if(z[0]=='*' || y[0]=='/' )
	{
		if(root->child_list->child_first->label==all_node1 && root->child_list->child_first->next->next->label==all_node1)
		{
			if(root->child_list->child_first->child_list->child_first->next==NULL || root->child_list->child_first->child_list->child_first->next->label==-2)
			{
				if(root->child_list->child_first->next->next->child_list->child_first->next==NULL || root->child_list->child_first->next->next->child_list->child_first->next->label==-2)
					if(determinetype(root->child_list->child_first->next->next->child_list->child_first->lexicalTOKEN->lineNo,root->child_list->child_first->next->next->child_list->child_first->lexicalTOKEN->lexeme_value,c)[0]=='#')
						printf("error10\n");
			}	
		}
	}
	if(root->label==all_node1)	
	{
		
		if(root->child_list->child_first->next==NULL || root->child_list->child_first->next->label==-2)
		{
			char* z=root->child_list->child_first->lexicalTOKEN->lexeme_value;
			if(strcmp(d,determinetype(root->child_list->child_first->lexicalTOKEN->lineNo,z,c))!=0)
				printf("error11\n");
		}
		else
		{
			char* z=root->child_list->child_first->next->lexicalTOKEN->lexeme_value;
			if(strcmp(d,determinetype(root->child_list->child_first->next->lexicalTOKEN->lineNo,z,c))!=0)
				printf("error14\n");
		}
	}
	else if(root->label==all_node2)
	{
		if(strcmp(d,"int")!=0)
			printf("error12\n");
	}
	else if(root->label==all_node3)
	{
		if(strcmp(d,"real")!=0)
			printf("error13\n");
	}
	else
	{
		// printf("asdfas\n\n\n\n\n");
		assignmentcheckutil(root->child_list->child_first,d,c);
		assignmentcheckutil(root->child_list->child_first->next->next,d,c);
	}
}

void traverse(astNode* root,hashtable* h,char* c)
{
	if(root==NULL)
		return ;
	if(root->label==booleanExpression2_node)
	{
		char* z=root->child_list->child_first->lexicalTOKEN->lexeme_value;
		char* y=root->child_list->child_first->next->next->lexicalTOKEN->lexeme_value;
		if(strcmp(determinetype(root->child_list->child_first->lexicalTOKEN->lineNo,z,c),determinetype(root->child_list->child_first->next->next->lexicalTOKEN->lineNo,y,c))!=0)
		{
			printf("Error9");
		}
	}
	if(root->label==-1)
		insertelement3(root->lexicalTOKEN->lexeme_value,NULL,h);
	traverse(root->next,h,c);
	if(root->child_list!=NULL)
	{
		traverse(root->child_list->child_first,h,c);
	}
}

char* determinetype(int line,char* value,char* c)
{
	char* d=(char*)findelement(value,c==NULL?variable:(((function_st*)findelement(c,func))->variable));
	if(d==NULL)
		d=(char*)findelement(value,globalvar);
	if(d==NULL)
	{
		// printf("%s     %s\n",value,c);
		char* xx=(char*)malloc(sizeof(char*)*50);
		sprintf(xx,"Line %d:variable %s is not declared\n",line,value);
		errorlist[line]=xx;
	}
	return d;
}

char* determinetype1(char* value,char* c)
{
	hashtable* h=(hashtable*)findelement(c,record);
	return (char*)findelement(value,h);
}