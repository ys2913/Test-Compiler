//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "stackops.h"
#include <string.h>
#include "lexer.h"
#include "parser.h"

//#include "hashFunctions.h"

/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/

int atom=0;

Stackhead createstack()
{
	Stackhead s;
	s.top = NULL;
	s.size =0;
	s.error  = FALSE;
	return s;
}


char *top(Stackhead s)

{
	if(s.top!=NULL)
		return s.top->tok;
	else
		return "null";
}



Stackhead push(Stackhead s ,char tok[50])
{
	Stacklink ptr = (Stacklink)malloc(sizeof(Stacknode));
	if(ptr == NULL)
	{
		s.error = TRUE;
		return s;
	}
	else
	{
		strcpy(ptr->tok,tok);
		ptr->next = s.top;
		s.top = ptr;
		s.size++;
		return s;
	}
}



Stackhead pop(Stackhead s)
{
	if(s.top == NULL)
	printf("Can't pop. Empty list.\n");
	else
	{
		Stacklink ptr = s.top;
		s.top = s.top->next;
		free(ptr);
		s.size--;
	}
	return s;
}



void printstack(Stackhead s)
{
	Stacklink curr= s.top;
	int count = 0;
	printf("Printing...\n");
	while (curr!= NULL)
	{
		count ++;
		printf("%d %s\n",count, curr->tok);
		curr=curr->next;
	}
	if(count ==0)
		printf("Empty Stack!!\n");
	else
		printf("End of Stack\n");
}






Treenode create()
{
 Treenode current;

 current = (Treenode)malloc(sizeof(struct treenode));
 current->noofchildren=0;
 current->posofchildren=0;
 current->children=NULL;
 current->sibling=NULL;
 current->parent=NULL;
 strcpy(current->a.lexemecurrentnode,"");//change BLEH
 current->a.lineno=0;
 strcpy(current->a.token,"");
 strcpy(current->a.parentnodesymbol,"");
 strcpy(current->a.isleafnode,"");
 strcpy(current->a.nodesymbol,"");

 return current;


}

//===========================================================================================================================================================================================

//============================================================================================================================================================================================




//---------------------------FOR PARSR TREE END------------------------------------------------






void createParseTable(FILE *fp1,FILE *fp2,FILE *fp3,int array[50][55],char grammar[90][150])
{
 static int lineno=0;
 static int lineno2=0;
 static int lineno3=0;
 //FILE *fp1;
 //FILE *fp2;
 //FILE *fp3;
 //fp1 = fopen("grammar.txt", "r");//to be opened in main and passed
 //fp2 = fopen("first.txt", "r");//to be opened in main and passed
 //fp3 = fopen("follow.txt", "r");//to be opened in main and passed
 //char grammar[90][150];
 char c1,c2,c3;
 int r=0;
 int a,b,c,d;
 //int array[50][55];


	/*int p,q;
	for(p=0; p<50;p++)
	{
		for(q=0;q<55;q++)
		array[p][q]=0;

	}*/

 	for(r=0;r<90;r++)
	{
	char line1[150]="";
	char line2[150]="";
	char line3[150]="";
	int k=0,j=0;
	int p=0;

		while((c1=fgetc(fp1))!='\n')
	 	{
		line1[p]=c1;
		p++;
	 	}
		lineno++;
		strcpy(grammar[r],line1);
		char buffer[30]="";
		int buf=0;
		int dum=0;

			while(line1[buf]!='@')
			{
				if(line1[buf]==' ')
					buf++;
				else
				{
					buffer[dum]=line1[buf];
					dum++;
					buf++;
				}

			}
			a=getrowno2(buffer);
			//printf("rowno:::%d\n",a);
			//printf("buffer %s\n",buffer);
			int li=0;
		while((c2=fgetc(fp2))!='\n')
		{
		line2[li]=c2;
		li++;
		}
		//printf("line2::::::::::::: %s\n",line2);
		lineno2++;

		int li2=0;
		while((c3=fgetc(fp3))!='\n')
		{
		line3[li2]=c3;
		li2++;
		}
		//printf("line3::::::::::::: %s\n",line3);
		//printf("line2::::::::::::: %s\n",line2);
		lineno3++;

			while(line2[k] != '#')
			{
			char buffer2[30]="";
			int temp=0;
			while(line2[k] != ' ')
				{
					buffer2[temp]=line2[k];
					k++;
					temp++;
				}

					b=getcolno(buffer2);
					//printf("col %s \n",buffer2);
					//printf("col number %d \n",b);
					if(b == -1)
					{

						while(line3[j] != '#')
						{
						char buffer3[30]="";
						//size_t len1 = 0;
						int temp2=0;
							while(line3[j] != ' ')
							{
							buffer3[temp2]=line3[j];
							j++;
							temp2++;
							}

						d=getcolno(buffer3);
						array[a][d]=lineno;

						j++;
						}
					}

					else
					array[a][b]=lineno;


				k++;
			}



	}

/*int m=0,n=0;
	for(m=0;m<50;m++)
	{
		for(n=0;n<55;n++)
		printf("%3d",array[m][n]);
		printf("\n");

	}*/
//return 0;
}


