// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"

//Grammar functions

void printRules(Grammar *G)
{
	int i=0;
	for(i=0;i<G->rules->size;i++)
	{
		linkedlist* temp1 = G->rules->arr[i];
		int size = temp1->size;
		node* temp = temp1->root;
		int j=0;
		int status = temp->status;
		int val = temp->val;
		if(status ==1)
		{
			printf("%d. %s -->",temp1->ruleno,G->nonterminals->arr[val]->str );
		}
		else
		{
			printf("%d. %s -->",temp1->ruleno,G->terminals->arr[val]);
		}
		temp = temp->next;
		for(j=1;j<size;j++)
		{
			status = temp->status;
			val = temp->val;
			if(status ==1)
			{
				printf(" %s ",G->nonterminals->arr[val]->str );
			}
			else
			{
				printf(" %s ",G->terminals->arr[val]);
			}
			temp = temp->next;
		}
		printf("\n");
	}
}

void printnonterminals(Grammar *G)
{
	int i=0;
	int j=0;
	int k=0;
	for(i=0;i<G->nonterminals->size;i++)
	{
		printf("%d . %s \n",i+1,G->nonterminals->arr[i]->str);
		int y = G->nonterminals->arr[i]->rule_nos->size;
		node3* temp1 = G->nonterminals->arr[i]->rule_nos->root;
		for(k=0;k<y;k++)
		{
			linkedlist *ls = G->rules->arr[temp1->ruleno];
			int x = ls->size;
			node *temp = ls->root;
			if(temp->status==0)
			{
				printf("%d. %s ===> ",i+1,G->terminals->arr[temp->val]);
			}
			else
			{
				printf(" %s ===> ",G->nonterminals->arr[temp->val]->str);
			}
			temp = temp->next;
			for(j=0;j<x-1;j++)
			{
				if(temp->status==0)
				{
					printf(" %s ",G->terminals->arr[temp->val]);
				}
				else
				{
					printf(" %s ",G->nonterminals->arr[temp->val]->str);
				}
				temp = temp->next;
			}
			printf("\n");
			temp1 = temp1->next;
		}
	
	}

}

void addinlinkedlist(linkedlist *ls,int val,int status)
{
	if(ls==NULL)
	{
		printf("NULL list\n");
		return ;
	}
	if(ls->size > 0 && ls->root==NULL)
	{
		printf("nothing added in list previously\n");
		return ;
	}
	node* new1 = (node*)malloc(sizeof(node));
	new1->val = val;
	new1->status = status;
	new1->next = NULL;
	if(ls->size == 0)
	{
		ls->root = new1;
	}
	else
	{
		int i=0;
		node* temp = ls->root;
		for(i=0;i<ls->size-1;i++)
		{
			temp=temp->next;
		}
		temp->next = new1;
	}
	ls->size = ls->size+1;
}

void addinrules_st(Grammar *G,int val,int status,int i)
{
	if(G==NULL || G->rules==NULL || G->rules->arr==NULL)
	{
		printf("error!!");
		return ;
	}
	if(i==G->rules->size)
	{
		if(G->rules->size == G->rules->capacity)
		{
			G->rules->capacity = 2*G->rules->capacity;
			G->rules->arr = realloc(G->rules->arr,G->rules->capacity*sizeof(rules_st));
			int j=0;
			for(j=G->rules->size;j<G->rules->capacity;j++)
			{
				G->rules->arr[j] = NULL;
			}
		}
		G->rules->size = G->rules->size+1;
		if(G->rules->arr[i]==NULL)
		{
			G->rules->arr[i] = (linkedlist*)malloc(sizeof(linkedlist));
			G->rules->arr[i]->size = 0;
			G->rules->arr[i]->ruleno = i+1;
			G->rules->arr[i]->root = NULL;
		}
		addinlinkedlist(G->rules->arr[i],val,status);
	}
	else if(i == G->rules->size-1)
	{
		G->rules->arr[i]->ruleno = i+1;
		addinlinkedlist(G->rules->arr[i],val,status);
	}
	else
	{
		printf("wrong index provided!!");
		return ;
	}
}


void addinlinkedlist3(linkedlist3 *ls,int ruleno)
{
	if(ls==NULL)
	{
		printf("wrong list3 \n");
		return ;
	}
	if(ls->size>0 && ls->root==NULL)
	{
		printf("how can this even happen? \n");
		return ;
	}
	node3 *new1 = (node3*)malloc(sizeof(node3));
	new1->ruleno = ruleno;
	new1->next = NULL;
	if(ls->size == 0)
	{
		ls->root = new1;
	}
	else
	{
		node3* temp = ls->root;
		ls->root = new1;
		new1->next = temp;
	}
	ls->size = ls->size+1;
}


void addrulenoinnon_terminals_st(Grammar *G,int ruleno,int i)
{
	if(G==NULL || G->nonterminals==NULL || G->nonterminals->arr==NULL || i >= G->nonterminals->size || G->nonterminals->arr[i]==NULL || i<0 || G->nonterminals->arr[i]->rule_nos==NULL)
	{
		printf("grammar not initialised properly!! \n");
		return;
	}
	addinlinkedlist3(G->nonterminals->arr[i]->rule_nos,ruleno);
	
}

void addinnonterminals_st(Grammar *G,char* str)
{
	if(G==NULL || G->nonterminals ==NULL || G->nonterminals->arr ==NULL || str==NULL)
	{
		printf(" error in input of addinterminals_st \n");
	}
	if(G->nonterminals->size == G->nonterminals->capacity)
	{
		G->nonterminals->capacity = 2*G->nonterminals->capacity;
		G->nonterminals->arr = realloc(G->nonterminals->arr,G->nonterminals->capacity*sizeof(single_non_terminal_st*));
		int j=0;
		for(j=G->nonterminals->size;j<G->nonterminals->capacity;j++)
		{
			G->nonterminals->arr[j] = NULL;
		}
	}
	int i = G->nonterminals->size;
	if(G->nonterminals->arr[i]==NULL)
	{
		G->nonterminals->arr[i] = (single_non_terminal_st*)malloc(sizeof(single_non_terminal_st));
		G->nonterminals->arr[i]->rule_nos = (linkedlist3*)malloc(sizeof(linkedlist3));
		G->nonterminals->arr[i]->rule_nos->size =0;
		G->nonterminals->arr[i]->rule_nos->root = NULL;
		G->nonterminals->arr[i]->str = str;
	}
	G->nonterminals->size = G->nonterminals->size+1;
}

