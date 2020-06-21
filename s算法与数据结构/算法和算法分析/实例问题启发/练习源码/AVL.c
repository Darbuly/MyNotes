/**
 * AVL.c   平衡二叉排序树
 *
 * @author Darbuly  970073804@qq.com
 * @copyright 2018-2019 Darbuly
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define LH 1
#define EH 0
#define RH -1

#define TRUE 1
#define FALSE 0

typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void CreateBiTree(BiTree *T)
{
	(*T) = (BiTNode *)malloc(sizeof(BiTNode));
	(*T)->lchild = (*T)->rchild = NULL;
	(*T)->bf = 0;
}
void R_Rotate(BiTree *T)
{
	BiTree p;
	p = (*T)->lchild;
	(*T)->lchild = p->rchild;
	p->rchild = (*T);
	(*T) = p;
}

void L_Rotate(BiTree *T)
{
	BiTree p;
	p = (*T)->rchild;
	(*T)->rchild = p->lchild;
	p->lchild = (*T);
	(*T) = p;
}
	
void LeftBalance(BiTree *T)
{
	BiTree L,Lr;
	L = (*T)->lchild;
	switch(L->bf)
	{
		case LH:
			(*T)->bf=L->bf = EH;
			R_Rotate(T);
			break;
		case RH:
			Lr = L->rchild;
			switch(Lr->bf)
			{
				case LH:
					(*T)->bf = RH;
					L->bf = EH;
					break;
				case EH:
					(*T)->bf= L->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					L->bf = LH;
					break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);
			R_Rotate(T);
		case EH:
			L->bf = RH;
			(*T)->bf = LH;
			R_Rotate(T);
			break;
	}				
}

void RightBalance(BiTree *T)
{
	BiTree R,Rl;
	R = (*T)->rchild;
	switch(R->bf)
	{
		case RH:
			(*T)->bf = R->bf = EH;
			L_Rotate(T);
			break;
		case EH:
			R->bf = LH;
			(*T)->bf = RH;
			L_Rotate(T);
			break;
		case LH:
			Rl = R->lchild;
			switch(Rl->bf)
			{
				case EH:
					(*T)->bf = R->bf = EH;
					break;
				case RH:
					R->bf = EH;
					(*T)->bf = LH;
					break;
				case LH:
					R->bf = RH;
					(*T)->bf = EH;
					break;
			}
			Rl->bf = EH;
			R_Rotate(&(*T)->rchild);
			L_Rotate(T);
			break;
	}
}
			
int InsertAVL(BiTree *T,int e,int *taller)
{
	if(!*T)
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild=(*T)->rchild=NULL;
		(*T)->bf=EH;
		*taller = TRUE;
	}
	else
	{
		if(e==(*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}
		if(e<(*T)->data)
		{
			if(!InsertAVL(&(*T)->lchild,e,taller))
			{
				return FALSE;
			}
			
			if(*taller)
			{
				switch((*T)->bf)
				{
					case LH:
						LeftBalance(T);
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = LH;
						*taller = TRUE;
						break;
					case RH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
				}
			}
		}
		else
		{
			if(!InsertAVL(&(*T)->rchild,e,taller))
			{
				return FALSE;
			}
			if(*taller)
			{
				switch((*T)->bf)
				{
					case LH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = RH;
						*taller = TRUE;
						break;
					case RH:
						RightBalance(T);
						*taller = FALSE;
						break;
				}
			}
		}
	}
}	
void visit(int c,int level)
{
	printf("\n %d  located in %d layer\n",c,level);
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


			
int main()
{
	BiTree T;
	int e,taller,level=0;
	printf("AVL.c Test\n");
	
	//CreateBiTree(&T);
	T = NULL;
	printf("Please enter number with creating the AVL,ending by 65535:\n");
	scanf("%d",&e);
	while(65535!=e)
	{
		InsertAVL(&T,e,&taller);
		scanf("%d",&e);
	}
	printf("\nOK!THe MidOrderTraverse can be followed :\n");
	MidOrderTraverse(T,level);
	

			
	return 0;
}
