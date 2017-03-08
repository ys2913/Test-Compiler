#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"
#include "parser.h"
#include "semantic.h"
int fin=0;
char string[30]="";
char arr[50][50];
void ismatch(Treenode head,char red[30])
{	//printf(" ALL GOOD HERE %s\n",red);

	while((strcmp(head->a.lexemecurrentnode,"<function>")!=0))// || (strcmp(head->a.lexemecurrentnode,"<mainFunction>")!=0) )
	{
	head=head->parent;
	if((strcmp(head->a.lexemecurrentnode,"<mainFunction>")==0))
	break;
	//printf(" ALL::::::%s\n",head->a.lexemecurrentnode);
	}
	//printf(" ALL GOOD HERE %s\n",head->a.lexemecurrentnode);
	head=head->children;
	
	if(strcmp(head->a.lexemecurrentnode,red)==0)
	{
		printf("ERROR::: Function %s called recursively\n",red);
	}
	
}

void recursiveerror(Treenode head)
{
	Treenode curr=NULL;
    if(head->children!=NULL)
    {

        recursiveerror(head->children);
        curr=head->children;
        while(curr->sibling!=NULL)
        {
            recursiveerror(curr->sibling);
            curr=curr->sibling;
        }
    }
	
	if(strcmp(head->a.token,"TK_CALL")==0)
	{
		char red[30]="";
		//printf(" ALL GOOD HERE %s\n",head->sibling->a.lexemecurrentnode);
		strcpy(red,head->sibling->a.lexemecurrentnode);
		ismatch(head,red);
	}

}


type dfsassign(Treenode head,type rhs,char * string,HashTable ht1)
{
	Treenode temp=NULL;
	if(head->children!=NULL)
	{
		rhs=dfsassign(head->children,rhs,string, ht1);
		temp=head->children->sibling;
	}
	while(temp !=NULL)
	{
		rhs=dfsassign(temp,rhs,string,ht1);
		temp=temp->sibling;
	}
	Treenode curr=head;
	/*if(strcmp(curr->a.token,"TK_ID")==0&&strcmp(curr->parent->a.lexemecurrentnode,"<declaration>")==0)
	{
		strcpy(x.varname,curr->a.lexemecurrentnode);
		curr=curr->parent;
		curr=curr->children;
		curr=curr->sibling;
		curr=curr->children;
		curr=curr->children;
		strcpy(x.datatype,curr->a.lexemecurrentnode);
	}*/
	//printf("\nrhsflag = %d\n",rhs.typeflag);
	//printf("\n token name = %s \n",curr->a.token);

	if(strcmp(curr->a.token,"TK_NUM")==0)
	{
		if(rhs.typeflag==1)
			rhs.error=1;
	}
	if(strcmp(curr->a.token,"TK_RNUM")==0)
	{
		if(rhs.typeflag==0)
			rhs.error=1;
	}

	if(strcmp(curr->a.token,"TK_ID")==0)
	{	
		int i=0;
		int j=0;
		type x;
		x=isinglobal(curr,ht1);
		if(x.gflag==0)
		{
		for(i=0;i<100;i++)
		{
			if(ht1->buckets[i].status==1)
			{
				if(strcmp(ht1->buckets[i].e.funcname,string)==0)
				{
					for(j=0;j<100;j++)
					{
						if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,curr->a.lexemecurrentnode)==0)
						{	
							strcpy(x.varname,curr->a.lexemecurrentnode);
							strcpy(x.datatype,ht1->buckets[i].e.ptr->buckets2[j].e2.type);	
						}
					}
				}
			}
		}
		}
		//printf("\n x.datatype = %s",x.datatype);
		//printf("\n x.varname = %s",x.varname);
		//break;
		//x=check value from symbol table to find datatype corresponding to x 			
		if(strcmp(x.datatype,"int")==0 && rhs.typeflag==1)
			rhs.error=1;
		if(strcmp(x.datatype,"real")==0 && rhs.typeflag==0)
			rhs.error=1;
	}
	return rhs;
	
		
}

