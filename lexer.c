// Group 15
// Alex Mathai - 2016A7PS0339P
// Sarthak Agarwal - 2016A7PS0135P
// Sanchit Shrivastava - 2016A7PS0072P
// Aman Sanghi - 2016A7PS0024P

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lexer.h"
#include "parserDef.h"
//Hash Functions
hashtable_st* createHastable(int size)
{
	hashtable_st* Ht = (hashtable_st*)malloc(sizeof(hashtable_st));
	Ht->size = size;
	int i=0;
	Ht->arr = (linkedlist2**)malloc(size*sizeof(linkedlist2*));
	for(i=0;i<size;i++)
	{
		Ht->arr[i] = NULL;
	}
	return Ht;
}

int hashfunction(int mod,char* str)
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

void addinlinkedlist2(linkedlist2* ls,char* str,int index)
{
	node2* new1 = (node2*)malloc(sizeof(node2));
	new1->str = str;
	new1->index = index;
	new1->next = NULL;
	ls->size = ls->size+1;
	if(ls->root==NULL)
	{
		ls->root = new1;
		return ;
	}
	node2* temp = ls->root;
	ls->root = new1;
	new1->next = temp;
}


void addinhashtable(hashtable_st *ht,char* str,int index)
{
	int val = hashfunction(ht->size,str);
	if(ht->arr[val]==NULL)
	{
		ht->arr[val]=(linkedlist2*)malloc(sizeof(linkedlist2));
		(ht->arr[val])->size = 0;
		(ht->arr[val])->root = NULL;
	}
	addinlinkedlist2(ht->arr[val],str,index);
}

int searchhashtable(hashtable_st *ht,char* str)
{
	int val = hashfunction(ht->size,str);
	linkedlist2* ls = ht->arr[val];
	if(ls==NULL)
	{
		return -1;
	}
	int x = ls->size;
	node2* temp = ls->root;
	int i=0;
	for(i=0;i<x;i++)
	{
		if(strCMP(str,temp->str)==0)
		{
			return temp->index;
		}
		temp=temp->next;
	}
	return -1;
}

int strCMP(char* str1,char* str2)
{
	int len1 = 0;
	int len2=0;
	while(str1[len1]!='\0')
	{
		len1++;
	}
	while(str2[len2]!='\0')
	{
		len2++;
	}
	if(len1!=len2)
	{
		return -1;
	}
	int i=0;
	while(str1[i]!='\0')
	{
		if(str1[i]!=str2[i])
		{
			return -1;
		}
		i++;
	}
	return 0;

}


//Lexer Functions