int getrowno2(char *buffer)
{
 int rid=-5;

	if(strcmp(buffer,"<program>") ==0)
			rid=0;
		else if(strcmp(buffer,"<mainFunction>") == 0)
			rid=1;
		else if(strcmp(buffer,"<otherFunctions>") == 0)
			rid=2;
		else if(strcmp(buffer,"<function>") == 0)
			rid=3;
		else if(strcmp(buffer,"<input_par>") == 0)
			rid=4;
		else if(strcmp(buffer,"<output_par>") == 0)
			rid=5;
		else if(strcmp(buffer,"<parameter_list>") == 0)
			rid=6;
		else if(strcmp(buffer,"<dataType>") == 0)
			rid=7;
		else if(strcmp(buffer,"<primitiveDatatype>") == 0)
			rid=8;
		else if(strcmp(buffer,"<constructedDatatype>") == 0)
			rid=9;
		else if(strcmp(buffer,"<remaining_list>") == 0)
			rid=10;
		else if(strcmp(buffer,"<stmts>") == 0)
			rid=11;
		else if(strcmp(buffer,"<typeDefinitions>") == 0)
			rid=12;
		else if(strcmp(buffer,"<typeDefinition>") == 0)
			rid=13;
		else if(strcmp(buffer,"<fieldDefinitions>") == 0)
			rid=14;
		else if(strcmp(buffer,"<fieldDefinition>") == 0)
			rid=15;
		else if(strcmp(buffer,"<moreFields>") == 0)
			rid=16;
		else if(strcmp(buffer,"<declarations>") == 0)
			rid=17;
		else if(strcmp(buffer,"<declaration>") == 0)
			rid=18;
		else if(strcmp(buffer,"<global_or_not>") == 0)
			rid=19;
		else if(strcmp(buffer,"<otherStmts>") == 0)
			rid=20;
		else if(strcmp(buffer,"<stmt>") == 0)
			rid=21;
		else if(strcmp(buffer,"<assignmentStmt>") == 0)
			rid=22;
		else if(strcmp(buffer,"<singleOrRecId>") == 0)
			rid=23;
		else if(strcmp(buffer,"<funCallStmt>") == 0)
			rid=24;
		else if(strcmp(buffer,"<outputParameters>") == 0)
			rid=25;
		else if(strcmp(buffer,"<inputParameters>") == 0)
			rid=26;
		else if(strcmp(buffer,"<iterativeStmt>") == 0)
			rid=27;
		else if(strcmp(buffer,"<conditionalStmt>") == 0)
			rid=28;
		else if(strcmp(buffer,"<elsePart>") == 0)
			rid=29;
		else if(strcmp(buffer,"<ioStmt>") == 0)
			rid=30;
		else if(strcmp(buffer,"<allVar>") == 0)
			rid=31;
		else if(strcmp(buffer,"<arithmeticExpression>") == 0)
			rid=32;
		else if(strcmp(buffer,"<expPrime>") == 0)
			rid=33;
		else if(strcmp(buffer,"<term>") == 0)
			rid=34;
		else if(strcmp(buffer,"<termPrime>") == 0)
			rid=35;
		else if(strcmp(buffer,"<factor>") == 0)
			rid=36;
		else if(strcmp(buffer,"<highPrecedenceOperators>") == 0)
			rid=37;
		else if(strcmp(buffer,"<lowPrecedenceOperators>") == 0)
			rid=38;
		else if(strcmp(buffer,"<all>") == 0)
			rid=39;
		else if(strcmp(buffer,"<temp>") == 0)
			rid=40;
		else if(strcmp(buffer,"<booleanExpression>") == 0)
			rid=41;
		else if(strcmp(buffer,"<var>") == 0)
			rid=42;
		else if(strcmp(buffer,"<logicalOp>") == 0)
			rid=43;
		else if(strcmp(buffer,"<relationalOp>") == 0)
			rid=44;
		else if(strcmp(buffer,"<returnStmt>") == 0)
			rid=45;
		else if(strcmp(buffer,"<optionalReturn>") == 0)
			rid=46;
		else if(strcmp(buffer,"<idList>") == 0)
			rid=47;
		else if(strcmp(buffer,"<more_ids>") == 0)
			rid=48;
		else if(strcmp(buffer,"<rest>") == 0)
			rid=49;

	return rid;


}



