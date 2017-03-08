#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include <string.h>
/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/

FILE *getStream(FILE *fp, buffer B, buffersize k)
{
	int x=0;
	char ch;
	//for(x=0;x<k;x++)
	//	B[x]='`';
	//printf("Initial Buffer : %s \n",B);
	//x=0;
	if(fp!=NULL)
	{	
		for(x=0;x<k;x++)
		{
			if(!feof(fp))
			{
				ch=getc(fp);
				//printf("inside getstream :%ld \n ",ftell(fp));
				B[x]=ch;
			}
				
		}//printf("Final Buffer : %s \n",B);
	//printf("afsafsafasfasfas");
	//B[x]='\0';
	//printf("\n %s ",B);
		
	}
	else
	printf("Error in reading file");	
	return fp;	
}

/*
int main()
{
int MAXBUFLEN = bufferSize;
buffer source1;
//source1[MAXBUFLEN]="/n";
FILE *fp = fopen("tester.txt", "r");
while(!feof(fp))
{
fp = getStream(fp,source1,MAXBUFLEN);
printf("\n%s\n",source1);
}
return 0;

}
*/
tokenInfo  getNextToken(FILE *fp, int f)
{
	/*This function reads the input character stream and uses efficient mechanism to recognize lexemes. The function tokenizes the lexeme appropriately and returns all relevant information it collects in this phase (lexical analysis phase) encapsulated as  tokenInfo. The function also displays lexical errors appropriately (list of errors to be uploaded soon). The input parameters are made flexible and students can select appropriate input parameters. The function also takes care of ignoring the white spaces and comments. */

    tokenInfo t;
    t.err=0;
    t.flaglex=0;
    char temp[100];
    int z=0;
    char keywords[24][15]={"with","parameters","end","while","int","real","type","_main","global","parameter","list",
			   "input","output","endwhile","if","then","endif","read","write","return",
			    "call","record","endrecord","else"};
    char keytokens[24][15]={"TK_WITH","TK_PARAMETERS","TK_END","TK_WHILE","TK_INT","TK_REAL","TK_TYPE","TK_MAIN","TK_GLOBAL",
			    "TK_PARAMETER","TK_LIST","TK_INPUT","TK_OUTPUT","TK_ENDWHILE","TK_IF","TK_THEN","TK_ENDIF",
			    "TK_READ","TK_WRITE","TK_RETURN","TK_CALL","TK_RECORD","TK_ENDRECORD","TK_ELSE"};
    int m=0; //denotes the position of keyword in character array

     while(f==0)                                 // ERRORS AND LENGTH CHECKS TO BE IMPLEMENTED YET
    { 
	//printf("\nstart of while loop state = %d \n",state);
	while(i<k)
	{	
		//printf("temp is %s \n",temp);
		if(B[i]==-1)
		{
			//printf("Buffer at flag time is %s \n",B);
			t.flaglex=1;
			//printf("\n flaglex = %d\n",flaglex);
			f=1;
			return t;
			break;
		}
		if(state==0 && B[i]=='\n')
		{
			i++;
			ln++;
			continue;
		}
		if(B[i]=='['&&state==0)
		{   
            		i++;
			strcpy(t.lexName, "[");	    		
			strcpy(t.tokenName,"TK_SQL");
	    		t.lineNo=ln;
	    		f=1;
	    		return t;
		}
		if(B[i]==']'&&state==0)
		{
			strcpy(t.lexName,"]");
	    		i++;
	    		strcpy(t.tokenName,"TK_SQR");
	    		t.lineNo=ln;
	    		f=1;
	    		return t;
		}
	
		if(B[i]==';'&&state==0)
		{
		    strcpy(t.lexName,";");
		    i++;
		    strcpy(t.tokenName,"TK_SEM");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
	
		if(B[i]==':'&&state==0)
		{
		    strcpy(t.lexName,":");
		    i++;
		    strcpy(t.tokenName,"TK_COLON");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		if(B[i]==','&&state==0)
		{
		    strcpy(t.lexName,",");
		    i++;
		    strcpy(t.tokenName,"TK_COMMA");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		if(B[i]=='.'&&state==0)
		{
		    strcpy(t.lexName,".");
		    i++;
		    strcpy(t.tokenName,"TK_DOT");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		if(B[i]=='('&&state==0)
		{	
		    strcpy(t.lexName,"(");
		    i++;
		    strcpy(t.tokenName,"TK_OP");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		
		if(B[i]==')'&&state==0)
		{
		    strcpy(t.lexName,")");
		    i++;
		    strcpy(t.tokenName,"TK_CL");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		
		if(B[i]=='+'&&state==0)
		{
		    strcpy(t.lexName,"+");
		    i++;
		    strcpy(t.tokenName,"TK_PLUS");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		
		if(B[i]=='-'&&state==0)
		{
		    strcpy(t.lexName,"-");
		    i++;
		    strcpy(t.tokenName,"TK_MINUS");
		    t.lineNo=ln;
        	    f=1;
		    return t;
		}
		
		
		if(B[i]=='*'&&state==0)
		{
		    strcpy(t.lexName,"*");
		    //printf("Value of i here is %d \n",i);
		   //printf("B[i] = \n",B[i]);		
		    i++;
		    strcpy(t.tokenName,"TK_MUL");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		
		if(B[i]=='/'&&state==0)
		{
		    strcpy(t.lexName,"/");
		    i++;
		    strcpy(t.tokenName,"TK_DIV");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
		
		if(B[i]=='~'&&state==0)
		{
		    strcpy(t.lexName,"~");
		    i++;
		    strcpy(t.tokenName,"TK_NOT");
		    t.lineNo=ln;
		    f=1;
		    return t;
		}
		
	
		if(B[i]=='%'&&state==0)
		{
		    while((B[i]!='\n'))
		    {
			if(i<k)
			{
			    	i++;
			}
			else
			{
				fp=getStream(fp,B,k);
				i=0;			
		        }
		    }
		    i++;
		    f=1;
		    strcpy(t.tokenName,"TK_COMMENT");
		    t.lineNo=ln;
		    ln++;
		    strcpy(t.lexName,"");
		    return t;
		}


		if(B[i]=='='&&state==0) //next 3 if-else for TK_EQ
		{
			state=1;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(B[i]!='='&&state==1)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='='&&state==1)
		{
			strcpy(t.lexName,"==");
			i++;
			state=0;
			strcpy(t.tokenName,"TK_EQ");
			t.lineNo=ln;
			f=1;
			return t;
		}


		if(B[i]=='!'&&state==0) //next 3 if-else for TK_NE
		{
			state=2;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;		
		}
		if(B[i]!='='&&state==2)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='='&&state==2)
		{
			strcpy(t.lexName,"!=");
			i++;
			state=0;
			strcpy(t.tokenName,"TK_NE");
			t.lineNo=ln;
			f=1;
			return t;
		}
		

		
		if(B[i]=='&'&&state==0) //next 5 if-else for TK_AND
		{
			state=3;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(B[i]!='&'&&state==3)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='&'&&state==3)
		{
			state=4;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;		
			continue;
		}
		if(B[i]!='&'&&state==4)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='&'&&state==4)
		{
			strcpy(t.lexName,"&&&");
			i++;
			state=0;
			strcpy(t.tokenName,"TK_AND");
			t.lineNo=ln;
			f=1;
			return t;
		}
	

		if(B[i]=='@'&&state==0) //next 5 if-else for TK_OR
		{
			state=5;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(B[i]!='@'&&state==5)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='@'&&state==5)
		{
			state=6;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(B[i]!='@'&&state==6)
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}
		if(B[i]=='@'&&state==6)
		{
			strcpy(t.lexName,"@@@");
			i++;
			state=0;
			strcpy(t.tokenName,"TK_OR");
			t.lineNo=ln;
			f=1;
			return t;
		}
		

		if(B[i]=='<'&&state==0) //for TK_LE,TK_LT,TK_ASSIGNOP
		{
			state=7;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(state==7&&B[i]=='=')
		{
			strcpy(t.lexName,"<=");
			state=0;
			strcpy(t.tokenName,"TK_LE");
			t.lineNo=ln;
			f=1;
			i++;
			return t;
		}
		if(state==7&&B[i]=='-')
		{
			state=8;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(state==7&&B[i]!='-'&&B[i]!='=')
		{
			strcpy(t.lexName,"<");
			state=0;
			strcpy(t.tokenName,"TK_LT");
			t.lineNo=ln;
			f=1;
			return t;
		}
		if(state==8&&B[i]=='-')
		{	
			state=9;
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}
		if(state==8&&B[i]!='-')	
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		} 		//	printf ("\n 1st state %d\n",state);
		if(state==9&&B[i]=='-')
		{
			strcpy(t.lexName,"<---");
			i++;
			state=0;
			strcpy(t.tokenName,"TK_ASSIGNOP");
			t.lineNo=ln;
			f=1;
			return t;
		}	//	printf ("\n 2nd state %d\n",state);
		if(state==9&&B[i]!='-')
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;
		}


		if(state==0&&B[i]=='>')	  //for TK_GE and TK_GT
		{
			state=10;
			i++;
			continue;
		}
		if(state==10&&B[i]=='=')
		{
			strcpy(t.lexName,">=");
			state=0;
			strcpy(t.tokenName,"TK_GE");
			t.lineNo=ln;
			f=1;
			return t;
		}
		if(state==10&&B[i]!='=')
		{
			strcpy(t.lexName,">");
			state=0;
			strcpy(t.tokenName,"TK_GT");
			t.lineNo=ln;
			f=1;
			return t;
		}
		


       		if(state==0&&B[i]=='#') //for TK_RECORDID
        	{
            	        state=11;
            		i++;
			//printf("K");
            		temp[z]='#';
            		temp[z+1]='\0';
			z++;
			continue;
			//getchar();
        	}
		if(state==11&&(B[i]<'a'||B[i]>'z'))
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;	
		}
        	if(state==11&&B[i]>='a'&&B[i]<='z')
        	{
			//printf("L");
            		state=12;
            		temp[z]=B[i];
            		temp[z+1]='\0';
            		z++;
            		i++;
			//printf("state 11: value of i %d \n",i);
			continue;
	        }

		if(state==12&&B[i]>='a'&&B[i]<='z')
		{
			//printf("state 12: value of i %d \n",i);
			//printf("M");
			//getchar();
			temp[z]=B[i];
			temp[z+1]='\0';
			z++;
			i++;
			continue;
		}

        	if(state==12&&(B[i]<'a'||B[i]>'z'))
        	{
			//getchar();
			//printf("N");
        		strcpy(t.lexName,temp);
         		state=0;
			strcpy(t.tokenName,"TK_RECORDID");
			t.lineNo=ln;
			f=1;
			return t;
        	}

        	if(state==0&&B[i]>='0'&&B[i]<='9') //for TK_NUM and TK_RNUM
        	{
			/*printf("Value of i here is %d \n",i);
			printf("B[i]= %d \n",B[i]);
			printf("K");
            		*/state=13;
            		temp[z]=B[i];
            		temp[z+1]='\0';
            		z++;
            		i++;
			continue;
        	}
        	if(state==13&&B[i]>='0'&&B[i]<='9')
        	{	
			/*printf("Value of i here is %d \n",i);
			printf("B[i]= %d \n",B[i]);
			printf("L"); */
			state=13;
            		temp[z]=B[i];
            		temp[z+1]='\0';
            		z++;
            		i++;
			continue;
        	}
        	if((state==13&&B[i]!='.')&&(B[i]>'9'||B[i]<'0'))
        	{
			/*strcpy(t.lexName,temp);   */      		
			state=0;
			strcpy(t.lexName,temp);
			strcpy(t.tokenName,"TK_NUM");
			t.lineNo=ln;
			f=1;
			return t;
        	}
        	if(state==13&&B[i]=='.')		
		{
			state=14;
			temp[z]='.';
			temp[z+1]='\0';
			i++;
			z++;
			continue;
		}
		if(state==14&&(B[i]<'0'||B[i]>'9'))
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;	

		}
		if(state==14&&B[i]>='0'&&B[i]<='9')
		{
			state=15;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;
			continue;
		}
		if(state==15&&B[i]>='0'&&B[i]<='9')
		{
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;
			continue;
		}
		if(state==15&&(B[i]<'0'||B[i]>'9'))
		{
			strcpy(t.lexName,temp);
			state=0;
			strcpy(t.tokenName,"TK_RNUM");
			t.lineNo=ln;
			f=1;
			return t;
		}


		if(state==0&&B[i]>='b'&&B[i]<='d') //for TK_ID
		{
		//	printf("\n State A = %d \n",state);
			state=16;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==16&&(B[i]>='a'&&B[i]<='z'))
		{
			//printf("\n State Z = %d \n",state);
			state=19;                                            //CHECK
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==16&&(B[i]>='2'&&B[i]<='7'))
		{
		//	printf("\n State B = %d \n",state);
			state=17;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;			
			continue;	
		}
		if(state==16&&(B[i]<'2'||B[i]>'7')&&(B[i]<'a'||B[i]>'z'))   //check
		{
			strcpy(t.lexName,temp); 
			state=0;
			strcpy(t.tokenName,"TK_FIELDID");
			t.lineNo=ln;
			f=1;
			return t;
		}
		if(state==17&&(B[i]>='b'&&B[i]<='d'))
		{
			//printf("\n State C = %d \n",state);
			state=17;
			if(strlen(temp)<20)
			{
				temp[z]=B[i];
				temp[z+1]='\0';
				i++;
				z++;
			//printf("\n i = %d \n",i);
			//printf("\n state = %d \n",state);						
			continue;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_1 : Identifier at line  %d is longer than the prescribed length of 20 characters \n",ln);
				t.err=1;
				continue;
	
			} 
		}
		if(state==17&&(B[i]>='2'&&B[i]<='7'))
		{
			//printf("\n State D= %d \n",state);
			state=18;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==17&&((B[i]<'2'||B[i]>'7')&&(B[i]<'b'||B[i]>'d')))
		{
			//printf("\n State E = %d \n",state);
			state=0;
			if(strlen(temp)<20)
			{
				strcpy(t.lexName,temp);
				strcpy(t.tokenName,"TK_ID");
				t.lineNo=ln;
				f=1;
				return t;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_1 : Identifier at line  %d is longer than the prescribed length of 20 characters \n",ln);
				t.err=1;
				continue;
	
			}
		}
		if(state==18&&(B[i]>='2'&&B[i]<='7'))
		{
			//printf("\n State F = %d \n",state);
			if(strlen(temp)<20)
			{			
				state=18;
				temp[z]=B[i];
				temp[z+1]='\0';
				i++;
				z++;				
				continue;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_1 : Identifier at line  %d is longer than the prescribed length of 20 characters \n",ln);
				t.err=1;
				continue;
	
			}
		}
			
		if(state==18&&(B[i]<'2'||B[i]>'7'))
		{
			if(strlen(temp)<20)
			{
				//printf("\n State G = %d \n",state);
				strcpy(t.lexName,temp);
				state=0;
				strcpy(t.tokenName,"TK_ID");
				t.lineNo=ln;
				f=1;
				return t;
			}
			else
			{
				//printf("\n %s \n",temp);
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_1 : Identifier at line  %d is longer than the prescribed length of 20 characters \n",ln);
				t.err=1;
				continue;
	
			}
		}

		
		if(state==0&&B[i]>='a'&&B[i]<='z'&&B[i]!='b'&&B[i]!='c'&&B[i]!='d') // for TK_FIELDID and KEYWORDS
		{
			state=19;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==19&&B[i]>='a'&&B[i]<='z')
		{
			state=19;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==19&&(B[i]<'a'||B[i]>'z'))
		{
			for(m=0;m<24;m++)
			{
				if(strcmp(temp,keywords[m])==0)
				{
					state=0;
					f=1;
					t.lineNo=ln;
					strcpy(t.lexName,temp);
					strcpy(t.tokenName,keytokens[m]);
					return t;
				}
			}
			strcpy(t.lexName,temp); 
			state=0;
			strcpy(t.tokenName,"TK_FIELDID");
			t.lineNo=ln;
			f=1;
			return t;
			
		}

	
		if(state==0&&B[i]=='_') // For TK_FUNID
		{
			state=20;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==20&&(B[i]<'a'||B[i]<='z')&&(B[i]<'A'&&B[i]>'Z'))
		{
			state=0;
			printf("\nERROR_3:  Unknown pattern %s \n",temp);
			temp[0]='\0';
			z=0;
			t.err=1;
			continue;	
		}
		if(state==20&&((B[i]>='a'&&B[i]<='z')||(B[i]>='A'&&B[i]<='Z')))
		{
			//printf(" \n B[i]= %c \n",B[i]);
			state=21;
			temp[z]=B[i];
			temp[z+1]='\0';
			i++;
			z++;				
			continue;
		}
		if(state==21&&((B[i]>='a'&&B[i]<='z')||(B[i]>='A'&&B[i]<='Z')))
		{
			if(strlen(temp)<30)
			{
				state=21;
				temp[z]=B[i];
				temp[z+1]='\0';
				i++;
				z++;	
				if(strcmp(temp,keywords[7])==0)
				{
					state=0;
					f=1;
					t.lineNo=ln;
					strcpy(t.lexName,temp);
					strcpy(t.tokenName,keytokens[7]);
					return t;		
				}		
				continue;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_4 : Function Identifier at line  %d is longer than the prescribed length of 30 characters 					\n",ln);
				t.err=1;
				continue;
			}

			
		}
		if(state==21&&(B[i]<'0'||B[i]>'9'))
		{
		 	state=0;
			f=1;
			t.lineNo=ln;
			strcpy(t.lexName,temp);
			strcpy(t.tokenName,"TK_FUNID");
			return t;
		}
		if(state==21&&B[i]>='0'&&B[i]<='9')
		{
			if(strlen(temp)<30)
			{
				state=22;
				temp[z]=B[i];
				temp[z+1]='\0';
				i++;
				z++;
				continue;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_4 : Function Identifier at line  %d is longer than the prescribed length of 30 characters 					\n",ln);
				t.err=1;
				continue;
			}
		}
		if(state==22&&B[i]>='0'&&B[i]<='9')
		{
			if(strlen(temp)<30)
			{
				temp[z]=B[i];
				temp[z+1]='\0';
				i++;
				z++;
				continue;
			}
			else
			{
				state=0;
				temp[0]='\0';
				z=0;
				printf("\nERROR_4 : Function Identifier at line  %d is longer than the prescribed length of 30 characters 					\n",ln);
				t.err=1;
				continue;
			}
		}
		if(state==22&&(B[i]<'0'||B[i]>'9'))
		{
			state=0;
			f=1;
			t.lineNo=ln;
			strcpy(t.lexName,temp);
			strcpy(t.tokenName,"TK_FUNID");
			return t;
		}
		if(state==0&&B[i]=='\t')
		{
			i++;
			continue;
		}

		if(state==0 &&B[i]==' ')
		{
			i++;
			//printf("(space)B[i]= %d \n",B[i]);
			continue;
		}
		printf("\nERROR_2: Unknown Symbol %c at line %d\n",B[i],ln);
		t.err=1;
		i++;
    	}
    	if(i==k)
	{
		//printf("SAFAS %d",i);
		fp=getStream(fp,B,k);
		i=0;	
		//printf("andar wala fp = %ld \n",ftell(fp));		
	}
    }
}
/*
int main()
{
	printf("Test Case \n");
	fp = fopen("testcase.txt", "r");
	fp=getStream(fp,B,k);
	int j=0;
	int f=0;
	tokenInfo test;
	if(fp!=NULL)
	printf("Printing Tokens : \n");
	/*for(j=0;j<k;j++)
	{
		if(B[j]==-1)	
			break;
		f=0;
		test=getNextToken(fp,f);
		if(flaglex==0)
			printf("\n%s in line no. : %d and lexeme name %s \n",test.tokenName,test.lineNo, test.lexName);	
	}
	//printf("Buffer at this time is %s \n",B);
	while(flaglex!=1)
	{
		f=0;
		//printf("Buffer at this time is %s \n",B);
		test=getNextToken(fp,f);
		//printf("\n Buffer at this time is %s \n",B);
		//printf("\n main wala fp %ld",ftell(fp));
		if(flaglex==0)
		printf("\n%s in line no. : %d and lexeme name %s \n",test.tokenName,test.lineNo, test.lexName);		
		else
		printf("\n End of file \n");
	}	
	return 0;
}	


*/
