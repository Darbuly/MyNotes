/**
 * 拉丁方阵问题
 * 
 */














#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}node;

node *create(int n )
{
	node *head,*s,*p;
	head = (node*)malloc(sizeof(node));
	p = head;
	int i=0;
	while(i<n)
	{
		s = (node*)malloc(sizeof(node));
		s->data = ++i;
		p->next = s;
		p = s;
	}
	p->next = head->next;
	free(head);
	return s->next;
}


int main()
{
	node *p;
	int n,i=0,j=0;
	
	printf("Please enter the number of Latin Squart order:\n");
	scanf("%d",&n);
	if(n>2)
	{
		p = create(n);//生成拉丁方阵
	}
	while(i<n)//第一次的周期输出
	{
		printf("%d",p->data);
		p = p->next;
		++i;
	}	
	printf("\n");
	for(i=1;i<n;i++)//从1到  n-1，每次就来一次周期
	{
		p = p->next;//递进一次
		while(j<n)//一个周期输出
		{
			printf("%d",p->data);
			p = p->next;
			++j;
		}
		printf("\n");//每一个周期  就输出一次回车符
		j=0;//周期循环的工作指针归0
	}
}
