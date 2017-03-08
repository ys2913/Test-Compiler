/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/
#include"stack.h"
//#include "element.h"
//#include "boolean.h"
typedef enum { TRUE , FALSE}boolean;
struct stacknode;
typedef struct stacknode Stacknode;
typedef Stacknode *Stacklink;
struct stacknode
{
	char tok[50];
	Stacklink next;
};

typedef struct
{
	int size;
	Stacklink top;
    boolean error;
}Stackhead;