void fill_symbol_table(hashtable_st* searchtable)
{	
	int x = searchhashtable(searchtable,"TK_WITH");
	addinhashtable(symbol_table,"with",x);
	x = searchhashtable(searchtable,"TK_PARAMETERS");
	addinhashtable(symbol_table,"parameters",x);
	x = searchhashtable(searchtable,"TK_END");
	addinhashtable(symbol_table,"end",x);
	x = searchhashtable(searchtable,"TK_WHILE");
	addinhashtable(symbol_table,"while",x);
	x = searchhashtable(searchtable,"TK_MAIN");
	addinhashtable(symbol_table,"_main",x);
	x = searchhashtable(searchtable,"TK_GLOBAL");
	addinhashtable(symbol_table,"global",x);
	x = searchhashtable(searchtable,"TK_PARAMETER");
	addinhashtable(symbol_table,"parameter",x);
	x = searchhashtable(searchtable,"TK_LIST");
	addinhashtable(symbol_table,"list",x);
	x = searchhashtable(searchtable,"TK_INPUT");
	addinhashtable(symbol_table,"input",x);
	x = searchhashtable(searchtable,"TK_OUTPUT");
	addinhashtable(symbol_table,"output",x);
	x = searchhashtable(searchtable,"TK_INT");
	addinhashtable(symbol_table,"int",x);
	x = searchhashtable(searchtable,"TK_REAL");
	addinhashtable(symbol_table,"real",x);
	x = searchhashtable(searchtable,"TK_ENDWHILE");
	addinhashtable(symbol_table,"endwhile",x);
	x = searchhashtable(searchtable,"TK_IF");
	addinhashtable(symbol_table,"if",x);
	x = searchhashtable(searchtable,"TK_THEN");
	addinhashtable(symbol_table,"then",x);
	x = searchhashtable(searchtable,"TK_ENDIF");
	addinhashtable(symbol_table,"endif",x);
	x = searchhashtable(searchtable,"TK_READ");
	addinhashtable(symbol_table,"read",x);
	x = searchhashtable(searchtable,"TK_WRITE");
	addinhashtable(symbol_table,"write",x);
	x = searchhashtable(searchtable,"TK_RETURN");
	addinhashtable(symbol_table,"return",x);
	x = searchhashtable(searchtable,"TK_CALL");
	addinhashtable(symbol_table,"call",x);
	x = searchhashtable(searchtable,"TK_RECORD");
	addinhashtable(symbol_table,"record",x);
	x = searchhashtable(searchtable,"TK_ENDRECORD");
	addinhashtable(symbol_table,"endrecord",x);
	x = searchhashtable(searchtable,"TK_ELSE");
	addinhashtable(symbol_table,"else",x);
	x = searchhashtable(searchtable,"TK_TYPE");
	addinhashtable(symbol_table,"type",x);
	return;
}


FILE* getStream(FILE* fp,char* buffer)
{
	if(feof(fp))
	{
		fclose(fp);
 		return NULL;
 	}
	int x;
	if((x = fread(buffer, sizeof(char), Bufferlen, fp))>0)
	{
		if(x!=Bufferlen)
		{
			buffer[x]='\0';
		}
 		return fp;
 	}
	else
	{
 		fclose(fp);
 		return NULL;
 	}
}