//-------------------------------------------------------------------------------------------------------------------------------






int getcolno(char *buffer2)
{
     int colid=-5;

	if(strcmp(buffer2,"eps") == 0)
	colid= -1;
	else if(strcmp(buffer2,"$") == 0)
	colid= 0;
	else if(strcmp(buffer2,"TK_FUNID") == 0)
	colid=1;
	else if(strcmp(buffer2,"TK_MAIN") == 0)
	colid=2;
	else if(strcmp(buffer2,"TK_INPUT") == 0)
	colid= 3;
	else if(strcmp(buffer2,"TK_OUTPUT") == 0)
	colid= 4;
	else if(strcmp(buffer2,"TK_INT") == 0)
	colid=5;
	else if(strcmp(buffer2,"TK_REAL") == 0)
	colid=6;
	else if(strcmp(buffer2,"TK_RECORD") == 0)
	colid=7;
	else if(strcmp(buffer2,"TK_COMMA") == 0)
	colid=8;
	else if(strcmp(buffer2,"TK_TYPE") == 0)
	colid=9;
	else if(strcmp(buffer2,"TK_ID") == 0)
	colid=10;
	else if(strcmp(buffer2,"TK_WHILE") == 0)
	colid=11;
	else if(strcmp(buffer2,"TK_IF") == 0)
	colid=12;
	else if(strcmp(buffer2,"TK_READ") == 0)
	colid=13;
	else if(strcmp(buffer2,"TK_WRITE") == 0)
	colid=14;
	else if(strcmp(buffer2,"TK_SQL") == 0)
	colid=15;
	else if(strcmp(buffer2,"TK_CALL") == 0)
	colid=16;
	else if(strcmp(buffer2,"TK_RETURN") == 0)
	colid=17;
	else if(strcmp(buffer2,"TK_COLON") == 0)
	colid=18;
	else if(strcmp(buffer2,"TK_ELSE") == 0)
	colid=19;
	else if(strcmp(buffer2,"TK_ENDIF") == 0)
	colid=20;
	else if(strcmp(buffer2,"TK_NUM") == 0)
	colid=21;
	else if(strcmp(buffer2,"TK_RNUM") == 0)
	colid=22;
	else if(strcmp(buffer2,"TK_RECORDID") == 0)
	colid=23;
	else if(strcmp(buffer2,"TK_OP") == 0)
	colid=24;
	else if(strcmp(buffer2,"TK_PLUS") == 0)
	colid=25;
	else if(strcmp(buffer2,"TK_MINUS") == 0)
	colid=26;
	else if(strcmp(buffer2,"TK_MUL") == 0)
	colid=27;
	else if(strcmp(buffer2,"TK_DIV") == 0)
	colid=28;
	else if(strcmp(buffer2,"TK_DOT") == 0)
	colid=29;
	else if(strcmp(buffer2,"TK_NOT") == 0)
	colid=30;
	else if(strcmp(buffer2,"TK_AND") == 0)
	colid=31;
	else if(strcmp(buffer2,"TK_OR") == 0)
	colid=32;
	else if(strcmp(buffer2,"TK_LT") == 0)
	colid=33;
	else if(strcmp(buffer2,"TK_LE") == 0)
	colid=34;
	else if(strcmp(buffer2,"TK_EQ") == 0)
	colid=35;
	else if(strcmp(buffer2,"TK_GT") == 0)
	colid=36;
	else if(strcmp(buffer2,"TK_GE") == 0)
	colid=37;
	else if(strcmp(buffer2,"TK_NE") == 0)
	colid=38;
	else if(strcmp(buffer2,"TK_SEM") == 0)
	colid=39;
	else if(strcmp(buffer2,"TK_SQR") == 0)
	colid=40;
	else if(strcmp(buffer2,"TK_END") == 0)
	colid=41;
	else if(strcmp(buffer2,"TK_ENDRECORD") == 0)
	colid=42;
	else if(strcmp(buffer2,"ENDWHILE") == 0)
	colid=43;
	else if(strcmp(buffer2,"TK_ASSIGNOP") == 0)
	colid=44;
	else if(strcmp(buffer2,"TK_CL") == 0)
	colid=45;
	else if(strcmp(buffer2,"TK_COMMENT") == 0)
	colid=46;
	else if(strcmp(buffer2,"TK_FIELDID") == 0)
	colid=47;
	else if(strcmp(buffer2,"TK_WITH") == 0)
	colid=48;
	else if(strcmp(buffer2,"TK_PARAMETERS") == 0)
	colid=49;
	else if(strcmp(buffer2,"TK_GLOBAL") == 0)
	colid=50;
	else if(strcmp(buffer2,"TK_LIST") == 0)
	colid=51;
	else if(strcmp(buffer2,"TK_ENDWHILE") == 0)
	colid=52;
	else if(strcmp(buffer2,"TK_THEN") == 0)
	colid=53;

  return colid;

}


