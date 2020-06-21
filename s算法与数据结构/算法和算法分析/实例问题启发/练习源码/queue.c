

/**
 * queue.c  链式队列的应用
 *
 * @author DBL 970073804@qq.com
 * @copyright 2018-2019 DBL
 * 
 */





#include <stdio.h>
#include <stdlib.h>


#define OK 1
#define ERROR 0


typedef char ElemType;
typedef int Status;

typedef struct QNode
{
	ElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front,rear;
}LinkQueue;

Status InitQueue(LinkQueue *q)
{
	q->front=q->rear=(QueuePtr)malloc(sizeof(QNode));
	if(!q->front)return ERROR;
	q->front->next=NULL;
	return OK;
}

Status InsertQueue(LinkQueue *q,ElemType e)
{
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(p==NULL)return ERROR;
	p->data=e;
	p->next=NULL;
	q->rear->next=p;
	q->rear = p;
	return OK;
}



Status DeleteQueue(LinkQueue *q,ElemType *e)
{
	QueuePtr p;
	if(q->front == q->rear)return ;
	p=q->front->next;
	*e = p->data;
	q->front->next=p->next;
	if(q->rear==p) q->rear = q->front;
	free(p);
	return OK;
}

Status DestroyQueue(LinkQueue *q)
{
	while(q->front)
	{
		q->rear = q->front->next;
		free(q->front);
		q->front = q->rear;
	}
	return OK;
}


int main()
{
	LinkQueue q;
	ElemType c;
	InitQueue(&q);
	printf("Please enter your char and end by #\n");
	scanf("%c",&c);
	while(c!='#')
	{
		InsertQueue(&q,c);		
		scanf("%c",&c);
	}
	//getchar();						//说过了   通过字符#来标识输入缓冲接受的结束  就可以不用getchar() 来解决回车带入乱码与scanf回车触发接受的矛盾了      
	while(q.rear!=q.front)
	{
		DeleteQueue(&q,&c);
		printf("%c",c);
	}
	return 0;
}






























































