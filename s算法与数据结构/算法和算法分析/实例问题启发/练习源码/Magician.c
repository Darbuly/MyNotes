
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next; 
}node;

node *create (int n)
{
	node *head,*p,*s;
	head  = (node*)malloc(sizeof(node));
	p = head;
	int i=1;
	if(0!=n)
	{
		while(i<n)
		{
			s = (node*)malloc(sizeof(node));
			s->data = 0;
			p->next = s;
			p = s;
			++i;
		}
		s->next = head->next;
	}
	free(head);
	return s->next;
}

int main()
{
	node *p = create(14);//为什么是14呢
	node *s;//s 的作用是  用来作一个 头指针  因为在发牌的时候  你得知道 我该从哪里 开始发
	s = p;
	p->data = 1;
	
	int i=2,j;//i  是代表着  当前数数  的递增数列排列  当前是  2   下一次是  3
	while(1)
	{
		for(j=0;j<i;j++)//对  数数 数列 每次就跳多少次这么多的  链表
		{
			p = p->next;
			if(p->data!=0)//因为是循环链表  会出现已经安排好序列的元素    为了避免  j-- 抵消  j++  就是跳过它
			{
				 p->next;
				j--;
			}
			
		}
		if(p->data == 0)//安排该元素的扑克牌序列
		{
			p->data = i;
			i++;
			if(i==14)//如果递增数列 数到14 了  就说明 整个链表元素全部安排完毕  跳出循环
			{
				break;
			}
		}
	}
	//输出魔术师发牌的序列
	for(i=0;i<14;i++)
	{
		printf("%d->",s->data);
		s = s->next;
		
	}
	return 0;
}