/*Treenode getout(Treenode curr)
{
	if(curr->sibling==NULL)
		curr=getout(curr->parent);
	else
		curr=curr->sibling;

	return curr;

}*/


Treenode getout(Treenode curr)
{
  Treenode tempo;
	tempo=curr;

	if(curr->sibling!=NULL)
	 {
	  curr=curr->sibling;
	  return curr;
	 }
	else if(curr->parent!=NULL)
	 {
	  curr=curr->parent;
	  tempo=getout(curr);
	  return tempo;
	 }
	else
	 {
	  return curr;
	 }


}


Treenode createparsetree(FILE *fp,int array[50][55],char grammar[90][150])
{

 char temp[30];
 char tempbuffer[100]="";

 int row2,col2,ruleno;

 tokenInfo lexvalues;
 Treenode head;
 Treenode curr;
 Treenode temporary;
 Treenode dog;

 head = create();
 strcpy(head->a.token,"<program>");
 strcpy(head->a.lexemecurrentnode,"<program>");
 strcpy(head->a.isleafnode,"NO");


 curr=head;


 Stackhead s;
 s = createstack();
 strcpy(temp,"$");
 s=push(s,temp);
 strcpy(temp,"<program>");
 s=push(s,temp);



	if(fp==NULL)
	{
		 printf("\n File is empty \n");
		 exit(EXIT_FAILURE);
	}
	fp=getStream(fp,B,k);

	lexvalues=getNextToken(fp,0);
	while(strcmp(lexvalues.lexName,"")==0)
		lexvalues=getNextToken(fp,0);
	//printf("\n%s in line no. : %d and lexeme name %s \n",lexvalues.tokenName,lexvalues.lineNo, lexvalues.lexName);





    while(strcmp(s.top->tok,"$")!=0)
    {


	temporary=curr;


	if(s.top->tok[0] !='<')
	{
	   if(strcmp(s.top->tok,lexvalues.tokenName)==0)
		{
	  		s=pop(s);

   			temporary=curr->parent;
		  	strcpy(curr->a.lexemecurrentnode,lexvalues.lexName);

		  	curr->a.lineno=lexvalues.lineNo;
		  	strcpy(curr->a.token,lexvalues.tokenName);
			//printf("currentHEEEEEE  %s %s \n",curr->a.lexemecurrentnode,curr->a.token);

			Treenode test;
			test=getout(curr);
			curr=test;

						//if(curr->sibling != NULL)
		  				//curr=curr->sibling;
		  				//else if(curr->parent->sibling!=NULL)
  		  				//curr=curr->parent->sibling;
						//else
						//curr=curr->parent->parent;
			if(curr->parent!=NULL)
			temporary=curr->parent;


			//printf("WOW I AM HERE\n");
			//printf("current  %s \n",curr->a.lexemecurrentnode);

			lexvalues=getNextToken(fp,0);
			while(strcmp(lexvalues.lexName,"")==0)
				lexvalues=getNextToken(fp,0);
			if(lexvalues.err==1)
			{
				printf("\n Lexical Error \n");
				exit(EXIT_FAILURE);
			}

			//printf("\nToken Name::%s in line no. : %d and lexeme name %s \n",lexvalues.tokenName,lexvalues.lineNo, lexvalues.lexName);
			//getchar();
			if(lexvalues.flaglex==1)
			{
				if(strcmp(s.top->tok,"$")==0)
				{
					printf("\n \t \t::::Grammar Syntactically correct ::::\n \n \n");
				}
				else
				{
					printf("\n \t \t ::::Grammar not syntactically correct %s on the stack::::\n",s.top->tok);
				}
			}
		}

		else
		{
	 	 printf("Error stack top != lexeme \n");
		 printf("EXPECTED TOKEN : %s\n",s.top->tok);
		 printf("PRESENT TOKEN : %s	at line number: %d\n",lexvalues.tokenName,lexvalues.lineNo);
		 //break;
	 	 exit(EXIT_FAILURE);
		}

	}


	else
	{
	  row2=getrowno2(s.top->tok);
	  col2=getcolno(lexvalues.tokenName);
				//printf("col2: %d\n",col2);
				//printf("row2: %d\n",row2);
	  ruleno=array[row2][col2];

		if(ruleno==0)
		{
		  printf("Error:::WRONG RULE NO\n");
		  exit(EXIT_FAILURE);
		}


		else
		{

				//printf("grammar: %s\n",grammar[ruleno-1]);
  		 	 int y=0;
				while(grammar[ruleno-1][y] != '@')
				{
				y++;			//printf("%d\n",y);
				}

			  y+=2;
			  int r=0;


				while(grammar[ruleno-1][y] !='#')
				{
				tempbuffer[r]=grammar[ruleno-1][y];
				r++;
				y++;
				}


						//printf("BBBBBBBBBBBBBBBgrammar:coming\n");
				//printf("grammar:%s\n",tempbuffer);


			  int ql=0;
			  Stackhead t;
			  s=pop(s);
			  int count=0;
 			  int epsflag=0;
			  int flag=0;

				while(tempbuffer[ql] !='!')
				{
				 int h=0;
			         char temp4[30]="";

					 while(tempbuffer[ql] != ' ')
					 {

					  temp4[h]=tempbuffer[ql];
					  			//printf("string123: %d	%c \n",h,temp4[h]);
					  h++;
					  ql++;

		 			 }
			 			//temp[h]='\0';
						//printf("string123: %d	%c \n",h,temp4[h]);
			 			//printf("string: %s \n",temp4);
			 			//temp4[0]='\0';//strcpy(temp4,"a");
			 			//strcpy(temp4,"\0");
					// printf("string2: %s \n",temp4);


					   if(strcmp(temp4,"eps")==0)
					   {
					 	 dog =create();
					 	// printf("DOGGGGGCCCCCC: %s \n",dog->a.lexemecurrentnode);
						// printf("DOG NO OF CHILDREN CCCCC: %d \n",dog->noofchildren);

						 if(flag==0)
						 {
						 curr->children=dog;
						 strcpy(curr->children->a.lexemecurrentnode,temp4);
						 curr->children->parent=temporary;
						// printf("flag00000curr->childre->parent:CCCCCCCC: %s \n",curr->children->parent->a.lexemecurrentnode);
						 curr=curr->children;
					 	 }

				 		else if(flag==1)
				 		{
				 		curr->sibling=dog;
				 		strcpy(curr->sibling->a.lexemecurrentnode,temp4);
				 		curr->sibling->parent=temporary;
				 		//printf("flag11111curr->childre->parent:CCCCCCCC: %s \n",curr->sibling->parent->a.lexemecurrentnode);
				 		curr=curr->sibling;
				 		}

				 		flag=1;

						// printf("RRRRRRRRcurrent: %s \n",curr->a.lexemecurrentnode);
					        // printf("RRRRRRRRcurrentparent: %s \n",curr->parent->a.lexemecurrentnode);
						epsflag=1;
					     	break;
			   		   }

					   else

					   {



						 t = push(t,temp4);

						 dog =create();
					 	 //printf("DOGGGGGCCCCCC: %s \n",dog->a.lexemecurrentnode);

						 //printf("DOG NO OF CHILDREN CCCCC: %d \n",dog->noofchildren);

						 if(flag==0)
						 {
						   curr->children=dog;
						   strcpy(curr->children->a.lexemecurrentnode,temp4);
					 	   curr->children->parent=temporary;
						 //  printf("flag00000curr->childre->parent:CCCCCCCC: %s \n",curr->children->parent->a.lexemecurrentnode);
						   curr=curr->children;
						 }

						 else if(flag==1)
						 {
						   curr->sibling=dog;
				 		   strcpy(curr->sibling->a.lexemecurrentnode,temp4);
						   curr->sibling->parent=temporary;
						  // printf("flag11111curr->childre->parent:CCCCCCCC: %s \n",curr->sibling->parent->a.lexemecurrentnode);
						   curr=curr->sibling;
						 }
						 flag=1;

						// printf("RRRRRRRRcurrent: %s \n",curr->a.lexemecurrentnode);
					       //  printf("RRRRRRRRcurrentparent: %s \n",curr->parent->a.lexemecurrentnode);
						 count++;
						 ql++;

					   }
					 //  printf("count :::%d \n",count);

				}




				if(epsflag==1)
				{

					 curr=getout(temporary);
					 /*if(temporary->sibling!=NULL)
					 curr=temporary->sibling;
					 else
					 curr=temporary->parent->sibling;*/

					 //correct cat;
					 //cat=epscorrect(s,curr,temporary,lexvalues,array,grammar);
					 //s=cat.s;
					 //curr=cat.curr;
					 //temporary=cat.temporary;
				}

				else
				{
					if(temporary->children!=NULL)
					curr=temporary->children;
					else if(temporary->sibling!=NULL)
					curr=temporary->sibling;
					else
					curr=temporary->parent;//pointer back to the first child node
					//printf("TESTING DATA: %s   \n",head->a.lexemecurrentnode);
					//printf("TESTING DATA: %s   \n",curr->sibling->a.lexemecurrentnode);
				}
					//printf("count 2:::%d \n",count);


				 int de=0;
				 for(de=0;de<count;de++)
				 {
					 s=push(s,t.top->tok);
					 t=pop(t);
				 }
		}
	}
	//printf("CURR1 :: %s \n",curr->a.lexemecurrentnode);
	//printf("TEMP1 :: %s \n",temporary->a.lexemecurrentnode);
	//printstack(s);
	//getchar();
	//printf("ENDING:::::::\n");

  }

	return head;


}
//===========================================================================================================================================

