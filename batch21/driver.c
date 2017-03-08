#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "stackops.h"
#include "parser.h"
#include "hashtable.h"
#include "symboltable.h"
#include "semantic.h"
#include <string.h>
/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/

int main(int argc, char*argv[]) // bufferSize value set constant as 10 in lexerDef.h  . Can be changed as per the instructor's wish.
{
	if(argc!=4)
	{
	   	printf("Insufficient arguments\n");
   		return 0;
	   }
	   FILE *fp;
	   fp=fopen("testcase.txt","r");
	   int c;
	   printf("\nEnter choice no.\n");
	   printf("\n1. Print all tokens \n");
	   printf("\n2. Check if grammar is syntactically correct or not and compute parse tree in output.txt\n");
	   printf("\n3. Compute Abstract Syntax Tree in out.txt \n");
	   printf("\n4. Create and print Symbol Table and compute Semantic errors \n");
           scanf("%d",&c);
      	   switch (c)
		{
			case 1:
			{
			fp=getStream(fp,B,k);
			int j=0;
			int f=0;
			tokenInfo test;
			if(fp!=NULL)
			printf("Printing Tokens : \n");
			while(test.flaglex!=1)
			{
				f=0;
				//printf("flaglex is %d \n",flaglex);
				test=getNextToken(fp,f);
				if(test.flaglex==0)
				{
					printf("\n%s in line no. : %d and lexeme name %s \n",test.tokenName,test.lineNo, test.lexName);
				}
				else
					printf("\nEnd of file \n");
			}
			fclose(fp);
			break;
			}
			case 2:
			{

  				 FILE * fp1;//to be passed & declared in main
  				 FILE * fp2;//to be passed & declared in main
  				 FILE * fp3;//to be passed & declared in main

   				int array[50][55];//to be passed & declared in main
   				char grammar[90][150];

 				int p,q;
 				 for(p=0; p<50;p++)
   					 for(q=0;q<55;q++)
					 	array[p][q]=0;


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

 				fp1 = fopen("grammar.txt", "r");
 				if (fp1 == NULL)
 				{
   					printf("ERROR:File grammar.txt(PARSE TREE) not opening\n");
 					  exit(EXIT_FAILURE);
 				}
 				Treenode headptr,headptr2;
				fp=fopen(argv[1],"r");
 				headptr = createparsetree(fp,array,grammar);
				Treenode temp1=headptr;
				//getchar();
				printParseTree(headptr, argv[2]);
				//HashTable ht1;
				//printf("\n HeadBLAH = %s",headptr->a.nodesymbol);
				//printf("\n ChildrenBLAH = %s \n",headptr->children->a.lexemecurrentnode);
				//headptr2 = createAbstractSyntaxtree(headptr);
				//printf("head111:::%s\n",headptr2->a.nodesymbol);
				//printParseTree(headptr2, argv[3]);
				break;
			}
			case 3:
				{
				 FILE * fp1;//to be passed & declared in main
  				 FILE * fp2;//to be passed & declared in main
  				 FILE * fp3;//to be passed & declared in main

   				int array[50][55];//to be passed & declared in main
   				char grammar[90][150];

 				int p,q;
 				 for(p=0; p<50;p++)
   					 for(q=0;q<55;q++)
					 	array[p][q]=0;


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

 				fp1 = fopen("grammar.txt", "r");
 				if (fp1 == NULL)
 				{
   					printf("ERROR:File grammar.txt(PARSE TREE) not opening\n");
 					  exit(EXIT_FAILURE);
 				}
 				Treenode headptr,headptr2;
				fp=fopen(argv[1],"r");
 				headptr = createparsetree(fp,array,grammar);
				Treenode temp1=headptr;
				//getchar();
				printParseTree(headptr, argv[2]);
				headptr2 = createAbstractSyntaxtree(headptr);
				printf("\nABSTRACT TREE COMPUTED \n");
				printParseTree(headptr2, argv[3]);
				
				break;
				}
			case 4:
				{
				
  				 FILE * fp1;//to be passed & declared in main
  				 FILE * fp2;//to be passed & declared in main
  				 FILE * fp3;//to be passed & declared in main

   				int array[50][55];//to be passed & declared in main
   				char grammar[90][150];

 				int p,q;
 				 for(p=0; p<50;p++)
   					 for(q=0;q<55;q++)
					 	array[p][q]=0;


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

 				fp1 = fopen("grammar.txt", "r");
 				if (fp1 == NULL)
 				{
   					printf("ERROR:File grammar.txt(PARSE TREE) not opening\n");
 					  exit(EXIT_FAILURE);
 				}
 				Treenode headptr,headptr2;
				fp=fopen(argv[1],"r");
 				headptr = createparsetree(fp,array,grammar);
				Treenode temp1=headptr;
				//getchar();
				printParseTree(headptr, argv[2]);
				HashTable ht1;
				//printf("\n HeadBLAH = %s",headptr->a.nodesymbol);
				//printf("\n ChildrenBLAH = %s \n",headptr->children->a.lexemecurrentnode);
				//headptr2 = createAbstractSyntaxtree(headptr);
				//printf("head111:::%s\n",headptr2->a.nodesymbol);
				//printParseTree(headptr2, argv[3]);
				ht1=createsymboltable(headptr);
				recursiveerror(headptr);
				typechecker(headptr,ht1);
				break;
				}

			default:
				printf("\n Wrong Choice, Enter Again. \n");

		}
	return 0;
}



