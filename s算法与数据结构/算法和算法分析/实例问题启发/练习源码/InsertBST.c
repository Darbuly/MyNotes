

#include <stdio.h>
#include <stdlib.h>


typedef struct BiNode
{
	int data;
	struct BiNode *lchild,*rchild;
}BiNode,*BiTree;

int str[] = {70,105,115,104,67,46,99,111,109,65535};
int top=0;
void insertChild(BiTree *T,int num);
void CreateBT(BiTree *T)
{
	*T = (BiNode*)malloc(sizeof(BiNode));
	(*T)->lchild = NULL;
	(*T)->rchild = NULL;
	
	int num;
	//scanf("%d",&num);
	num = str[top++]; 
	
	if((*T)!=NULL && 65535 !=num)
		(*T)->data = num;

	while(65535!=num)
	{
		//scanf("%d",&num);
		num = str[top++];
		if((*T) !=NULL && 65535 !=num)
			insertChild(T,num);
	}
}

void insertChild(BiTree *T,int num)
{
	if(num<(*T)->data)
	{
		if((*T)->lchild==NULL)
		{
			(*T)->lchild = (BiNode*)malloc(sizeof(BiNode));
			(*T)->lchild->lchild=NULL;
			(*T)->lchild->rchild=NULL;
			(*T)->lchild->data = num;
		}
		else
		{
			insertChild(&((*T)->lchild),num);
		}
	}
	else
	{
		if((*T)->rchild==NULL)
		{
			(*T)->rchild = (BiNode*)malloc(sizeof(BiNode));
			(*T)->rchild->rchild=NULL;
			(*T)->rchild->lchild=NULL;
			(*T)->rchild->data = num;
		}
		else
		{
			insertChild(&((*T)->rchild),num);
		}
	}
}
void visit(int c,int level)
{
	printf(" %d   located in %d layer\n",c,level);
}

void MidOrderTraverse(BiTree T,int level)
{
	if(T)
	{
		MidOrderTraverse(T->lchild,level+1);
		visit(T->data,level+1);
		MidOrderTraverse(T->rchild,level+1);
	}
}
	

	

int SearchBST(BiTree T,int key,BiTree f,BiTree *p)
{
	if(!T)
	{
		*p = f;
		return 0;
	}
	else if(key==T->data)
	{
		*p = T;
		return 1;
	}
	else if(key<T->data)
	{
		return SearchBST(T->lchild,key,T,p);
	}
	else
	{
		return SearchBST(T->rchild,key,T,p);
	}
}	

int InsertBST(BiTree *T,int key)
{
	BiTree p,s;
	if(!SearchBST(*T,key,NULL,&p))
	{
		s = (BiNode*)malloc(sizeof(BiNode));
		s->data = key;
		s->lchild = s->rchild = NULL;
		
		if(!p)
		{
			*T=s;
		}
		else if (key<p->data)
		{
			p->lchild = s;
		}
		else
		{
			p->rchild = s;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}	
		




int main()
{
	printf("InsertBST.c  Test\n");
	BiTree T,p;
	int level=0;
	int key;
	CreateBT(&T);
	MidOrderTraverse(T,level);
	
	printf("Please enter what you want to insert:\n");
	scanf("%d",&key);

	
	if(InsertBST(&T,key))
	{
		level = 0;
		MidOrderTraverse(T,level);
	}
	else
	{
		printf("Insert error!Maybe it is exited!\n");
	}
		
	return 0;
}

	