void postOrder(Treenode head, FILE * fp5)
{
    Treenode x=NULL;

    if(head->children!=NULL)
    {
        postOrder(head->children,fp5);
        x = head->children->sibling;
        while(x!=NULL)
        {
            postOrder(x,fp5);
            x = x->sibling;
        }

    }
	//fprintf (fp5,"%s \n",head->a.lexemecurrentnode);
	if(head->parent !=NULL)
	strcpy(head->a.parentnodesymbol,head->parent->a.lexemecurrentnode);
	//strcpy(head->a.currentnodesymbol,head->a.lexemecurrentnode);

	int fin=0;
	char go[4]="----";
	if(head->a.token[0]=='T'/*||(strcmp(head->a.lexemecurrentnode,"eps")==0)*/)
		strcpy(head->a.isleafnode,"Yes");
	else
	{
		strcpy(head->a.nodesymbol,head->a.lexemecurrentnode);
		strcpy(head->a.isleafnode,"No");
	}
	if((head->a.lexemecurrentnode[0]=='<')||(strcmp(head->a.lexemecurrentnode,"eps")==0))
		fin=1;
if (fin==0)
{
	if((strcmp(head->a.token,"TK_NUM")==0)||(strcmp(head->a.token,"TK_RNUM")==0))
   		 fprintf (fp5,"1.%20s  2.%20d  3.%20s  4.%20s  5.%30s  6.%20s  7.%20s  \n", head->a.lexemecurrentnode,head->a.lineno,head->a.token,head->a.lexemecurrentnode,head->a.parentnodesymbol,head->a.isleafnode,head->a.nodesymbol);
	else
	{
		char shoot[30]="------------";
	fprintf (fp5,"1.%20s  2.%20d  3.%20s  4.%20s  5.%30s  6.%20s  7.%20s  \n", head->a.lexemecurrentnode,head->a.lineno,head->a.token,shoot,head->a.parentnodesymbol,head->a.isleafnode,head->a.nodesymbol);
	}
}

else
{
	if((strcmp(head->a.token,"TK_NUM")==0)||(strcmp(head->a.token,"TK_RNUM")==0))
   		 fprintf (fp5,"1.%20s  2.%20d  3.%20s  4.%20s  5.%30s  6.%20s  7.%20s  \n", go,head->a.lineno,head->a.token,head->a.lexemecurrentnode,head->a.parentnodesymbol,head->a.isleafnode,head->a.nodesymbol);
	else
	{
		char shoot[30]="------------";
	fprintf (fp5,"1.%20s  2.%20d  3.%20s  4.%20s  5.%30s  6.%20s  7.%20s  \n", go,head->a.lineno,head->a.token,shoot,head->a.parentnodesymbol,head->a.isleafnode,head->a.nodesymbol);
	}
}


}

