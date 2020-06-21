
/**
 * BiThrTree.c
 * 线索二叉树的代码实现
 *
 * 
 */


#include <stdio.h>
#include <stdlib.h>


typedef enum {Link,Thread} PointerTag;

typedef char ElemType;

typedef struct BiThrNode
{
	ElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag ltag;
	PointerTag rtag;
}BiThrNode,*BiThrTree;

BiThrTree pre;	//全局变量，始终指向刚刚走过的结点

CreateBiThrTree(BiThrTree *T)		//通过前序遍历递归建立一颗二叉树
									//形参是双指针接收，一旦对数据结构改值，就得用双指针
	char c;
	scanf("%c",&c);
	if(' ' == c)					//递归的结束条件
	{
		(*T) = NULL;
	}
	else							//进入递归
	{
		(*T) = (BiThrNode *)malloc(sizeof(BiThrTree));	//新建一个结点   先根
		(*T)->data = c;
		(*T)->ltag = Link;								//这个不为空的结点的左右孩子的指针类型是什么？答：链接型
		(*T)->ltag = Link;
		CreateBiThrTree(&(*T)->lchild);					//一定要双指针！  实参
		CreateBiThrTree(&(*T)->rchild);					//前序遍历创建二叉树 就是  先根  后 孩子
	}
}


InThreading(BiThrTree T)		//中序遍历线索化，递归法
{
	if(T)						//如果不是空树
	{
		//左递归
		InThreading(T->lchild);		
		//结点处理
		if(!T->lchild)			//如果左孩子为空，对于我要建立线索二叉树而言，我应该把本结点的ltag改为Thread	
								//并将左孩子指向中序遍历序列的前序		但前序已经走过了如何记得？答：全局变量脚印法
		{
			T->ltag = Thread;
			T->lchild = pre;	//先不管我们如何定义这个pre ，假设我们已经成功定义好了pre，是这样应用的 
		}
		if(!pre->rchild)		//但是，我们的线索二叉树也要知道后继的呀，所以，当我们走到一个结点时，就得为前一个结点负责！还好有pre这个记录好了，我们直接定义pre的rchild，为啥是rchild?答：线索二叉树定义的，右孩子线索为后继
		{
			pre->rtag = Thread;
			pre->rchild = T;
		}
		pre = T;				//该结点处理完了，就可以准备遍历右孩子，如何保存脚印？就在这保存就好
		//右递归
		InThreading(T->rchild);		
	}
}


InOrderThreading(BiThrTree *p,BiThrTree T)		//之所以需要额外加一个，是因为 递归是动态的，由于递归过程中用到了全局变量，而全局变量的开头问题需要解决，用一个p结点来开辟递归就好
{
	*p =(BiThrTree)malloc(sizeof(BiThrNode));		//这个开辟递归结点的左孩子就是二叉树了，右孩子设计为指向最后一个元素
	(*p)->ltag = Link;
	(*p)->rtag = Thread;
	(*p)->rchild = *p;		//还没遍历呢，先指向自己吧
	if(!T)					//如果准线索二叉树为空，那也指向自己吧
	{
		(*p)->lchild=*p;
	}
	else					//不为空，就可以开启递归遍历了
	{
		(*p)->lchild=T;		//左为准线索二叉树的根
		pre = *p;			//开启第一个脚印
		InThreading(T);		//进入遍历
		pre->rchild = *p;	//全部遍历完了。这时候的pre已经是经过递归遍历的pre，是最后那个元素，刚刚说了，它的右孩子就指回来吧
		pre->rtag = Thread;		
		(*p)->rchild = pre;		//这个开头结点就可以指向最后那个元素了
	}
}
void visit(char c)
{
	printf("%c",c);
}
void InOrderTraverse(BiThrTree T)			//用迭代法+中序遍历该二叉树
{
	BiThrTree p;
	p = T->lchild;			//由于之前建立线索二叉树的时候多了P=T，p指向T的左孩子才是树的根
	while(p!=T)				//如何设置迭代退出条件？答：有个标识就是p又等于T,因为它要么为空，要么迭代结束了（这里工作指针是p）
	{
		while(p->ltag==Link)	//如何中序遍历？先一直走，不走到左叶子到左叶子不罢休？如何实现 迭代它的左孩子只要是Link（不能通过空来判断了，因为这是线索二叉树，通过link来判断）
		{
			p = p->lchild;
		}
		visit(p->data);
		while(p->rtag == Thread && p->rchild!=T)		//接下来如何回到根？应用线索的性质，叶子右孩子必定指向它的后继，直接跳到后继去，当然不能盲目跳，因为有一种情况是不必跳的，就是跳到了P那个结点
		{
			p = p->rchild;
			visit(p->data);
		}
		p = p->rchild;				//对于这个被后继直接治过来的结点，按照中序遍历，一定是某个双亲结点，那么接下来就是右孩子遍历了，
	}
}
int main()
{
	BiThrTree P,T = NULL;
	CreateBiThrTree(&T);
	InOrderThreading(&P,T);
	InOrderTraverse(P);
	printf("\n");
	return 0;


}













