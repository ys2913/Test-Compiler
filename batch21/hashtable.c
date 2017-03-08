#include "hashtable.h"
#include <stdlib.h>



HashTable createHashTable (int size)
{
  HashTable ht;
  int i;
  ht = (HashTable) malloc (sizeof (hashtable));
  ht->buckets = (Bucket *) malloc (size * sizeof (Bucket));
  if (ht->buckets == NULL)
    {
      perror ("malloc:");
      return NULL;
    }
  for (i = 0; i < size; i++)
    {

      ht->buckets[i].status = EMPTY;
      ht->buckets[i].no_succ_probes = 0;
      ht->buckets[i].no_unsucc_probes = 0;
      ht->buckets[i].insertion_probes = 0;
    }

  ht->size = size;
  return ht;
}

HashTable2 createHashTable2 (int size)
{
  HashTable2 ht2;
  int i;
  ht2 = (HashTable2) malloc (sizeof (hashtable2));
  ht2->buckets2 = (Bucket2 *) malloc (size * sizeof (Bucket2));
  if (ht2->buckets2 == NULL)
    {
      perror ("malloc:");
      return NULL;
    }
  for (i = 0; i < size; i++)
    {

      ht2->buckets2[i].status = EMPTY;
      ht2->buckets2[i].no_succ_probes = 0;
      ht2->buckets2[i].no_unsucc_probes = 0;
      ht2->buckets2[i].insertion_probes = 0;
    }

  ht2->size = size;
  return ht2;
}

/*
int quadraticProbe(HashTable h,Element e)
{
	int h,hp;
	int i=0;
	int c1=3,c2=5;

	
	int emptySlotfound=0;
	h=hash(e.filename,h->size);
	while((i<h->size)&&(emptySlotfound==0))
	{
		hp=(h+c1*i+c2*i*i)%size;
		if(h[hp].status==EMPTY)
		{
			emptySlotfound=1;
			return hp;
		}
		else
			i++;
	}
return -1;
}
*/

void insertElement (HashTable h, Element e)
{
  int hashvalue, i, j, l;
  int c1 = 3, c2 = 5;
  l = hash (e.funcname, h->size);
  i = 0;
  do
    {
      j = (l + c1 * i + c2 * i * i) % h->size;
      if (h->buckets[j].status == EMPTY)
	{
	  h->buckets[j].status = FILLED;
	  h->buckets[j].e = e;
	  h->buckets[j].insertion_probes =
	    h->buckets[j].insertion_probes + i + 1;
	  return;
	}
      else
	i = i + 1;
    }
  while (i < h->size);
  printf ("Hashtable overflow");
}


void insertElement2 (HashTable2 h, Element2 e)
{
  int hashvalue, i, j, l;
  int c1 = 3, c2 = 5;
  l = hash (e.identifiername, h->size);
  i = 0;
  do
    {
      j = (l + c1 * i + c2 * i * i) % h->size;
      if (h->buckets2[j].status == EMPTY)
	{
	  h->buckets2[j].status = FILLED;
	  h->buckets2[j].e2 = e;
	  h->buckets2[j].insertion_probes =
	    h->buckets2[j].insertion_probes + i + 1;
	  return;
	}
      else
	i = i + 1;
    }
  while (i < h->size);
  printf ("Hashtable overflow");
}



Result
findElement (HashTable h, char filename[])
{
  Result r;
  int hashvalue, i, j, l;
  int c1 = 3, c2 = 5;
  l = hash (filename, h->size);
  i = 0;
  do
    {
      j = (l + c1 * i + c2 * i * i) % h->size;
      if (h->buckets[j].status == FILLED
	  && strcmp (h->buckets[j].e.filename, filename) == 0)
	{
	  h->buckets[j].no_succ_probes = h->buckets[j].no_succ_probes + i + 1;
	  r.error = 0;
	  r.e = h->buckets[j].e;
	  return r;
	}
      else
	i = i + 1;
    }
  while (h->buckets[j].status != EMPTY && i < h->size);
  r.error = 1;
  h->buckets[j].no_unsucc_probes = h->buckets[j].no_unsucc_probes + i;
  return r;
}