void addinterminals_st(Grammar *G,char* str)
{
	if(G==NULL || G->terminals ==NULL || G->terminals->arr ==NULL || str==NULL)
	{
		printf(" error in input of addinterminals_st \n");
	}
	if(G->terminals->size == G->terminals->capacity)
	{
		G->terminals->capacity = 2*G->terminals->capacity;
		G->terminals->arr = realloc(G->terminals->arr,G->terminals->capacity*sizeof(char*));
		int j=0;
		for(j=G->terminals->size;j<G->terminals->capacity;j++)
		{
			G->terminals->arr[j] = NULL;
		}
	}
	int i = G->terminals->size;
	G->terminals->arr[i] = str;
	G->terminals->size = G->terminals->size+1;
}

Grammar* createGrammar()
{
	Grammar* G = (Grammar*)malloc(sizeof(Grammar));
	
	G->nonterminals = (non_terminals_st*)malloc(sizeof(non_terminals_st));
	G->nonterminals->size = 0;
	G->nonterminals->capacity = 2;
	G->nonterminals->arr = (single_non_terminal_st**)malloc(G->nonterminals->capacity*sizeof(single_non_terminal_st*));
	
	G->terminals = (terminals_st*)malloc(sizeof(terminals_st));
	G->terminals->size = 0;
	G->terminals->capacity = 2;
	G->terminals->arr = (char**)malloc(G->terminals->capacity*sizeof(char*));
	
	G->start = 0;
	
	G->rules = (rules_st*)malloc(sizeof(rules_st));
	G->rules->size = 0;
	G->rules->capacity = 2;
	G->rules->arr = (linkedlist**)malloc(G->rules->capacity*sizeof(linkedlist*));
	
	G->searchtable = createHastable(23);
	int i=0;
	for(i=0;i<2;i++)
	{
		G->nonterminals->arr[i] = NULL;
		G->terminals->arr[i] = NULL;
		G->nonterminals->arr[i] = NULL;
	}
	
	return G;

}

int handleremaining(Grammar *G,char *buf,int i,int ruleno)
{
	char var[100];
	var[99]='\0';
	int status = 0;
	int l=0;
	while(buf[i]!='\n' && buf[i]!='|')
	{	
		//printf("d\n");
		l=0; 
		while(buf[i]==' ')
		{
			i++;
		}
		if(buf[i] =='\n' || buf[i]=='|')
		{
			return i;
		}
		if(buf[i] == 'T' && buf[i+1]=='K')
		{
			status = 0;
			var[l++] = 'T';
			var[l++] = 'K';
			i = i+2;
			while(buf[i]!=' ' && buf[i]!='\n' && buf[i]!='|')
			{
				var[l++] = buf[i++];
			}
			if(l>=3)
			{
				char *lhs = (char*)malloc((l+1)*sizeof(char));
				lhs[l] = '\0';
				int j=0;
				for(j=0;j<l;j++)
				{
					lhs[j] = var[j];
				}
				int x = searchhashtable(G->searchtable,lhs);
				if(x==-1)
				{
					x = G->terminals->size;
					addinhashtable(G->searchtable,lhs,x);
					addinterminals_st(G,lhs);
				}
				else
				{
				}
				addinrules_st(G,x,status,ruleno);
			}
		}
		else if(buf[i]=='<')
		{
			
			status = 1;
			var[l++] = '<';
			i++;
			while(buf[i]!='>' && buf[i]!='\n' && buf[i]!='|')
			{
				var[l++] = buf[i++];
			}
			if(buf[i]=='>')
			{
				var[l++] = buf[i++];
			}
			else
			{

				return i;
			}
			if(l>=3)
			{
				char *lhs = (char*)malloc((l+1)*sizeof(char));
				lhs[l] = '\0';
				int j=0;
				for(j=0;j<l;j++)
				{
					lhs[j] = var[j];
				}
				int x = searchhashtable(G->searchtable,lhs);
				if(x ==-1)
				{
					x = G->nonterminals->size;
					addinhashtable(G->searchtable,lhs,x);
					addinnonterminals_st(G,lhs);
				}
				else
				{
					//printf("x\n");
				}
				addinrules_st(G,x,status,ruleno);
			}
			else
			{
				//printf("error\n");
			}
			
			//printf("%d\n",i);
		}
		else if(buf[i] == 'e' && buf[i+1]=='p' && buf[i+2]=='s')
		{
			//printf("er\n");
			status = 0;
			var[l++] = 'e';
			var[l++] = 'p';
			var[l++] = 's';
			i = i+3;
			if(l>=3)
			{
				char *lhs = (char*)malloc((l+1)*sizeof(char));
				lhs[l] = '\0';
				int j=0;
				for(j=0;j<l;j++)
				{
					lhs[j] = var[j];
				}
				int x = searchhashtable(G->searchtable,lhs);
				if(x==-1)
				{
					x = G->terminals->size;
					addinhashtable(G->searchtable,lhs,x);
					addinterminals_st(G,lhs);
				}
				else
				{
					//printf("%d",x);
					//printf("x\n");
				}
				addinrules_st(G,x,status,ruleno);
			}
		}
		else
		{
			i++;
		}
	}
	return i;
}


