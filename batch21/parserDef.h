/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/


typedef struct
{
 char lexemecurrentnode[100];
 int lineno;
 char token[20];
 float valueifnumber;
 char parentnodesymbol[30];
 char isleafnode[3];
 char nodesymbol[30];

}printing;


typedef struct treenode * Treenode;

 struct treenode
{
 int noofchildren;
 int posofchildren;
 Treenode children;
 Treenode sibling;
 Treenode parent;
 printing a;

};

//================================================
/*typedef struct
{
    int offsetno;
    char blah[50];
}values;
*/
