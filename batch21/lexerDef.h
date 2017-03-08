/*
Karan Chauhan - 2010A7PS079P
Yash Sadhwani - 2010A7PS155P
Batch : 21
*/
typedef unsigned int buffersize;
#define bufferSize 10
typedef char buffer[bufferSize];

typedef struct{
    char tokenName[20];
    int lineNo;
    char lexName[30];
    int flaglex;
    int err;
    }tokenInfo;

static int ln=1;   
buffer B;
static int k=bufferSize;
static int i=0;
static int state=0;
//static int flaglex; //to specify end of file
FILE *fp;
