

//二进制转10进制
//
//时间复杂度     O(n),No.3




#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define SOVERFLOW -1



typedef int Status;
typedef char ElemType;
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}sqStack;

Status InitStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if(!s->base)return ERROR;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(sqStack *s,ElemType e)
{
	if(s->top - s->base >= s->stacksize)
	{
		s->base = (ElemType *)realloc(s->base,(s->stacksize + STACKINCREMENT)*sizeof(ElemType));
		if(!s->base)return SOVERFLOW;
		s->top = s->base + s->stacksize;
		s->stacksize = s->stacksize + STACKINCREMENT;
	}
	*(s->top++)=e;
	return OK;
}


Status Pop(sqStack *s,ElemType *e)
{
	if(s->top == s->base)return ERROR;
	*e = *(--s->top);
	return OK;
}
int StackLen(sqStack s)
{
	return(s.top - s.base);	
}

int main()
{
	ElemType c;
	sqStack s;
	int len,i,sum = 0;
	
	InitStack(&s);
	
	printf("plase input some num by bin and end with #\n");
	scanf("%c",&c);
	while(c != '#')
	{
		Push(&s,c);
		scanf("%c",&c);
	}
	getchar();
	
	len = StackLen(s);
	printf("The length of stack is:%d\n",len);
	for(i=0;i<len;i++)
	{
		Pop(&s,&c);
		sum = sum + (c-48)*pow(2,i);
	}
	printf("The Dec is :%d\n",sum);
	return 0;
}



















