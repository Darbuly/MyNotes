




/**
 *  RPN.c  逆波兰计算器
 *
 * @author Darbuly 970073804@qq.com
 * @copylight 2018-2019 DBL
 *
 *
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10
#define OK 1
#define ERROR 0
#define SOVERFLOW -1
#define MAXBUFFER 10

typedef double ElemType;
typedef int Status;

typedef struct
{
	ElemType *base;
	ElemType *top;
	int stacksize;
}sqStack;

Status InitStack(sqStack *s)
{
	s->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!s->base)return ERROR;
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(sqStack *s,ElemType e)
{
	if(s->top - s->base >=s->stacksize)
	{
		s->base = (ElemType *)realloc(s->base,(s->stacksize+STACKINCREMENT)*sizeof(ElemType));
		if(!s->base)return ERROR;
		s->top = s->base + s->stacksize;
		s->stacksize +=STACKINCREMENT;
	}
	*(s->top++) = e;
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
	sqStack s;
	ElemType a,b,d,sum=0;								//定义为双精度64位  支持	小数
	int i;
	char c,str[MAXBUFFER];								//定义一个缓冲器， 表示数用的 如  1 2 3   str[]= 1\02\
	InitStack(&s);
	printf("Please enter RPN expression end by #:\n");	//数字之间要有空格
	scanf("%c",&c);
	while(c!='#')										//通过用特定字符来标识结尾  不需要用到getchar()来吃掉回车
	{
		while(isdigit(c) || c=='.')  					//isdigit()判断是否为十进制字符  需要ctype.h头文件支持，  这里不断输入数值,一次循环一个数
		{
			str[i++]=c;									
			str[i]='\0';								//至于为什么要定制缓冲器每个数字后有个\0  跟 atof有关
			if(i>=MAXBUFFER)
			{
				printf("\nError!Overflow!\n");			//
				return -2;
			}
			scanf("%c",&c);
			if(c==' ')                        			//遇到空格 说明  该数的输入 结束
			{
				d = atof(str);							//atof()  头文件是stdlib.h 将缓冲器的字符形式的数转换为真正的数，并push到栈里面  
				Push(&s,d);
				i = 0;
				break;
			}
		}
		switch(c)                                       //前面同级的while优先过滤是数字的可能，接下来过滤掉    +  -   *  /
		{
			case '+':									//遇到 + 就要弹出两个数  进行 +法运算  再进栈
				//printf("It is a Inc\n");
				Pop(&s,&b);
				Pop(&s,&a);
				Push(&s,a+b);
				break;
			case '-':
				Pop(&s,&b);
				Pop(&s,&a);
				Push(&s,a-b);
				break;
			case '*':
				Pop(&s,&b);
				Pop(&s,&a);
				Push(&s,a*b);
				break;
			case '/':
				Pop(&s,&b);
				Pop(&s,&a);
				if(b==0)									//先出栈的是除数，不能为0
				{
					printf("\nError,b can not be zero!\n");
					return -1;
				}
				Push(&s,a/b);
				break;
		}
		scanf("%c",&c);										//继续触发下次的输入，返回循环  遇到#结束

	}
	Pop(&s,&d);
	printf("\nResult is : %f\n",d);
	return 0;
}





