void addtoGrammar(Grammar *G,char* buf)
{
	int i=0;
	int index = 0;
	char rhs[100];
	char lhs[100];
	rhs[99] = '\0';
	lhs[99] = '\0';
	rhs[0] = 'x';
	int l=0;
	int r=0;
	int ruleno = G->rules->size;
	
	while(buf[i]!='\n')
	{	
		if(buf[i] == '<')
		{
			if(rhs[r]!='x')
			{
				printf("error in input grammar\n");
				return ;
			}
			rhs[r] = '<';
			r++;
			i++;
			while(buf[i]!='\n' && buf[i]==' ')
			{
				i++;
			}
			if(buf[i]=='\n')
			{
				printf("error in input grammar\n");
				return ;
			}
			while(buf[i]!='>')
			{
				if(buf[i]=='\n')
				{
					printf("error in input grammar\n");
					return ;
				}
				if(buf[i]!=' ')
				{
					rhs[r] = buf[i];
					r++;
				}
				i++;
			}
			if(r==1)
			{
				printf("error in input grammar\n");
					return ;
			}
			else
			{
				rhs[r] ='>';
				r++;
			}
			i++;
		}
		else if(buf[i] =='=')
		{
			if(buf[i+1]=='\n' || buf[i+2]=='\n' || buf[i+3]=='\n' || buf[i+1]!='=' || buf[i+2]!='=' || buf[i+3]!='>')
			{
				printf("error in input grammar\n");
				return ;
			}
			if(r<=2 || rhs[r-1]!='>' || rhs[0] !='<')
			{
				printf("error in input grammar\n");
				return ;
			}
			char *rhs_add = (char*)malloc((r+1)*sizeof(char));
			int j=0;
			for(j=0;j<r;j++)
			{
				rhs_add[j] = rhs[j];
			}
			rhs_add[r] = '\0';
			i = i+4;
			int x = searchhashtable(G->searchtable,rhs_add);
			if(x ==-1)
			{
				x = G->nonterminals->size;
				addinhashtable(G->searchtable,rhs_add,x);
				addinnonterminals_st(G,rhs_add);
			}
			else
			{
				//printf("x\n");
			}
			addrulenoinnon_terminals_st(G,ruleno,x);
			addinrules_st(G,x,1,ruleno);
			while(buf[i] !='\n')
			{
				//printf("d\n");
				i = handleremaining(G,buf,i,ruleno);
				if(buf[i]=='|')
				{
					ruleno = G->rules->size;
					addrulenoinnon_terminals_st(G,ruleno,x);
					addinrules_st(G,x,1,ruleno);
					i++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	
}

Grammar* getgrammar(char* str)
{
	
	FILE *fp = fopen(str,"r");
	char *buf;
	Grammar *G = createGrammar();
	size_t len =0;
	if(fp==NULL)
	{
		printf("error in file open/read , this error is in first and follow\n");
		return NULL;
	}
	while(!feof(fp))
	{
		//printf("c\n");
		int x = getline(&buf,&len, fp);
		if(x>0)
		{
			addtoGrammar(G,buf);
		}
		else
		{
			break;
		}
	}
	char eps[4];
	eps[0] = 'e';
	eps[1] = 'p';
	eps[2] = 's';
	eps[3] = '\0';
	G->eps = searchhashtable(G->searchtable,eps);
	
	char* dollar=(char*)malloc(5*sizeof(char));
	dollar[0] = 'd';
	dollar[1] = 'o';
	dollar[2] = 'l';
	dollar[3] = 'r';
	dollar[4] = '\0';
	
	int x = G->terminals->size;
	addinhashtable(G->searchtable,dollar,x);
	addinterminals_st(G,dollar);
	
	fclose(fp);
	return G;
}


FirstFollow* getfirstfollow(Grammar *G)
{
	FirstFollow *F = (FirstFollow*)malloc(sizeof(FirstFollow));
	
	F->first = (ffl*)malloc(sizeof(ffl));
	F->first->size = G->nonterminals->size;
	F->first->arr = (linkedlist4**)malloc(F->first->size*sizeof(linkedlist4*));
	int i=0;
	for(i=0;i<F->first->size;i++)
	{
		F->first->arr[i] = (linkedlist4*)malloc(sizeof(linkedlist4));
		F->first->arr[i]->size = 0;
		F->first->arr[i]->root = NULL;
	}
	for(i=0;i<F->first->size;i++)
	{
		if(F->first->arr[i]->root == NULL)
		{
			//printf(" %d ",i);
			calculateFirst(F,G,i);
		}
	}
	//printFirst(F,G);
	//printf("\n");
	F->follow = (ffl*)malloc(sizeof(ffl));
	F->follow->size = G->nonterminals->size;
	F->follow->arr = (linkedlist4**)malloc(F->follow->size*sizeof(linkedlist4*));
	for(i=0;i<F->follow->size;i++)
	{
		F->follow->arr[i] = (linkedlist4*)malloc(sizeof(linkedlist4));
		F->follow->arr[i]->size = 0;
		F->follow->arr[i]->root = NULL;
	}
	linkedlist4 *ls = F->follow->arr[G->start];
	addinlinkedlist4(ls,(G->terminals->size)-1);
	calculateFollow(F,G);
	//printFollow(F,G);
	return F;
}

void addinlinkedlist4(linkedlist4 *ls,int index)
{
	if(ls==NULL)
	{
		return;
	}
	int i=0;
	if(ls->root==NULL)
	{
		node4 *new1 = (node4*)malloc(sizeof(node4));
		new1->index = index;
		new1->next = NULL;
		ls->root = new1;
		ls->size = 1;
		return;
	}
	node4 *temp = ls->root;
	for( i=0; i < ls->size-1 ; i++ )
	{
		if(temp->index == index)
		{
			return ;
		}
		temp = temp->next;
	}
	if(temp->index !=index)
	{
		node4 *new1 = (node4*)malloc(sizeof(node4));
		new1->index = index;
		new1->next = NULL;
		temp->next = new1;
		ls->size += 1;
	}
	return;
}


void calculateFirst(FirstFollow *F,Grammar *G,int index)
{
	linkedlist3 *rule_nos = G->nonterminals->arr[index]->rule_nos;
	if(rule_nos==NULL)
	{
		return;
	}
	int nr = rule_nos->size;
	node3* temp3 = rule_nos->root;
	int i=0;
	int k=0;
	for(i=0;i<nr;i++)
	{
		int ruleno = temp3->ruleno;
		linkedlist *rule = G->rules->arr[ruleno];
		int rsize  = rule->size;
		node* temp2 = rule->root->next;
		int check = 0;
		while(check!=1)
		{
			check = 1;
			if(temp2==NULL)
			{
				check=1;
			}
			else if(temp2->status==1)
			{
				if(F->first->arr[temp2->val]->root == NULL)
				{
					//printf(" c%s \n",G->nonterminals->arr[temp2->val]->str);
					calculateFirst(F,G,temp2->val);
				}
				linkedlist4 *firstls =  F->first->arr[temp2->val];
				int firstsize = firstls->size;
				node4 *temp4  = firstls->root;
				for(k=0;k<firstsize;k++)
				{
					//printf("c");
					if(temp4->index == G->eps)
					{
						check = 0;
						if(temp2->next==NULL)
						{
							addinlinkedlist4(F->first->arr[index],temp4->index);
						}
					}
					else
					{
						addinlinkedlist4(F->first->arr[index],temp4->index);
					}
					
					temp4 = temp4->next;
				}
			}
			else if(temp2->status ==0)
			{
				addinlinkedlist4(F->first->arr[index],temp2->val);
			}
			else
			{
				printf("error \n");
			}
			temp2 = temp2->next;
			if(temp2==NULL)
			{
				check=1;
			}
		}
		temp3 = temp3->next;
	}

}


void calculateFollow(FirstFollow *F,Grammar *G)
{
	int change = 1;
	while(change == 1)
	{
		change = 0;
		int size = G->rules->size;
		int i=0;
		int k=0;
		for(i=0;i<size;i++)
		{
			
			int m = G->rules->arr[i]->root->val;
			node* temp1 = G->rules->arr[i]->root->next;
			while(temp1!=NULL)
			{
	 			int j=0;
				if(temp1->status ==1)
				{
					linkedlist4 *toadd = F->follow->arr[temp1->val];
					int flsize = toadd->size;
					node* temp2 = temp1->next;
					int check=1;
					while(temp2!=NULL && check==1)
					{
						check = 0;
						if(temp2->status == 1)
						{
							linkedlist4 *ls = F->first->arr[temp2->val];
							node4 *temp3 = ls->root;
							
							for(k=0;k<ls->size;k++)
							{
								if(temp3->index == G->eps)
								{
									check = 1;
								}
								else
								{
									addinlinkedlist4(toadd,temp3->index);
								}
								temp3 = temp3->next;
							}
						}
						else if(temp2->status == 0)
						{
							if(temp2->val == G->eps)
							{
							}
							else
							{
								addinlinkedlist4(toadd,temp2->val);
							}
						}
						else
						{
							printf("error \n");
						}
						if(check==1)
						{
							temp2 = temp2->next;
						}
						
					}
					if(temp2==NULL)
					{
						linkedlist4 *ls = F->follow->arr[m];
						node4 *temp3 = ls->root;
						for(k=0;k<ls->size;k++)
						{
							addinlinkedlist4(toadd,temp3->index);
							temp3 = temp3->next;
						}
					}
					if(toadd->size > flsize)
					{
						change = 1;
					}
				}
				temp1 = temp1->next;
			}
		}
	}
}

void freeFirstFollow(FirstFollow *F)
{
	int i=0,j=0;
	for(int i=0;i<F->first->size;i++)
	{
		node4* temp1 = F->first->arr[i]->root;
		node4* temp2 = temp1;
		for(j=0;j<F->first->arr[i]->size;j++)
		{
			temp2 = temp1;
			temp1 = temp1->next;
			temp2->next = NULL;
			free(temp2);
		}
		F->first->arr[i]->root =NULL;
		free(F->first->arr[i]);
	}
	F->first->arr = NULL;
	free(F->first);
	for(int i=0;i<F->follow->size;i++)
	{
		node4* temp1 = F->follow->arr[i]->root;
		node4* temp2 = temp1;
		for(j=0;j<F->follow->arr[i]->size;j++)
		{
			temp2 = temp1;
			temp1 = temp1->next;
			temp2->next = NULL;
			free(temp2);
		}
		F->follow->arr[i]->root =NULL;
		free(F->follow->arr[i]);
	}
	F->follow->arr = NULL;
	free(F->follow);
	free(F);

}

void freeGrammar(Grammar *G)
{
	int i=0,j=0;
	for(i=0;i<G->nonterminals->size;i++)
	{
		single_non_terminal_st *temp = G->nonterminals->arr[i];
		node3 *temp2 = temp->rule_nos->root;
		node3 *temp3 = temp2;
		for(j=0;j<temp->rule_nos->size;j++)
		{
			temp3 = temp2;
			temp2 = temp2->next;
			temp3->next = NULL;
			free(temp3);
		}
		temp->rule_nos->root = NULL;
		free(temp->rule_nos);
		free(temp->str);
		temp->str = NULL;
		temp->rule_nos  =NULL;
		free(temp);
	}
	free(G->nonterminals->arr);
	free(G->nonterminals);
	free(G->terminals->arr);
	free(G->terminals);
	for(i=0;i<G->rules->size;i++)
	{
		linkedlist *temp = G->rules->arr[i];
		node *temp2 = temp->root;
		node *temp3 = temp2;
		for(j=0;j<temp->size;j++)
		{
			temp3 = temp2;
			temp2 = temp2->next;
			temp3->next = NULL;
			free(temp3);
		}
		temp->root = NULL;
		free(temp);
	}
	free(G->rules->arr);
	free(G->rules);
	
	for(i=0;i<G->searchtable->size;i++)
	{
		linkedlist2 *temp = G->searchtable->arr[i];
		node2 *temp2 = temp->root;
		node2 *temp3 = temp2;
		for(j=0;j<temp->size;j++)
		{
			temp3 = temp2;
			temp2 = temp2->next;
			temp3->str = NULL;
			temp3->next = NULL;
			free(temp3);
		}
		temp->root = NULL;
		free(temp);
	}
	free(G->searchtable->arr);
	free(G->searchtable);
	
	free(G);
}

/* STACK FUNCTIONS */
int istopdollar(parser_stack* stack, Grammar* G){

	if(stack == NULL){
		printf("Stack is empty in istopdollar().\n");
	}
	else{
		if(stack->head->id == G->terminals->size - 1){
			return 1;
		}
		else{
			return 0;
		}
	}

}

int isempty(parser_stack* stack){

	if(stack->size == 0){
		return 1;
	}
	else{
		return 0;
	}

}

stack_node* top(parser_stack* stack){

	if(stack == NULL){
		printf("Stack Pointer is NULL. Cannot execute top function.\n");
		return NULL;
	}
	else{
		return stack->head;
	}

}

void push(parser_stack* stack,int id, int status){

	stack_node* newnode = (stack_node*)malloc(sizeof(stack_node));
	newnode->id = id;
	newnode->status = status;

	if(stack == NULL){
		printf("Stack Pointer is NULL. Cannot add a new node\n");
	}
	else{

		if(stack->size == 0){
			newnode->next = NULL;
			stack->head = newnode;
			stack->size += 1;
		}
		else{
			newnode->next = stack->head;
			stack->head = newnode;
			stack->size += 1;
		}
	}

	return;
}

void push_production(parser_stack* pstack,linkedlist* rule,Grammar* G){

	node* root = rule->root;
	root = root->next;

	int token_id;
	int status;

	// check of the rule rhs is only eps
	if(rule->size == 2){

		if(root->val == G->eps){
			return ;
		}

	}

	// Make a temporary array of nodes
	node* alex[rule->size-1];

	int i;
	for(i = 1; i < rule->size; i++){

		alex[i-1] = root;


		root = root->next;
	}
	// printf("\n");

	// Copy all the nodes of the rule into the array
	int k;
	for(k = rule->size - 2; k >= 0; k--){

		token_id = alex[k]->val;
		status = alex[k]->status;
		

		push(pstack,token_id,status);
	}

	//printf("\n");

}

void pop(parser_stack* stack){

	if(stack == NULL){
		printf("Stack Pointer is NULL. Cannot delete a node\n");
	}
	else{

		if(stack->size == 0){
			printf("Stack is Empty. Cannot delete a node\n");		
		}
		else if(stack->size == 1){
			stack_node* temp = stack->head;
			stack->head = NULL;
			stack->size -= 1;

		
			free(temp);
		}
		else{
			stack_node* temp = stack->head;
			stack->head = stack->head->next;
			stack->size -= 1;

			free(temp);
		}
	}

}

/* PARSE TREE FUNCTIONS*/
parser_ptnode* parent(parser_ptnode* curr){
	
	if(curr == NULL){
		printf("Node ptr is NULL. Hence cannot find parent.\n");
	}
	else{
		return curr->parent;
	}
}

parser_ptnode* right(parser_ptnode* curr){

	if(curr == NULL){
		printf("Node ptr is NULL. Hence cannot find right sibling.\n");
	}
	else{
		return curr->sibling;
	}
}

parser_ptnode* child(parser_ptnode* curr){
	if(curr == NULL){
		printf("Node ptr is NULL. Hence cannot find the child.\n");
	}
	else{
		return curr->children_first;
	}	
}

parser_ptnode* next_node(parser_ptnode* curr){

	if(curr == NULL){
		printf("Node ptr is NULL. Hence cannot find the next node.\n");
		return NULL;
	}
	else{

		parser_ptnode* temp = curr;

		while( temp != NULL && right(temp) == NULL){
			temp = parent(temp);
		}

		if(temp == NULL){
			return temp;
		}
		else{
			return right(temp);
		}
		
	}
}

void add_child(parser_ptnode* par, parser_ptnode* child){

	if(par == NULL){
		printf("Parent Pointer is NULL in add_child function.\n");
	}
	else if(child == NULL){
		printf("Child Pointer is NULL in add_child function.\n");
	}
	else{

		if(par->children_last == NULL){

			// 1st child
			par->children_first = child;
			par->children_last = child;
			child->parent = par;
		}
		else{

			// nth child
			par->children_last->sibling = child;
			par->children_last = child;
			child->parent = par;
		}
	}
}

/*PARSE Table FUNCTIONS*/
table* createParseTable(FirstFollow *F,Grammar *G)
{
	table *t = (table*)malloc(sizeof(table));
	t->row=G->nonterminals->size;
	t->column=G->terminals->size;
	t->arr=(ruleused**)malloc(sizeof(ruleused*)*(t->row));
	int i,j,nt,flag=0;
	node *temp,*temp1;
	node4 *temp2;
	for(i=0;i<t->row;i++)
		t->arr[i]=(ruleused*)malloc(sizeof(ruleused)*(t->column));
	for(i=0;i<t->row;i++)
	{
		for(j=0;j<t->column;j++)
		{
			t->arr[i][j].status=-1;
			t->arr[i][j].l=NULL;
		}
	}
	for(i=0;i<G->rules->size;i++)
	{
		temp=G->rules->arr[i]->root;
		nt=temp->val;
		temp1=temp->next;
		while(temp1!=NULL)
		{
			if(temp1->status==0)
			{
				t->arr[nt][temp1->val].status=0;
				t->arr[nt][temp1->val].l=G->rules->arr[i];
				if(temp1->val==G->eps)
				{
					flag=1;
				}
			}
			else
			{
				temp2=F->first->arr[temp1->val]->root;
				while(temp2!=NULL)
				{
					if(temp2->index==G->eps)
					{
						flag=1;
					}
					else
					{
						t->arr[nt][temp2->index].status=0;
						t->arr[nt][temp2->index].l=G->rules->arr[i];
					}
					temp2=temp2->next;
				}
			}
			if(flag==1)	
			{
				temp1=temp1->next;
				flag=0;
			}
			else
				break;
		}
		if(temp1==NULL)
		{
			temp2=F->follow->arr[temp->val]->root;
			while(temp2!=NULL)
			{
				t->arr[nt][temp2->index].status=0;
				t->arr[nt][temp2->index].l=G->rules->arr[i];
				temp2=temp2->next;
			}
		}
	}
	for(i=0;i<t->row;i++)
	{
		temp2=F->follow->arr[i]->root;
		while(temp2!=NULL)
		{
			if(t->arr[i][temp2->index].status==-1)
			{
				t->arr[i][temp2->index].status=1;	
			}
			temp2=temp2->next;
		}
	}
	return t;
}

linkedlist* get_rule(table* t,int non_terminal,int input,int *error,int *syn)
{
	if(t->arr[non_terminal][input].status==0)
		return t->arr[non_terminal][input].l;
	else
	{
		if(t->arr[non_terminal][input].status==1)
			*syn=-1;
		else
			*error=-1;
		return NULL;
	}
}

//**************************************


/*PARSER FUNCTIONS*/
parser_ptnode* add_production(parser_ptnode* curr, linkedlist* rule, Grammar* G, int lineNo){

	if(curr == NULL || rule == NULL || G == NULL){
		
		if(curr == NULL){
			printf("The curr node ptr is NULL in add_production().\n");
		}
		else if(rule == NULL){
			printf("The rule ptr is NULL in add_production().\n");
		}
		else if(G == NULL){
			printf("The grammar ptr is NULL in add_production().\n");
		}
		
		return NULL;
	}

	node* root = rule->root;
	root = root->next;

	int token_id;
	int status;

	int i;
	for(i = 1; i < rule->size; i++){
		
		// Adding the RHS of the production to the parse tree
		token_id = root->val;
		status = root->status;
		
		if(status == 0){

			// Adding a terminal node as a child
			parser_ptnode* newchild = (parser_ptnode*)malloc(sizeof(parser_ptnode));
			strcpy(newchild->parent_symbol,curr->node_symbol);
			strcpy(newchild->node_symbol,G->terminals->arr[token_id]);

			newchild->token = (tokenInfo*)malloc(sizeof(tokenInfo));
			newchild->token->lineNo = lineNo;
			newchild->token->token_id = token_id;
			newchild->token->status = status;
			newchild->token->lexeme_value = NULL;

			newchild->isleafnode = 1;
			newchild->parent = curr;
			newchild->sibling = NULL;
			newchild->children_first = NULL;
			newchild->children_last = NULL;
			newchild->addr = NULL;
			newchild->inh_addr = NULL;

			add_child(curr,newchild);
		}
		else{

			// Adding a non-terminal node as a child
			parser_ptnode* newchild = (parser_ptnode*)malloc(sizeof(parser_ptnode));
			strcpy(newchild->parent_symbol,curr->node_symbol);
			strcpy(newchild->node_symbol,G->nonterminals->arr[token_id]->str);

			newchild->token = (tokenInfo*)malloc(sizeof(tokenInfo));
			newchild->token->lineNo = lineNo;
			newchild->token->token_id = token_id;
			newchild->token->status = status;
			newchild->token->lexeme_value = NULL;

			newchild->isleafnode = 0;
			newchild->parent = curr;
			newchild->sibling = NULL;
			newchild->children_first = NULL;
			newchild->children_last = NULL;
			newchild->addr = NULL;
			newchild->inh_addr = NULL;

			add_child(curr,newchild);
		}

		root = root->next;
	}

	parser_ptnode* nodeptr;

	if(token_id == G->eps && status == 0){
		// if it was epsilon then next node
		nodeptr = next_node(curr);
	}
	// else then child_node
	else{
		// move downwards
		nodeptr = child(curr);
	}

	return nodeptr;
}

int checkifnull(FILE* fileptr){
	if(checkbuffer == 0){
		getStream(fileptr,buffer0);
	}
}

void fprint_40_spaces(int len){

	int i = 0;
	for(i; i < 15-len; i++){
		printf(" ");
	}

}

int check_length(int len){

	int divide = 10;
	int count = 1;

	while(len/divide != 0){
		divide *= 10;
		count += 1;
	}

	return count;
}

//*****************************


void getptreenodes(parser_pt* curr, Grammar* G,int* counter){
	getptreenodeshelper(curr->root,G,counter);
}

void getptreenodeshelper(parser_ptnode* curr, Grammar* G,int* counter){

	if(curr == NULL){
		return;
	}
	/*Children first*/
	getptreenodeshelper(curr->children_first,G,counter);
	(*counter)++;
	
	/*Then siblings of the the fist child */
	if(curr->children_first != NULL){

		parser_ptnode* temp = curr->children_first;
		temp = right(temp);

		while(temp != NULL){
			getptreenodeshelper(temp,G,counter);
			temp = right(temp);
		}

	}
}



void print_parse_nodes(parser_ptnode* curr, Grammar* G){

	if(curr == NULL){
		return;
	}
	/*Children first*/
	print_parse_nodes(curr->children_first,G);

	/*Then myself*/
	if(curr->isleafnode == 1){
		if(curr->token->token_id == G->eps){
			printf("---");
			fprint_40_spaces(3);
		}
		else{
			printf("%s",curr->token->lexeme_value);
			fprint_40_spaces(strlen(curr->token->lexeme_value));
		}

		printf("%d", curr->token->lineNo);
		fprint_40_spaces(check_length(curr->token->lineNo) );

		printf("%s", G->terminals->arr[curr->token->token_id]);
		fprint_40_spaces(strlen(G->terminals->arr[curr->token->token_id]) );

		// if number
		if(curr->token->lexeme_value != NULL && curr->token->lexeme_value[0] >= '0' && curr->token->lexeme_value[0] <= '9'){
			printf("%s",curr->token->lexeme_value);
			fprint_40_spaces(strlen(curr->token->lexeme_value));
		}
		// if not number
		else{
			printf("---");
			fprint_40_spaces(3);
		}

		printf("%s",curr->parent_symbol);
		fprint_40_spaces(strlen(curr->parent_symbol));

		printf("yes");
		fprint_40_spaces(3);

		printf("---\n\n");
		
	}
	else{
		printf("---");
		fprint_40_spaces(3);

		printf("---");
		fprint_40_spaces(3);

		printf("---");
		fprint_40_spaces(3);

		printf("---");
		fprint_40_spaces(3);
		
		printf("%s",curr->parent_symbol);
		fprint_40_spaces(strlen(curr->parent_symbol));

		printf("no");
		fprint_40_spaces(2);

		printf("%s\n\n",curr->node_symbol);
	}

	/*Then siblings of the the fist child */
	if(curr->children_first != NULL){

		parser_ptnode* temp = curr->children_first;
		temp = right(temp);

		while(temp != NULL){
			print_parse_nodes(temp,G);
			temp = right(temp);
		}

	}
}

void printParseTree(parser_pt* ptree, Grammar* G){

	print_parse_nodes(ptree->root,G);


}


//****************************

int check_eps(Grammar* G,FirstFollow *F,int index){

	int i=0;
	linkedlist4 *ls = F->first->arr[index];
	node4* temp = ls->root;
	for(i=0;i<ls->size;i++)
	{
		if(temp->index == G->eps)
		{
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}


//****************************


void printfirst(Grammar* G, table* T,tokenInfo* token,parser_stack* pstack){

	// printf("\n\n\n");
	// printf("Expected ");
	printf("set { ");
	int z;
	for(z=0;z<T->column;z++)
	{
		if(T->arr[top(pstack)->id][z].status==0)
			printf("%s, ",G->terminals->arr[z]);
	}
	printf("}");

	printf(" which is first_set of %s", G->nonterminals->arr[top(pstack)->id]->str);	
	printf("\n");
	// printf("but received %s.\n",token->lexeme_value);
	// printf("\n\n\n");
}


parser_pt* parseInputSourceCode(char *testcaseFile, table* T, Grammar* G,FirstFollow *F) {

	// printf("AL\n");

	if(testcaseFile == NULL || T == NULL || G == NULL){

		if(testcaseFile == NULL){
			printf("testcaseFile ptr is NULL in parseInputSourceCode().\n");
		}
		else if(T == NULL){
			printf("T ptr is NULL in parseInputSourceCode().\n");
		}
		else if(G == NULL){
			printf("G ptr is NULL in parseInputSourceCode().\n");
		}

		return NULL;
	}

	FILE* fileptr = fopen(testcaseFile, "r");

	if(fileptr == NULL){
		printf("Please provide the correct path, file not opened");
	}

	(*currIndex)=0;
	lineNo=1;
	checkbuffer=0;

	buffer0 = (char*)malloc(Bufferlen);
	buffer1 = (char*)malloc(Bufferlen);

	getStream(fileptr,buffer1);
	getStream(fileptr,buffer0);

	int dollarid = (G->terminals->size-1);

	// Create the Parser Stack and populate with start symbol
	parser_stack* pstack = (parser_stack*)malloc(sizeof(parser_stack));
	pstack->size = 0;	
	push(pstack,dollarid,0);
	push(pstack,G->start,1);
	
	//print_stack(pstack,G);
	printf("\n");

	// Create the Parse Tree and populate with start symbol
	parser_pt* ptree = (parser_pt*)malloc(sizeof(parser_pt));
	

	ptree->root = (parser_ptnode*)malloc(sizeof(parser_ptnode));
	strcpy(ptree->root->node_symbol,"<program>");
	strcpy(ptree->root->parent_symbol,"no parent");
	ptree->root->isleafnode = 0;
	
	ptree->root->token = (tokenInfo*)malloc(sizeof(tokenInfo));
	ptree->root->token->lineNo = 1;
	ptree->root->token->token_id = G->start;
	ptree->root->parent = NULL;
	ptree->root->sibling = NULL;
	ptree->root->children_first = NULL;
	ptree->root->children_last = NULL;

	parser_ptnode* nodeptr = ptree->root;


	int error_flag = 0;
	int syn_flag = 0;

	// printf("Before Token Call\n");
	int previous_line_no = 0;
	tokenInfo* token = getNextToken(fileptr,G->searchtable);
	// printf("Token with %s received.\n",token->lexeme_value);
	
	//checkifnull(fileptr);
	int error_in_syntax = 0;

	// printf("AL6\n");
	int flag_disaster = 0;

	while(1) {

		// exit
		if(flag_disaster == 1){
			break;
		}

		// Check if the stack's top is a terminal (not dollar) but the token dollar has been received
		if( token->token_id == dollarid && istopdollar(pstack,G) == 0 && top(pstack)->status == 0){
			printf("Source Code is Over but the stack is not empty\n");
			break;
		}

		// Check if the stack's top is dollar but token value is not dollar
		if(token->token_id != dollarid  && istopdollar(pstack,G) == 1){
			printf("Source Code is still remaining but the stack is empty\n");
			break;
		}

		// Check if the stack's top is dollar and the token value is also dollar
		if(token->token_id == dollarid && istopdollar(pstack,G) == 1){
			break;
		}

		// Code is still remaining and stack is not over

		// If top of the stack is a terminal
		if(top(pstack)->status == 0){

			// same terminal
			if( top(pstack)->id == token->token_id){

				// pop stack
				pop(pstack);

				nodeptr->token = token;
				nodeptr->rule_no = 0;

				// move to the next node - rightwards or upwards
				nodeptr = next_node(nodeptr);

				// get the next token
				previous_line_no = token->lineNo;
				token = getNextToken(fileptr,G->searchtable);
						
			}
			// different terminal
			else{

				error_in_syntax = 1;

				// If Expected token is semi-colon then print different message
				if(searchhashtable(G->searchtable,"TK_SEM") == top(pstack)->id){
					printf("Line %d: Semicolon is Missing\n",previous_line_no);
				}
				else{
					printf("Line %d: The token %s for lexeme \'%s\' does not match with the expected token %s.\n",
					token->lineNo,G->terminals->arr[token->token_id],token->lexeme_value,G->terminals->arr[top(pstack)->id]);
				}

				pop(pstack);

				while( !( (token->token_id == dollarid && istopdollar(pstack,G) == 0 && top(pstack)->status == 0) || (token->token_id != dollarid  && istopdollar(pstack,G) == 1) ) ){

					//printf("z\n");

					// check if the top of the stack still has terminals, pop them if they don't match
					while( istopdollar(pstack,G) == 0 && top(pstack)->status == 0 && top(pstack)->id != token->token_id ){

						pop(pstack);
						nodeptr = next_node(nodeptr);

						// printf("Deleted one more terminal from the stack\n");
					}

					// is the stack's top is dollar
					if( istopdollar(pstack,G) == 1 ){
						// printf("z1\n");
						break;
					}

					// stack has a terminal and it matches
					else if( istopdollar(pstack,G) == 0 && top(pstack)->status == 0 && top(pstack)->id == token->token_id ){
		
						break;
					}

					// if the stack has a non-terminal
					else if( istopdollar(pstack,G) == 0 && top(pstack)->status == 1 ){

						// Get the rule
						int non_term_id;
						int input_id;
						linkedlist* rule;

						while( !( (token->token_id == dollarid && istopdollar(pstack,G) == 0 && top(pstack)->status == 0) || (token->token_id != dollarid  && istopdollar(pstack,G) == 1) ) ){

							// printf("z4\n");

							non_term_id = top(pstack)->id; 
							input_id = token->token_id;

							syn_flag = 0;
							error_flag = 0;
							rule = get_rule(T,non_term_id,input_id,&error_flag,&syn_flag);

							// syn or error possibilites
							if(rule == NULL){

								if(syn_flag == -1){

									// pop the stack
									pop(pstack);

									// update the pointer in parse tree
									nodeptr = next_node(nodeptr);

									//success_flag = 1;
									syn_flag = 0;
									error_flag = 0;
									break;
								}
								else if(error_flag == -1){

									// flags reset
									syn_flag = 0;
									error_flag = 0;

									previous_line_no = token->lineNo;
									token = getNextToken(fileptr,G->searchtable);
									// printf("Token with %s received.\n",token->lexeme_value);
									//checkifnull(fileptr);
								}

								//syn_flag = 0;
								//error_flag = 0;
							}
							else if(rule != NULL){
								// break;
								//success_flag = 1;
								break;
							}

						}

						// printf("z5\n");
						break;
					}
					else{
						// printf("Something is seriously wrong\n");
						//printf("%d %d %d %d", istopdollar(pstack,G), top(pstack)->status,token->token_id, top(pstack)->id);
					}

				}

				/* PANIC MODE */
				
			}

		}

		// If the top of the stack is a non-terminal
		else if(top(pstack)->status == 1){

			// Get the indices to index into the parse table
			int non_term_id = top(pstack)->id;
			int input_id = token->token_id;
			int line_no = token->lineNo;

			// Get the rule
			linkedlist* rule = get_rule(T,non_term_id,input_id,&error_flag,&syn_flag);
			
			if(rule != NULL){

				// save rule number
				nodeptr->rule_no = rule->ruleno;

				// Add the rule to the parse tree and update the node pointer
				nodeptr = add_production(nodeptr,rule,G,line_no);
				
				// Add the RHS to the stack
				pop(pstack);
				push_production(pstack,rule,G);			
			}

			// Panic Mode Start
			else if(rule == NULL){

				// print_stack(pstack,G);
				error_in_syntax = 1;

				if( check_eps(G,F,top(pstack)->id) == 1 ){

					// printf("This terminal derives epsilon\n");
					pop(pstack);

				}
				else{

					// syn or error possibilites
					int one_error_already = 0;

					while( !( (token->token_id == dollarid && istopdollar(pstack,G) == 0 && top(pstack)->status == 0) || (token->token_id != dollarid  && istopdollar(pstack,G) == 1) ) ){

						non_term_id = top(pstack)->id;
						input_id = token->token_id;
						rule = get_rule(T,non_term_id,input_id,&error_flag,&syn_flag);

						// syn or error possibilites
						if(rule == NULL){

							// If the token received was dollar and no rule exists then abort
							if(token->token_id == dollarid ){
								printf("Source Code is Over but the stack is not empty\n");
								flag_disaster = 1;
								break;
							}

							if(syn_flag == -1){

								if(one_error_already == 0){

									one_error_already += 1;

									// The token TK_END for lexeme end does not match with the expected token TK_RETURN
									printf("Line %d: The token %s for lexeme \'%s\' does not match with the expected token ",token->lineNo,G->terminals->arr[token->token_id],token->lexeme_value);
									printfirst(G,T,token,pstack);
								}

								// pop the stack
								// printf("Terminal %s is in syn set of non-terminal %s\n",token->lexeme_value, G->nonterminals->arr[top(pstack)->id]->str);
								pop(pstack);

								// update the pointer in parse tree
								nodeptr = next_node(nodeptr);

								syn_flag = 0;
								error_flag = 0;

								// success
								break;
							}
							else if(error_flag == -1){

								if( one_error_already == 0 ){

									one_error_already += 1;

									// Line 31: The token of type TK_NUM for lexeme 45 does not match with the expected token of type <singleOrRecId>
									printf("Line %d: The token of type %s for lexeme \'%s\' does not match with the expected token of type %s\n",token->lineNo,G->terminals->arr[token->token_id],token->lexeme_value,
										G->nonterminals->arr[top(pstack)->id]->str);
								}

								//printf("Error, The terminal %s with token_id %d on line %d cannot be generated from the top of the stack.\n", token->lexeme_value,token->token_id,token->lineNo);

								syn_flag = 0;
								error_flag = 0;

								previous_line_no = token->lineNo;
								token = getNextToken(fileptr,G->searchtable);
								// printf("Token with %s received.\n",token->lexeme_value);
								//checkifnull(fileptr);
							}

							//syn_flag = 0;
							//error_flag = 0;
						}
						else if(rule != NULL){
							
							/*
							// Add the rule to the parse tree and update the node pointer
							nodeptr = add_production(nodeptr,rule,G,line_no); */

							// success
							break;
						}

					}

				}

			}
			// Panic Mode End
		}

	}

	if(error_in_syntax == 1){
		return NULL;
	}

	return ptree;
}