void dfsfun(Treenode head, HashTable ht1)
{
	Treenode temp=NULL;
	if(head->children!=NULL)
	{
		dfsfun(head->children,ht1);
		temp=head->children->sibling;
	}
	while(temp !=NULL)
	{
		dfsfun(temp,ht1);
		temp=temp->sibling;
	}
	Treenode curr=head;
	if(strcmp(curr->a.token,"TK_CALL")==0&&strcmp(curr->sibling->a.lexemecurrentnode,string)==0)
	{
		if(strcmp(curr->parent->children->children->a.lexemecurrentnode,"eps")!=0)
			printf("\n ERROR : The function %s not invoked properly\n",string);
	}
}
void typechecker(Treenode head,HashTable ht1)
{
	int fin=0;
	Treenode temp=NULL;
	if(head->children!=NULL)
	{
		typechecker(head->children,ht1);
		temp=head->children->sibling;
	}
	while(temp !=NULL)
	{
		typechecker(temp,ht1);
		temp=temp->sibling;
	}
	type x;
	Treenode curr=head;
	Treenode current=head;
	if(strcmp(curr->a.token,"TK_MAIN")==0)
	{
		fin=0;
		strcpy(string,curr->a.lexemecurrentnode);
		//printf("current function is %s",string);
	}	
	if(strcmp(curr->a.token,"TK_FUNID")==0 && strcmp(curr->parent->a.lexemecurrentnode,"<funCallStmt>")==0)
	{
		int had=0;
		int verify=0;
		for(had=0;had<50;had++)
		{
			if(ht1->buckets[had].status==1)
			{
				if(strcmp(ht1->buckets[had].e.funcname,curr->a.lexemecurrentnode)==0)
				{
					verify=1;
				}
			}
		}
		if(verify==0)
		{
			printf("\nERROR CALLED FUNCTION %s NOT DEFINED\n",curr->a.lexemecurrentnode);
		}		
	}
	if(strcmp(curr->a.token,"TK_FUNID")==0&&strcmp(curr->parent->a.lexemecurrentnode,"<function>")==0)
	{
		strcpy(string,curr->a.lexemecurrentnode);
		//printf("current function 123::::::::: is %s\n",string);
		if(strcmp(curr->sibling->sibling->children->a.lexemecurrentnode,"eps")==0)
			{
			dfsfun(curr->parent->parent->parent,ht1);
			}		
		
	}
	
//=========================================================================================================
	if(strcmp(curr->a.token,"TK_ID")==0)
	{
		//printf("\nlex name %s \n",current->a.lexemecurrentnode);
		int i=0;
		int j=0;
		int cnt=0;
		int gf=0;
		type z=isinglobal(current,ht1);
		for(i=0;i<100;i++)
		{
			if(ht1->buckets[i].status==1)
			{	//printf("current function is %s",string);
				if(strcmp(ht1->buckets[i].e.funcname,string)==0)
				{
					for(j=0;j<100;j++)
					{
						if(ht1->buckets[i].e.ptr->buckets2[j].status==1)
						{
						if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,current->a.lexemecurrentnode)==0)
						{
							cnt++;
							//printf("\ncount= %d for identifier %s\n",cnt,current->a.lexemecurrentnode);
						}
						}
					}
				}
			}
		}
		
		//printf("\n Value of cnt = %d and Value of z.count =%d \n",cnt,z.count);
		//getchar();
		if(cnt>1)
			printf("\n Line %d : The identifier <%s> is declared more than once. \n",current->a.lineno,current->a.lexemecurrentnode);
		if(z.count>1&&fin==0)
			{fin=1;
			printf("\n line %d : Variable %s being a global variable, cannot be declared more than once. \n",current->a.lineno,current->a.lexemecurrentnode);
			}
		if(cnt==0&&z.count==0)
			printf("\n line %d : variable %s is not declared with its scope of %s \n",current->a.lineno,current->a.lexemecurrentnode,string);
		/*if(z.count!=0&&cnt!=0)
			printf("\n Identifier %s declared globally, so cannot be declared again here\n",current->a.lexemecurrentnode);
		*/	
	}