void printParseTree(Treenode head, char *outfile)
{
   Treenode curr = head;
   FILE * fp5 = fopen(outfile,"w");
   fprintf(fp5,"LexemeCurrentNode \t lineno \t token \t valueIfNumber \t parentNodeSymbol \t isLeafNode(yes/no) \t NodeSymbol \n");
   postOrder(curr,fp5);


}
//=============================================================================================================================================

void deletenode(Treenode curr)
{
	Treenode f=curr->children;
	//printf("going to remove curr = %", f.
	curr->children = curr->children->children;
	Treenode t=curr->children;
	while(t->sibling!=NULL)
	{
		t->parent=curr;
		t=t->sibling;
	}
	free(f);
}

void removesinglenode(Treenode curr)
{
		//printf("hey it is printing2\n");
		//printf("curr=%s\n",curr->a.nodesymbol);
    if(curr->parent!=NULL)
	{
		if(curr->children!=NULL)
		{
			if((curr->children->children!=NULL)&&(curr->children->sibling==NULL))
			{
				deletenode(curr);
			}
				else if((curr->children->children!=NULL)&&(curr->children->sibling!=NULL))
			{
				curr=curr->children;
			}
			else if((curr->children->children==NULL)&&(curr->children->sibling!=NULL))
			{
				curr=curr->children;
			}
			else if((curr->children->children==NULL)&&(curr->children->sibling==NULL))
			{
				if(curr->sibling!=NULL)
				curr=curr->sibling;
				else
				curr=getoutast(curr);
			}

			removesinglenode(curr);
		}

		else
		{
			if(curr->sibling!=NULL)
			curr=curr->sibling;
			else if(curr->sibling==NULL)
			curr=getoutast(curr);

			removesinglenode(curr);
		}
    }
}
Treenode getoutast(Treenode curr)
{
	if(curr->parent!=NULL)
	{	if(curr->parent->sibling !=NULL)
		curr=curr->parent->sibling;
		else
		{
			curr=curr->parent;
			curr=getoutast(curr);
		}
	}

	//else
	//curr=curr->parent;
	return curr;

}
//===============================================================================================================
void removeendnode(Treenode curr)
{
	//printf("curr:::%s%s\n",curr->a.nodesymbol,curr->a.token);
	if(curr->parent!=NULL)
	{
		//printf("WHY AM I HERE\n");
		if(curr->children!=NULL)
		{
			curr=curr->children;
			removeendnode(curr);
		}
		else if(curr->children==NULL)
		{
			int x=isone(curr);
			if(x==1)
			{	Treenode tempor;
				tempor=deleteendnode(curr);
				curr=tempor;
				removeendnode(curr);
			}
			else
			{
				if(curr->sibling!=NULL)
				{
					curr=curr->sibling;
					removeendnode(curr);
				}
				else
				{
					curr=getoutast(curr);
					removeendnode(curr);
				}
			}
		}
	}

}

