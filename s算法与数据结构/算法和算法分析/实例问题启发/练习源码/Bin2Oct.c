





//二进制转八进制   时间复杂度O(n),No3







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
	if(!s->base)
	{
		return ERROR;
	}	
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;	
}

Status Push(sqStack *s,ElemType e)
{
	if(s->top - s->base >=s->stacksize)
	{
		s->base = (ElemType *)realloc(s->base,(s->stacksize + STACKINCREMENT)*sizeof(ElemType));
		if(!s->base)
		{
			return ERROR;
		}
		s->top = s->base + s->stacksize;
		s->stacksize = s->stacksize + STACKINCREMENT;
	}
	*(s->top++)=e;
	return OK;
}
Status Pop(sqStack *s,ElemType *e)
{
	if(s->top == s->base) return ERROR;
	*e = *(--s->top);
	return OK;
}
int StackLen(sqStack s)
{
	return (s.top - s.base);
}



int main()
{
	sqStack s1,s2;
	int len1,len2,d,y,i,j,sum=0;
	ElemType c;

	InitStack(&s1);
	InitStack(&s2);

	printf("Please enter a number by Bin and end by # :\n");
	scanf("%c",&c);
	while( c != '#')
	{
		Push(&s1,c);
		scanf("%c",&c);
	}
	getchar();//吃掉回车
	
	len1 = StackLen(s1);
	printf("The length of s1 is : %d \n",len1);
	d = len1/3;//d==2
	y = len1%3;//y==2
	for(i=0;i<d;i++)						//一共有2组够3的，每组计算
	{
		for(j=0;j<3;j++)					//计算所有能被3整除部分的组
		{
			Pop(&s1,&c);
			sum = sum + (c-48)*pow(2,j);	//pow(x,n)  计算x^n (c-48)*pow(2,j)  计算   伯努利计次变量* 2^n
		}
		//printf("%d",sum);
		Push(&s2,sum+48);					//低位三个一组  进栈2保存
		sum = 0;							//为了二次利用  清0
	}
	for(i=0;i<y;i++)						//计算高位缺3的部分
	{
		Pop(&s1,&c);
		sum = sum + (c-48)*pow(2,i);		//pow(x,n)  计算x^n (c-48)*pow(2,j)  计算   伯努利计次变量* 2^n
	}
	//printf("%d",sum);
	Push(&s2,sum+48);						
	len2 = StackLen(s2);
	printf("The Oct is :");
	for(i=0;i<len2;i++)						//输出结果栈，就得到答案
	{
		Pop(&s2,&c);
		printf("%c",c);
	}	
	printf("\n");
	return 0;
}




