//=========================================================================================================
	if(strcmp(curr->a.token,"TK_ASSIGNOP")==0&&strcmp(curr->parent->a.lexemecurrentnode,"<assignmentStmt>")==0)
	{
		type lhs;
		type rhs;
		rhs.error=0;
		//printf("\ncurrent function is %s\n",string);
		current=current->parent->children->children;
		if(strcmp(current->sibling->children->a.lexemecurrentnode,"eps")!=0)
		{
			int i=0,j=0,k=0;
			current=current->sibling->children->sibling;
			//printf("\n yo = %s \n",current->a.lexemecurrentnode);
		        for(i=0;i<50;i++)
   			{
        			if(ht1->buckets[i].status==1)
       			        {
       		        	     for(j=0;j<100;j++)
      			 	     {
      			             if(ht1->buckets[i].e.ptr->buckets2[j].status==1)
                		     {
					if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.type,"record")==0)
					{
						for(k=0;k<60;k++)
						{
						if(ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].status==1)
						{
						if(strcmp(current->a.lexemecurrentnode,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.identifiername)==0)
						{
						strcpy(lhs.varname,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.identifiername);
						strcpy(lhs.datatype,ht1->buckets[i].e.ptr->buckets2[j].e2.ptr->buckets3[k].e3.type);
						}
						}
						}
					}
				     }
				     }
				}                	
			}
		}

			
		else
		{
		lhs=isinglobal(current,ht1);
		/*if(lhs.count>1)
			printf("\n Variable declared more than once");
		*/
		/*if(lhs.gflag==1)
			printf("\n Global identifier : %s \n",current->a.lexemecurrentnode);
		*/if(lhs.gflag==0)
		{
		int i=0;
		int j=0;
		for(i=0;i<100;i++)
		{
			if(ht1->buckets[i].status==1)
			{	//printf("current function is %s",string);
				if(strcmp(ht1->buckets[i].e.funcname,string)==0)
				{
					for(j=0;j<100;j++)
					{
						//printf("\nlex name %s \n",current->a.lexemecurrentnode);
						if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,current->a.lexemecurrentnode)==0)
						{
							strcpy(lhs.varname,current->a.lexemecurrentnode);
							strcpy(lhs.datatype,ht1->buckets[i].e.ptr->buckets2[j].e2.type);
						}
					}
				}
			}
		}
		}
		}
		//printf("\n lhs.datatype = %s",lhs.datatype);
		//printf("\n lhs.varname = %s",lhs.varname);

		if(strcmp(lhs.datatype,"int")==0)
			rhs.typeflag=0;
		if(strcmp(lhs.datatype,"real")==0)
			rhs.typeflag=1;		
		rhs=dfsassign(curr->sibling,rhs,string,ht1);
		if(rhs.error==1)
			printf("\nError : Left hand type not equal to Right hand type\n");
		//else 
		//	printf("\n no error\n");
	}

	//if(strcmp(curr->a.token,"TK_"
	/*
	if(strcmp(curr->a.token,"TK_ASSIGNOP")==0&&strcmp(curr->parent->a.lexemecurrentnode,"<outputParameters>")==0)
	{
		curr=curr->parent->children->sibling;
		curr=curr->children;
		type x;		
	}*/
	/*if(strcmp(curr->a.token,"TK_IF")==0)
	{
		type typeif;
		curr=curr->sibling->sibling;
		typeif=dfsif(curr,typeif,string,ht1);
	}*/
}	
/*
type dfsif(Treenode head,type typeif,char * string,HashTable ht1)
{
	Treenode temp=NULL;
	if(head->children!=NULL)
	{
		typeif=dfsif(head->children,typeif,string, ht1);
		temp=head->children->sibling;
	}
	while(temp !=NULL)
	{
		typeif=dfsif(temp,typeif,string,ht1);
		temp=temp->sibling;
	}
	Treenode curr=head;
	
	if(strcmp(curr->a.token,"TK_NUM")==0)
	{
		if(rhs.typeflag==1)
			rhs.error=1;
	}
	if(strcmp(curr->a.token,"TK_RNUM")==0)
	{
		if(rhs.typeflag==0)
			rhs.error=1;
	
	}
	
}*/

type isinglobal(Treenode current,HashTable ht1)
{
	type x;
	x.gflag=0;
	x.count=0;
	int i=0;
	int j=0;
	for(i=0;i<100;i++)
		{
			if(ht1->buckets[i].status==1)
			{	//printf("current function is %s",string);
				if(strcmp(ht1->buckets[i].e.funcname,"global")==0)
				{
					for(j=0;j<100;j++)
					{
						if(ht1->buckets[i].e.ptr->buckets2[j].status==1)
						{
						//printf("\nlex name %s \n",current->a.lexemecurrentnode);
						if(strcmp(ht1->buckets[i].e.ptr->buckets2[j].e2.identifiername,current->a.lexemecurrentnode)==0)
						{
							strcpy(x.varname,current->a.lexemecurrentnode);
							strcpy(x.datatype,ht1->buckets[i].e.ptr->buckets2[j].e2.type);
							x.gflag=1;
							x.count++;
						}
						}
					}
				}
			}
		}
		return x;

}