Treenode deleteendnode(Treenode curr)
{
	atom=1;
	//printf("deletednode:::%s%s\n",curr->a.nodesymbol,curr->a.token);
	if((curr==curr->parent->children) && (curr->sibling==NULL))
	{
		Treenode tempo;
		tempo=curr;
		curr->parent->children=NULL;
		curr=getoutast(curr);
		free(tempo);
	}
	else if((curr==curr->parent->children) && (curr->sibling!=NULL))
	{
		Treenode tempo=curr;
		curr->parent->children=curr->sibling;
		curr=curr->sibling;
		free(tempo);
	}
	else if((curr!=curr->parent->children) && (curr->sibling!=NULL))
	{
		Treenode fo,tempo;
		tempo=curr;
		fo=curr->parent->children;

		while(fo->sibling!=curr)
		fo=fo->sibling;

		fo->sibling=curr->sibling;
		curr=curr->sibling;

		free(tempo);
	}
	else if((curr!=curr->parent->children) && (curr->sibling==NULL))
	{
		Treenode fo,tempo;
		tempo=curr;
		fo=curr->parent->children;

		while(fo->sibling!=curr)
		fo=fo->sibling;

		curr=getoutast(curr);
		fo->sibling=NULL;

		free(tempo);
	}
	//printf("currafterdelete:::%s%s\n",curr->a.nodesymbol,curr->a.token);
	return curr;
}
int isone(Treenode curr)
{
	int t=0;
	if((strcmp(curr->a.token,"TK_COMMA")==0) || (strcmp(curr->a.token,"TK_SEM")==0) || (strcmp(curr->a.token,"TK_COLON")==0) || (strcmp(curr->a.token,"TK_CL")==0) || (strcmp(curr->a.token,"TK_OP")==0) || (strcmp(curr->a.token,"TK_SQR")==0) || (strcmp(curr->a.token,"TK_SQL")==0) || (strcmp(curr->a.token,"TK_TYPE")==0) || (strcmp(curr->a.token,"TK_CALL")==0) || (strcmp(curr->a.token,"TK_WITH")==0) || (strcmp(curr->a.token,"TK_IF")==0) || (strcmp(curr->a.token,"TK_THEN")==0) || (strcmp(curr->a.token,"TK_ELSE")==0) || (strcmp(curr->a.token,"TK_ENDIF")==0) || (strcmp(curr->a.token,"TK_WHILE")==0) || (strcmp(curr->a.token,"TK_ENDWHILE")==0) || (strcmp(curr->a.token,"TK_PARAMETER")==0) || (strcmp(curr->a.token,"TK_PARAMETERS")==0) || (strcmp(curr->a.nodesymbol,"eps")==0) )
	t=1;

	return t;

}
//===========================================================================================================================
void removevertical(Treenode curr)
{
	if(curr->parent!=NULL)
	{
		if(curr->children!=NULL)
		{
			curr=curr->children;
		}
		else
		{
			if(strcmp(curr->a.isleafnode,"No")==0)
			{
				curr=deleteendnode(curr);
				removevertical(curr);
			}
			else
			{
				if(curr->sibling!=NULL)
				{
					curr=curr->sibling;
					removeendnode(curr);
				}
				else
				{
					curr=getoutast(curr);
					removeendnode(curr);
				}
			}
		}
	}
}

