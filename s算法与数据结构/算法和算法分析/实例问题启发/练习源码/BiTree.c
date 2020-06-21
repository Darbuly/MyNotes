

/**
 *
 * BiTree.c 二叉树的建立和遍历
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019
 */



#include <stdio.h>
#include <stdlib.h>



typedef struct BiNode
{
	char data;
	struct BiNode *lchild,*rchild;
}BiNode,*BiTree;


CreateBiTree(BiTree *T)
{
	char c;
	
	scanf("%c",&c);

	if(' '==c)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiNode*)malloc(sizeof(BiNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}


void visit(char c,int level)
{
	printf("%c  located in %d layer\n",c,level);
}

void PreOrderTraverse(BiTree T,int level)
{
	if(T)
	{
		visit(T->data,level);
		PreOrderTraverse(T->lchild,level+1);
		PreOrderTraverse(T->rchild,level+1);
	}
}


void MidOrderTraverse(BiTree T,int level)
{
	if(T)
	{
		MidOrderTraverse(T->lchild,level+1);
		visit(T->data,level);
		MidOrderTraverse(T->rchild,level+1);
	}
}

	






int main()
{
	printf("BiTree.c Test\n");
	BiTree T;
	int level=1;
	CreateBiTree(&T);
	printf("\n PreOrderTraverse :\n");
	PreOrderTraverse(T,level);	
	
	level =1;

	printf("\n MidOrderTraverse :\n");
	MidOrderTraverse(T,level);
	
	return 0;
}

















