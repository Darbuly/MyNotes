




#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

node *create(int n)
//一级指针解决方案：因为是结构体嵌套分配  不需要二级指针
//因为mian中的  node *p = create(n);    p必须是地址，而*p是地址的内容块，所以create必须返回地址的内容块
//由于create  return s->next      s->next 是一个地址，地址求内容块  就是  前面加*
{
	node *head,*p;
	head = (node*)malloc(sizeof(node));
	p = head;
	node *s;
	int i=1;
	if(0!=n)	
	{
		while(i<n)
		{
		 	s = (node*)malloc(sizeof(node));
			s->data=i++;
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}
	free(head);
	return s->next;
}
int main()
{
	int n = 41;
	int m = 3;
	m%=n;//这里等于2
	int i;
	node *p = create(n);//*p = *（s->next）,s->next=BBBBBBB,*(BBBBBBBB):{BNode},p=s->next:BBBBBBBBB
	node *temp;

	while(p!=p->next)
	{
		for(i=1;i<m-1;i++)//每次只会循环一次  因为 m-1=1
		{
			p = p->next;//一次
		}
		printf("%d->",p->next->data);//两次  它的下一个人要自杀
		//从链表中删除
		temp = p->next;
		p->next = temp->next;
		free(temp);

		p = p->next;
	}
	printf("%d\n",p->data);
	return 0;
}