tokenInfo* getNextToken(FILE* fp, hashtable_st* search_table)
{	
	int state=0;
	tokenInfo* newtoken=(tokenInfo*)malloc(sizeof(newtoken));
	newtoken->token_id=-1;
	newtoken->status=0;
	int error=1;
	char read_input[50];
	int count=0;
	char current_input;
	
	
	while(1)
	{			
		if(*currIndex >= Bufferlen )
		{
			if(checkbuffer==1)
			{
				getStream(fp,buffer0);
			}			
			char* temp=buffer1;
			buffer1=buffer0;
			checkbuffer=1;
			buffer0=temp;
			*currIndex=0;
		}
		current_input=buffer1[*currIndex];
		if(state!=100)
		{
			(*currIndex)++;
			read_input[count]=current_input;
			count++;
		}
		
		switch(state)
		{
			case 0:
				switch(current_input)
				{
					case '<':
						state=1;
						break;
						
					case '%':
						state=4;
						if(showcomment==1)
						{	
							char ch='%';
							printf("Line %d: %c",lineNo,ch);
						}
						break;
						
					case '#':
                        state=5;
                        break;
                        
                    case 'a':
                    case 'e':
                    case 'f':
                    case 'g':
                    case 'h':
                    case 'i':
                    case 'j':
                    case 'k':
                    case 'l':
                    case 'm':
                    case 'n':
                    case 'o':
                    case 'p':
                    case 'q':
                    case 'r':
                    case 's':
                    case 't':
                    case 'u':
                    case 'v':
                    case 'w':
                    case 'x':
                    case 'y':
                    case 'z':
                        state = 7;
                        break;
                        
                    case 'b':
                    case 'c':
                    case 'd':
                        state = 8;
                        break;
					
					case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        state = 11;
                        break;
                        
                    case '[':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_SQL");
           				break;
                    
                    case ']':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_SQR");
           				break;
           			
           			case ',':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_COMMA");
           				break;
           					
                    case ';':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_SEM");
           				break;
           				
                    case ':':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_COLON");
           				break;
           				
                    case '.':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_DOT");
           				break;
           				
                    case '(':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_OP");
           				break;
           				
                    case ')':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_CL");
           				break;
           				
                    case '+':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_PLUS");
           				break;
           				
                    case '-':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_MINUS");
           				break;
           				
                    case '*':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_MUL");
           				break;
           				
                    case '/':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_DIV");
           				break;
           				
                    case '&':
						state=14;
           				break;
           				
                    case '@':
						state=16;
           				break;
           				
                    case '=':
						state=18;
           				break;
           				
                    case '>':
						state=19;
           				break;
           				
                    case '!':
						state=20;
           				break;
           				
                    case '_':
						state=21;
           				break;
           			
           			case '~':
						state=24;
           				newtoken->token_id=searchhashtable(search_table,"TK_NOT");
           				break;
           			
           			case ' ':
           			case '\t':
                    case '\r':
                    case '\f':
                    case '\v':
                    	count--;
           				break;
           				
           			case '\n':
           				count--;
                        lineNo++;	
						break;
					
					case '\0':
						count--;
						read_input[count]='$';
						state=100;
						count++;
						newtoken->token_id=searchhashtable(search_table,"dolr");
						break;
					
					default:
						//unknown symbol error
						state=100;
						error=-2;
						break;
				}	
			break;
			case 1:
				if(current_input == '=')
				{
					state=24;
       				newtoken->token_id=searchhashtable(search_table,"TK_LE");
       				break;
           		}
           		else if(current_input == '-')
           		{		
					state=2;
					break;
				}
				else
				{
					state=100;
					(*currIndex)--;
					count--;
					newtoken->token_id=searchhashtable(search_table,"TK_LT");
					break;						
				}
			break;
			
			case 2:
				if(current_input == '-')
           		{		
					state=3;
					break;
				}
				else
				{
					//unknown pattern error
					state=100;
					error=-1;
					(*currIndex)--;
					count--;
					break;
				}	
			break;
			
			case 3:
				if(current_input == '-')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_ASSIGNOP");
					break;
				}
				else
				{
					//unknown pattern error
					state=100;
					error=-1;
					(*currIndex)--;
					count--;
					break;
				}
			break;
				
			case 4: //comment too long
				if(current_input == '\n') 
				{
					state = 100;
					count--;
					lineNo++;
					newtoken->token_id=-10;
					break;
				}
				else
				{
					if(showcomment==1)
					{
						printf("%c",current_input);
					}
					count--;
					break;
				}
			break;
			
			case 5:
				if(current_input>='a' && current_input<='z') 
				{
                    state = 6;
                    break;
                }
                else
                {
                	//unknown pattern error
					state=100;
					error=-1;
					(*currIndex)--;
					count--;
					break;
                }
			break;
			
			case 6:
				if(current_input>='a' && current_input<='z') 
				{
					if(count>20)
					{
						error=-20;
						count--;
					}
                    break;
                }
                else
                {       
                	state=100;
                	(*currIndex)--;
                	count--;
					newtoken->token_id=searchhashtable(search_table,"TK_RECORDID");
					break;
                }
			break;
			
			case 7:
                if(current_input>='a' && current_input<='z') 
				{
                    break;
                }
                else
                {       
                	state=100;
                	(*currIndex)--;
                	count--;
					newtoken->token_id=searchhashtable(search_table,"TK_FIELDID");
					break;
                }
			break;
			
			case 8:
                if(current_input>='a' && current_input<='z') 
				{
					state = 7;
                    break;
                }
                else if(current_input>='2' && current_input<='7')
                {   
                    state = 9;
                    break;
                }
            break;
            
            case 9:
                if(current_input>='b' && current_input<='d') 
				{
					if(count>20)
					{
						error=-17;
						count--;
					}
                    break;
                }
                else if(current_input>='2' && current_input<='7')
                {   
                    state = 10;
                    break;
                }
                else
                {
                    state=100;
                	(*currIndex)--;
                	count--;
					newtoken->token_id=searchhashtable(search_table,"TK_ID");
					break;
                }
            break;

            case 10:
                if(current_input>='2' && current_input<='7')
                {   
                    if(count>20)
					{
						error=-17;
						count--;
					}
                    break;
                }
                else
                {
                    state=100;
                	(*currIndex)--;
                	count--;
					newtoken->token_id=searchhashtable(search_table,"TK_ID");
					break;
                }
            break;

            case 11:
                if(current_input>='0' && current_input<='9') 
                {
                    if(count>20)
					{
						error=-21;
						count--;
					}
                    break;
                }
                else if(current_input=='.')
                {
                        state = 12;
                        break;
                }
                else
                {
                	state=100;
                	(*currIndex)--;
                	count--;
					newtoken->token_id=searchhashtable(search_table,"TK_NUM");
					break;
                }
            break;

            case 12:
                if(current_input>='0' && current_input<='9') 
                {
                    state = 13;
                    break;
                }
              	else
              	{	
              		state=100;
              		if(error==-21)
              		{
              			error=-50;
              		}
              		else
              		{
						error=-1;
					}
					(*currIndex)--;
					count--;
					break;
                }
            break;

            case 13:
                if(current_input>='0' && current_input<='9') 
                {
                	state=24;
                	if(error==-21)
                	{
                		error=-22;
                	}
                    newtoken->token_id=searchhashtable(search_table,"TK_RNUM");
					break;
                }
                else
                {	//unknown + too long
                 	state=100;
					(*currIndex)--;
					count--;
					if(error==-21)
              		{
              			error=-50;
              		}
              		else
              		{
						error=-1;
					}
					break;
                }
            break;
            
            case 14:
				if(current_input == '&')
				{
					state=15;
					break;
				}	
				else
				{
					//unknown pattern error	
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;			
				}
			break;
			
			case 15:
				if(current_input == '&')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_AND");
					break;
				}
				else
				{
					//unknown pattern error	
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;			
				}	
			break;
			
			case 16:
				if(current_input == '@')
				{
					state=17;
					break;
				}
				else
				{
					//unknown pattern error
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;				
				}		
			break;
			
			case 17:
				if(current_input == '@')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_OR");
					break;
				}
				else
				{
					//unknown pattern error	
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;			
				}		
			break;
			
			case 18:
				if(current_input == '=')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_EQ");
					break;
				}
				else
				{
					//unknown pattern error	
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;			
				}		
			break;
			
			case 19:
				if(current_input == '=')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_GE");
					break;
				}
				else
				{	
					state=100;
					(*currIndex)--;
					count--;
					newtoken->token_id=searchhashtable(search_table,"TK_GT");
					break;
				}	
			break;
			
			case 20:
				if(current_input == '=')
				{
					state=24;
					newtoken->token_id=searchhashtable(search_table,"TK_NE");
					break;
				}
				else
				{
					//unknown pattern error	
					state=100;
					error=-1;
					(*currIndex)--;
					count--;	
					break;			
				}	
			break;
			
			case 21:
				if((current_input>='a' && current_input<='z') || (current_input>='A' && current_input<='Z'))
				{
					state=22;
					break;
				}
				else
				{
					//unknown pattern error
					state=100;
					error=-1;
					(*currIndex)--;
					count--;
					break;
				}
			break;
						
			case 22:
				if((current_input>='a' && current_input<='z') || (current_input>='A' && current_input<='Z'))
				{
					if(count>30)
					{
						error=-25;
						count--;
					}
					break;
				}
				else if(current_input>='0' && current_input<='9')
				{
					state=23;
					break;
				}
				else
				{
					state=100;
					(*currIndex)--;
					count--;
					newtoken->token_id=searchhashtable(search_table,"TK_FUNID");
					break;
				}	
			break;
			
			case 23:
				if(current_input>='0' && current_input<='9')
				{
					if(count>30)
					{
						error=-25;
						count--;
					}
					break;
				}
				else
				{
					state=100;
					(*currIndex)--;
					count--;
					newtoken->token_id=searchhashtable(search_table,"TK_FUNID");
					break;
				}	
			break;
			
			case 24:
				state=100;
				(*currIndex)--;
				count--;
				break;
				
			case 100:
				read_input[count]='\0';
				newtoken->lineNo=lineNo;
				newtoken->lexeme_value=(char*)malloc((count+2)*sizeof(char));
				int i;
				for(i=0;i<count+1;i++)
				{
					newtoken->lexeme_value[i]=read_input[i];
				}
				int id=searchhashtable(symbol_table,newtoken->lexeme_value);
				if(id!=-1)
				{
					newtoken->token_id=id;
				}
				
				if(newtoken->token_id==-10)
				{
					if(showcomment==1)
					{
						printf(" | TK_COMMENT\n");
					}
					return getNextToken(fp,search_table);
				}
				
				if(error<0)
				{
					if(showerror==1)
					{
						errorhandler(error,newtoken);
					}
					return getNextToken(fp,search_table);
				}
				return newtoken;
			break;			
		}	
	}
}