//==========================================================================================================================

Treenode createAbstractSyntaxtree(Treenode head)
{
    Treenode curr=head->children;
	removeendnode(head->children);
	atom=1;
	while(atom==1)
	{
		atom=0;
		removevertical(head->children);
    		removesinglenode(head->children);
	}
	return head;
}

//==========================================================================================================================================================

/*
int main()
{

   FILE * fp1;//to be passed & declared in main
   FILE * fp2;//to be passed & declared in main
   FILE * fp3;//to be passed & declared in main

   int array[50][55];//to be passed & declared in main
   char grammar[90][150];

//--------------------initializing array with 0----------------------------------------
   int p,q;

  for(p=0; p<50;p++)
  {
    for(q=0;q<55;q++)
      array[p][q]=0;
  }
//------------------------array initialized---------------------------------------------



 fp1 = fopen("grammar.txt", "r");//to be opened in main and passed
 fp2 = fopen("first.txt", "r");//to be opened in main and passed
 fp3 = fopen("follow.txt", "r");//to be opened in main and passed

 if (fp1 == NULL)
 {
  printf("ERROR OPENING grammar.txt\n");
  exit(EXIT_FAILURE);
 }
 if (fp2 == NULL)
 {
  printf("ERROR OPENING first.txt\n");
  exit(EXIT_FAILURE);
 }
 if (fp3 == NULL)
 {
  printf("ERROR OPENING follow.txt\n");
  exit(EXIT_FAILURE);
 }


 createParseTable(fp1,fp2,fp3,array,grammar);


//printf("GRAMMAR::::::::::::::::::::::::::::::::::\n");

	//int bul=0;
	//for(bul=0;bul<90;bul++)
	//printf("%s\n",grammar[bul]);

 fclose(fp1);
 fclose(fp2);
 fclose(fp3);


//------------------------------------PARSE TREE---------------------------------------------


 fp1 = fopen("grammar.txt", "r");
 if (fp1 == NULL)
 {
   printf("ERROR:File grammar.txt(PARSE TREE) not opening\n");
   exit(EXIT_FAILURE);
 }
 Treenode headptr;
 headptr = createparsetree(fp1,array,grammar);


//printf("FINALLY\n");
//printf("HEAD :: %s\n",headptr->a.lexemecurrentnode);
//printf("children :: %s\n",headptr->children->a.lexemecurrentnode);
//printf("child sibling :: %s\n",headptr->children->sibling->a.lexemecurrentnode);
 //printf("child child :: %s\n",headptr->children->children->a.lexemecurrentnode);
//printf("chil child sibling :: %s\n",headptr->children->children->sibling->a.lexemecurrentnode);






 return 0;


}*/





