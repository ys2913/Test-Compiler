#include <stdio.h>

extern HashTable createsymboltable(Treenode head);
extern void dfs(Treenode head,HashTable ht1);
extern int findrecord(HashTable ht1,char str[100]);
extern void addrecord(Treenode head,HashTable ht1);
extern int hash (char s[], int size);
extern HashTable createHashTable (int size);
extern HashTable2 createHashTable2 (int size);
extern HashTable3 createHashTable3 (int size);
extern void insertElement (HashTable h, Element e);
extern void insertElement2 (HashTable2 h, Element2 e);
extern void insertElement3 (HashTable3 h, Element3 e);
extern void printsymboltable(HashTable ht1);
extern void dfs(Treenode head,HashTable ht1);