void errorhandler(int error,tokenInfo* newtoken)
{
	if(error==-1)
	{
		printf("Line %d: Unknown pattern %s\n",lineNo,newtoken->lexeme_value);
	}
	else if(error==-2)
	{
		printf("Line %d: Unknown Symbol %s\n",lineNo,newtoken->lexeme_value);
	}
	else if(error==-17)
	{
		printf("Line %d: Identifier is longer than the prescribed length of 20 characters\n",lineNo);
	}
	else if(error==-20)
	{
		printf("Line %d: RecordId is too long (>200 characters)\n",lineNo);
	}
	else if(error==-21)
	{
		printf("Line %d: TK_NUM is too long (>20 characters)\n",lineNo);
	}
	else if(error==-22)
	{
		printf("Line %d: TK_RNUM is too long (>20 characters)\n",lineNo);
	}
	else if(error==-50)
	{
		printf("Line %d: Unknown Pattern is too long (>20 characters)\n",lineNo);
	}
	else if(error==-25)
	{
		printf("Line %d: Function Identifier is longer than the prescribed length of 30 characters\n",lineNo);
	}
	
	return;
}



int printcommentfree(char *testcaseFile)
{
	char* buff0=(char*)malloc(Bufferlen*sizeof(char));
	char* buff1=(char*)malloc(Bufferlen*sizeof(char));
	
	FILE* fpr = fopen(testcaseFile,"r");
	if(fpr==NULL)
	{
		printf("Invalid testcaseFile\n");
		return -1;
	}
	int checker=0;
	getStream(fpr,buff1);
	getStream(fpr,buff0);
	int currentindex=0;
	char current_input=buff1[currentindex];
	while(current_input != '\0')
	{
		checker=0;
		if(currentindex>=Bufferlen)
		{
			char* temp=buff1;
			buff1=buff0;
			buff0 = temp;
			getStream(fpr,buff0);
			currentindex=0;
		}
		current_input=buff1[currentindex];
		if(current_input == '\0')
		{
			break;
		}
		if(current_input=='%')
		{
			while(current_input != '\n' && current_input != '\0') 
			{
				if(currentindex>=Bufferlen)
				{
					char* temp=buff1;
					buff1=buff0;
					buff0 = temp;
					getStream(fpr,buff0);
					currentindex=0;
				}
				else
					currentindex++;
					
				current_input=buff1[currentindex];
			}
			if(current_input == '\n')
			{
				checker=1;
			}	
		}
		if(current_input == '\0')
		{
			break;
		}
		currentindex++;
		if(checker!=1)
		{
			printf("%c",current_input);
		}
	}
	free(buff1);
	free(buff0);
	return 0;
}
