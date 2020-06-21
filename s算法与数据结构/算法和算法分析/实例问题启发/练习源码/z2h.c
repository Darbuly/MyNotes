


/**
 * z2h.c   中缀表达式转后缀表达式
 *
 * @author Darbuly	970073804@qq.com
 * @copylight 2018-2019 DBL
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

typedef char ElemType;
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
		if(!s->base)return SOVERFLOW;
		s->top = s->base+s->stacksize;
		s->stacksize +=STACKINCREMENT;
	}
	*(s->top++)=e;
	return OK;
}
Status Pop(sqStack *s,ElemType *e)
{
	if(s->top ==s->base)return ERROR;
	*e = *(--s->top);
	return OK;
}
int StackLen(sqStack s)
{
	return (s.top  - s.base);
}


int main()
{
	sqStack s;																		//符号栈
	char c,str[MAXBUFFER];
	int i=0,len;
	ElemType d;
	InitStack(&s);
	printf("Please enter your expression and end by #:\n");
	scanf("%c",&c);
	while(c!='#')
	{
		while(isdigit(c)|| c=='.')													//过滤数字，遇到数字就打印 
		{
			str[i++]=c;
			str[i]='\0';															//每个字符后有一个\0  缓冲器就可以通过%s的格式来打印一个正确的数字了
			if(i>=MAXBUFFER)														//溢出判断
			{
				printf("\nThe number you entered is overflow!\n");
				return -1;
			}
			scanf("%c",&c);															//接受下一个字符  如果是字符了 说明本次数字的缓冲结束 要打印 并且触发后面的switch
			if(!isdigit(c))															//遇到符号了
			{
				printf("%s",str);													//先把这个数字打印出来
				i=0;
				break;
			}
		}
		switch(c)																	//遇到符号了
		{
			case '(':																//左括号直接进
				Push(&s,c);
				break;
			case ')':																//右括号要开始打印括号里的符号了
				Pop(&s,&d);															//打印栈顶的符号  肯定不会是(的
				printf("%c",d);
				while(d!='(')														//循环  一直打印，直到（
				{
					Pop(&s,&d);
					if(d=='(')break;												//遇到（  输出  跳出循环  本次（）输出结束
					printf("%c",d);
				}
				break;
			case '+':
			case '-':																//遇到+ 和 -  并列过滤
				if(*(s.top-1)=='*'||*(s.top-1)=='/')								//如果栈顶是优先级更高的，就得1、把优先级高的输出 2、把里面一直在吃shi 的输出
				{
					Pop(&s,&d);
					printf("%c",d);
					if(*(s.top-1)=='+'||*(s.top-1)=='-')							//2、把里面一直在吃shi 的输出
					{
						Pop(&s,&d);
						printf("%c",d);
					}	
				}
				Push(&s,c);															//最后它才进去
				break;
			case '*':																//遇到* \   过滤，直接进栈 它只会影响后面优先级低的  所以直接进了
			case '/':
				Push(&s,c);
				break;
		}		
		if(c=='#')break;															//设置结束触发条件  #
		scanf("%c",&c);																//下一次循环
	}
	len = StackLen(s);
	//	printf("\nThe len is :%d\n",len);
	for(i=0;i<len;i++)
	{
		Pop(&s,&d);
		printf("%c",d);
	}
	printf("\n");
	return 0;
}






























