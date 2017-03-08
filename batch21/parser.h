#include "parserDef.h"
#include <stdio.h>


/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/

extern Treenode create();
extern void createParseTable(FILE *fp1,FILE *fp2,FILE *fp3,int array[50][55],char grammar[90][150]);
extern int getrowno2(char *buffer);
extern int getcolno(char *buffer2);
extern Treenode createparsetree(FILE *fp,int array[50][55],char grammar[90][150]);
extern void postOrder(Treenode head, FILE * fp5);
extern void printParseTree(Treenode head, char *outfile);
extern Treenode getout(Treenode curr);
extern Treenode createAbstractSyntaxtree(Treenode head);
extern Treenode getoutast(Treenode curr);
extern void deletenode(Treenode curr);
extern void removesinglenode(Treenode curr);
extern void removeendnode(Treenode curr);
extern Treenode deleteendnode(Treenode curr);
extern int isone(Treenode curr);
extern void removevertical(Treenode curr);
