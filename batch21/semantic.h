#include <stdio.h>
#include "typeextractorDef.h"
#include <string.h>
extern type dfsassign(Treenode head,type rhs,char * string,HashTable ht1);
extern void typechecker(Treenode head,HashTable ht1);
extern type isinglobal(Treenode current,HashTable ht1);

extern void ismatch(Treenode head,char red[30]);
extern void recursiveerror(Treenode head);
extern int functionoverloaderror(HashTable ht1);
//extern type dfsif(Treenode head,type typeif,char * string,HashTable ht1);
