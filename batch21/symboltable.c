#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "parser.h"
#include "hashtable.h"
#include "symboltable.h"

char random123[30]="";
int offset=0;
int globaloffset=0;


int hash (char s[], int size)
{
  double A = 0.6180339887;
  int a = 41;
  int i;
  long sum = s[0];
  for (i = 1; s[i] != '\0'; i++)
    {
      sum = s[i] + a * sum;
//              printf("=========i=%d %c %d %d\n",i, s[i], s[i],sum);

      int z = (int) sum * A;
      sum = (sum * A - z) * size;
      //xk-1 + a(xk-2 + a(xk-3 + ... + a(x2 + a(x1 + ax0)) ... ))

    }
  return sum;
}

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

HashTable3 createHashTable3 (int size)
{
  HashTable3 ht3;
  int i;
  ht3 = (HashTable3) malloc (sizeof (hashtable3));
  ht3->buckets3 = (Bucket3 *) malloc (size * sizeof (Bucket3));
  if (ht3->buckets3 == NULL)
    {
      perror ("malloc:");
      return NULL;
    }
  for (i = 0; i < size; i++)
    {

      ht3->buckets3[i].status = EMPTY;
      ht3->buckets3[i].no_succ_probes = 0;
      ht3->buckets3[i].no_unsucc_probes = 0;
      ht3->buckets3[i].insertion_probes = 0;
    }

  ht3->size = size;
  return ht3;
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


void insertElement3 (HashTable3 h, Element3 e)
{
  int hashvalue, i, j, l;
  int c1 = 3, c2 = 5;
  l = hash (e.identifiername, h->size);
  i = 0;
  do
    {
      j = (l + c1 * i + c2 * i * i) % h->size;
      if (h->buckets3[j].status == EMPTY)
	{
	  h->buckets3[j].status = FILLED;
	  h->buckets3[j].e3 = e;
	  h->buckets3[j].insertion_probes =
	    h->buckets3[j].insertion_probes + i + 1;
	  return;
	}
      else
	i = i + 1;
    }
  while (i < h->size);
  printf ("Hashtable overflow");
}



//==========================================================================================================================================================

int findrecord(HashTable ht1,char str[100])
{
    int d;
			
    int gone=0;
    while(strcmp(ht1->buckets[gone].e.funcname,"global")!=0)
    gone++;
	//printf("check6%s\n",str);
	//printf("check7%s\n",ht1->buckets[gone].e.funcname);
	
    int found=0;
    while(strcmp(ht1->buckets[gone].e.ptr->buckets2[found].e2.identifiername,str)!=0)
    found++;
	//printf("check8%s\n",ht1->buckets[gone].e.ptr->buckets2[found].e2.identifiername);
    d=ht1->buckets[gone].e.ptr->buckets2[found].e2.offset;
	//printf("D+++%d",d);
    return d;

}

void addrecord(Treenode head,HashTable ht1)
{
    Treenode curr=NULL;
    if(head->children!=NULL)
    {

        addrecord(head->children,ht1);
        curr=head->children;
        while(curr->sibling!=NULL)
        {
            addrecord(curr->sibling,ht1);
            curr=curr->sibling;
        }
    }

    if((strcmp(head->a.token,"TK_RECORDID")==0) && (strcmp(head->parent->a.lexemecurrentnode,"<typeDefinition>")==0))
    {
	//printf("RECORD ADDED %s\n",head->a.lexemecurrentnode);//========
        int dogy=0;
        while(strcmp(ht1->buckets[dogy].e.funcname,"global")!=0)
        dogy++;
	//printf("FUNCTION %s\n",ht1->buckets[dogy].e.funcname);//========
        Element2 e2;
        strcpy(e2.identifiername,head->a.lexemecurrentnode);
        strcpy(e2.scope,"global");
        strcpy(e2.type,"record");
        e2.offset=0;
        e2.ptr=createHashTable3(60);
        int last=0;
	insertElement2 (ht1->buckets[dogy].e.ptr, e2);
        Treenode current;
        current=head->sibling->children->children->sibling->sibling->sibling;
	//printf("identifier %s\n",e2.identifiername);//========
        Element3 e31;
        strcpy(e31.identifiername,current->a.lexemecurrentnode);
	//printf("type %s\n",current->parent->children->sibling->children->a.lexemecurrentnode);//========
        strcpy(e31.scope,"NA");
        strcpy(e31.type,current->parent->children->sibling->children->a.lexemecurrentnode);

        if(strcmp(current->parent->children->sibling->children->a.token,"TK_INT")==0)
        {
            e31.offset=2;
            last=last+2;
        }
        else if(strcmp(current->parent->children->sibling->children->a.token,"TK_REAL")==0)
        {
            e31.offset=4;
            last=last+4;
        }
	//printf("last=%d\n",last);

        insertElement3(e2.ptr,e31);
        current=current->parent->sibling->children->sibling->sibling->sibling;


        Element3 e32;
        strcpy(e32.identifiername,current->a.lexemecurrentnode);
        strcpy(e32.scope,"NA");
        strcpy(e32.type,current->parent->children->sibling->children->a.lexemecurrentnode);

        if(strcmp(current->parent->children->sibling->children->a.token,"TK_INT")==0)
        {
            e32.offset=2;
            last=last+2;
        }
        else if(strcmp(current->parent->children->sibling->children->a.token,"TK_REAL")==0)
        {
            e32.offset=4;
            last=last+4;
        }

        insertElement3(e2.ptr,e32);

        while(strcmp(current->parent->sibling->children->a.lexemecurrentnode,"eps")!=0)
        {
            current=current->parent->sibling->children->children->sibling->sibling->sibling;


            Element3 e33;
            strcpy(e33.identifiername,current->a.lexemecurrentnode);
            strcpy(e33.scope,"NA");
            strcpy(e33.type,current->parent->children->sibling->children->a.lexemecurrentnode);

            if(strcmp(current->parent->children->sibling->children->a.token,"TK_INT")==0)
            {
                e33.offset=2;
                last=last+2;
            }
            else if(strcmp(current->parent->children->sibling->children->a.token,"TK_REAL")==0)
            {
                e33.offset=4;
                last=last+4;
            }

            insertElement3(e2.ptr,e33);
        }

        int final=0;
        while(strcmp(ht1->buckets[dogy].e.ptr->buckets2[final].e2.identifiername,head->a.lexemecurrentnode)!=0)
        final++;

        ht1->buckets[dogy].e.ptr->buckets2[final].e2.offset=last;

    }
}
//===========================================================================================================================================================
void dfs(Treenode head,HashTable ht1)
{
    Treenode curr=NULL;
    if(head->children!=NULL)
    {

        dfs(head->children,ht1);
        curr=head->children;
        while(curr->sibling!=NULL)
        {
            dfs(curr->sibling,ht1);
            curr=curr->sibling;
        }
    }
   if( ((strcmp(head->a.token,"TK_FUNID")==0) && (head==head->parent->children)) || (strcmp(head->a.token,"TK_MAIN")==0))
   {
       Element e;
       e.ptr=createHashTable2(100);
       strcpy(e.funcname,head->a.lexemecurrentnode);
       strcpy(random123,head->a.lexemecurrentnode);
       offset=0;
	int gone=0;
	int flagcheck=0;
	for(gone=0;gone<50;gone++)
	{
		if(ht1->buckets[gone].status==1)
		{
			if(strcmp(ht1->buckets[gone].e.funcname,e.funcname)==0)
			{
				flagcheck=1;
			}
		}
	}
	
	if(flagcheck==0)			
        insertElement(ht1,e);
	else
	{
		printf("ERROR FUNCTION OVERLOAD for %s\n",e.funcname);	
	}

   }


   if((strcmp(head->a.token,"TK_ID")==0) && (strcmp(head->parent->a.lexemecurrentnode,"<declaration>")==0))
   {
    //curr->parent->children->sibling->children->children->a.token
        if((strcmp(head->parent->children->sibling->children->children->a.token,"TK_INT")==0) || (strcmp(head->parent->children->sibling->children->children->a.token,"TK_REAL")==0))
        {
            if(strcmp(head->sibling->children->a.lexemecurrentnode,"eps")==0)
            {

                int joke=0;
                while(strcmp(random123,ht1->buckets[joke].e.funcname)!=0)
                joke++;
                Element2 e2;
                strcpy(e2.identifiername,head->a.lexemecurrentnode);
                strcpy(e2.scope,random123);
                strcpy(e2.type,head->parent->children->sibling->children->children->a.lexemecurrentnode);
		e2.offset=offset;
                if(strcmp(head->parent->children->sibling->children->children->a.token,"TK_INT")==0)
                offset=offset+2;
                else if(strcmp(head->parent->children->sibling->children->children->a.token,"TK_REAL")==0)
                offset=offset+4;

                
                e2.ptr=NULL;
                insertElement2(ht1->buckets[joke].e.ptr,e2);
            }
            else
            {
                int joke=0;
                while(strcmp(ht1->buckets[joke].e.funcname,"global")!=0)
                joke++;
                Element2 e2;
                strcpy(e2.identifiername,head->a.lexemecurrentnode);
                strcpy(e2.scope,"global");
                strcpy(e2.type,head->parent->children->sibling->children->children->a.lexemecurrentnode);

                if(strcmp(head->parent->children->sibling->children->children->a.token,"TK_INT")==0)
                globaloffset=globaloffset+2;
                else if(strcmp(head->parent->children->sibling->children->children->a.token,"TK_REAL")==0)
                globaloffset=globaloffset+4;

                e2.offset=0;
                e2.ptr=NULL;
                insertElement2(ht1->buckets[joke].e.ptr,e2);

            }
        }

        else
        {	//printf("check2\n");
            if(strcmp(head->parent->children->sibling->children->children->sibling->a.token,"TK_RECORDID")==0)
            {	//printf("check3\n");
                int joke=0;
                while(strcmp(ht1->buckets[joke].e.funcname,random123)!=0)
                joke++;
		//printf("check4%s\n",ht1->buckets[joke].e.funcname);
		//printf("check5%s\n",head->a.lexemecurrentnode);
                Element2 e2;
                strcpy(e2.identifiername,head->a.lexemecurrentnode);
                strcpy(e2.scope,random123);
                strcpy(e2.type,head->parent->children->sibling->children->children->sibling->a.lexemecurrentnode);
                int d=0;
		//printf("check6%s\n",head->parent->children->sibling->children->children->sibling->a.lexemecurrentnode);
                d=findrecord(ht1,head->parent->children->sibling->children->children->sibling->a.lexemecurrentnode);

		e2.offset=offset;                
		offset=offset+d;
                
		insertElement2(ht1->buckets[joke].e.ptr,e2);

            }
        }

   }


   else if((strcmp(head->a.token,"TK_ID")==0) && (strcmp(head->parent->a.lexemecurrentnode,"<parameter_list>")==0))
   {

	//printf("check2\n");
		 if((strcmp(head->parent->children->children->children->a.token,"TK_INT")==0) || (strcmp(head->parent->children->children->children->a.token,"TK_REAL")==0))
        {
           
            

                int joke=0;
                while(strcmp(random123,ht1->buckets[joke].e.funcname)!=0)
                joke++;
                Element2 e2;
                strcpy(e2.identifiername,head->a.lexemecurrentnode);
                strcpy(e2.scope,random123);
                strcpy(e2.type,head->parent->children->children->children->a.lexemecurrentnode);
				e2.offset=offset;
                if(strcmp(head->parent->children->children->children->a.token,"TK_INT")==0)
                offset=offset+2;
                else if(strcmp(head->parent->children->children->children->a.token,"TK_REAL")==0)
                offset=offset+4;
                
                e2.ptr=NULL;
                insertElement2(ht1->buckets[joke].e.ptr,e2);
            
            
        }
		
		else
        {	//printf("check2\n");
            if(strcmp(head->parent->children->children->children->sibling->a.token,"TK_RECORDID")==0)
            {	//printf("check3\n");
                int joke=0;
                while(strcmp(ht1->buckets[joke].e.funcname,random123)!=0)
                joke++;
		//printf("check4%s\n",ht1->buckets[joke].e.funcname);
		//printf("check5%s\n",head->a.lexemecurrentnode);
                Element2 e2;
                strcpy(e2.identifiername,head->a.lexemecurrentnode);
                strcpy(e2.scope,random123);
                strcpy(e2.type,head->parent->children->children->children->sibling->a.lexemecurrentnode);
                int d=0;
		//printf("check6%s\n",head->parent->children->sibling->children->children->sibling->a.lexemecurrentnode);
                d=findrecord(ht1,head->parent->children->children->children->sibling->a.lexemecurrentnode);

				e2.offset=offset;                
				offset=offset+d;
                
				insertElement2(ht1->buckets[joke].e.ptr,e2);

            }
        }
   }
   



}
void printsymboltable(HashTable ht1)
{
    printf("\t\tidentifiername\t\t\t\t scope\t\t\t\t offset\t\t\t\t type\n\n");
    int i=0;
    int j=0;
    int k=0;
    for(i=0;i<50;i++)
    {
        if(ht1->buckets[i].status==1)
        {
            for(j=0;j<100;j++)
            {
                if(ht1->buckets[i].e.ptr->buckets2[j].status==1)
                {	
					if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.type,"record")!=0)
					{
						printf("%30s %30s %30d %30s \n",ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,ht1->buckets[i].e.ptr->buckets2[j].e2.scope,ht1->buckets[i].e.ptr->buckets2[j].e2.offset,ht1->buckets[i].e.ptr->buckets2[j].e2.type);
					}
					
					else
					{
						int hot=0;
						printf("%30s %30s %30d \t \t \t ",ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,ht1->buckets[i].e.ptr->buckets2[j].e2.scope,ht1->buckets[i].e.ptr->buckets2[j].e2.offset);
						for(hot=0;hot<100;hot++)
						{
							if(ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[hot].status==1&&(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[hot].e3.type,"int")==0||strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[hot].e3.type,"real")==0))
							{
								printf("%s *",ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[hot].e3.type);
								
							}
						}
						printf("\n");
					}
					
					
				}
		
/*
				if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.type,"record")==0)
				{
				printf("\nHASHTABLE 3 START:::::\n");
			
				for(k=0;k<60;k++)
				{
					if(ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].status==1)
					{

					printf("%30s %30s %30s %30d\n",ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.identifiername,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.scope,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.type,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.offset);
					}                	
				}
				printf("\nHASHTABLE 3 END:::::::\n");
				}



				if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.type[0]),"#"==0)
				{
				for(k=0
				printf("%30s %30s %30s %30d\n",ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,ht1->buckets[i].e.ptr->buckets2[j].e2.scope,ht1->buckets[i].e.ptr->buckets2[j].e2.type,ht1->buckets[i].e.ptr->buckets2[j].e2.offset);
				}*/
            }
        }
    }
}
HashTable createsymboltable(Treenode head)
{
    HashTable ht1;
	//printf("check1\n");
    ht1=createHashTable(50);
    Element e;
    strcpy(e.funcname,"global");
    e.ptr=createHashTable2(100);
    insertElement(ht1,e);
    addrecord(head,ht1);
    dfs(head,ht1);

    printsymboltable(ht1);
   /* int i=0;
    for(i=0;i<50;i++)
    {
      if(ht1->buckets[i].status == 1)
      printf("FUNCTION:::::%s     NO.%d\n",ht1->buckets[i].e.funcname,i);
    }*/

return ht1;
}

