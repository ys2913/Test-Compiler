typedef enum
{ EMPTY = 0, FILLED = 1 } Status;

typedef struct{
  char identifiername[30];
  char scope[30];
  char type[30];
  int offset;
} Element3;


typedef struct
{
  Element3 e3;
  Status status;
  int insertion_probes;
  int no_succ_probes;
  int no_unsucc_probes;
} Bucket3;

typedef struct
{
  Bucket3 *buckets3;
  int size;
} hashtable3;


typedef hashtable3 *HashTable3;


typedef struct{
  char identifiername[30];
  char scope[30];
  char type[30];
  int offset;
  HashTable3 ptr;
} Element2;


typedef struct
{
  Element2 e2;
  Status status;
  int insertion_probes;
  int no_succ_probes;
  int no_unsucc_probes;
} Bucket2;

typedef struct
{
  Bucket2 *buckets2;
  int size;
} hashtable2;


typedef hashtable2 *HashTable2;


typedef struct{
 char funcname[30];
 HashTable2 ptr;
} Element;



typedef struct
{
  Element e;
  Status status;
  int insertion_probes;
  int no_succ_probes;
  int no_unsucc_probes;
} Bucket;

typedef struct
{
  Bucket *buckets;
  int size;
} hashtable;

typedef hashtable *HashTable;


