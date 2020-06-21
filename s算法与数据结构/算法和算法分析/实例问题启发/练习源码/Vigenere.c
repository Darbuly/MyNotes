/*Vigenere.c search for Vigenere
 * Linux C gcc 
 *
 * @author Darbuly
 * @copylight 2018-2019
 *
 * This Program can be used to encrypt an English string by Vigenere.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 100
#define MaxSize 20
#define ENCRYPT 1
#define DECRYPT 0
#define SHOW_CHAR 1
#define SHOW_INT 2 

typedef int ElemType;
typedef int Status;

//Sqlist struct
struct Sqlist{
	ElemType elem[MaxSize];
	int length;
};
typedef struct Sqlist *PtrNode;
typedef PtrNode List;
//DualNode struct
typedef struct DualNode
{
	char data;
	struct DualNode *prior;
	struct DualNode *next;
}DualNode,*DuLinkList;


//Initial the Sqlist
List InitList()
{
	List L;
	L = (List)malloc(sizeof(struct Sqlist));
	L->length =0;
	return L;
}

//Insert The Sqlist
Status Insert_Sqlist(List L,int i,ElemType x)

{
	int j;
	if(i<1||i>L->length+1)
	{
		printf("OVERFLOW!\n");
		return ERROR;
	}
	for(j=L->length;j>i;j--)
	{
		L->elem[j+1]=L->elem[i];
	}
	L->elem[i-1]=x;
	L->length++;
	return OK;
}
//GetElem from Sqlist
ElemType GetElem(List L,int i)
{
	if(L->length==0||i<1||i>L->length)
		return ERROR;
	return L->elem[i-1];
}

//Print the Sqlist
void PrintSqlist(List L,int showMethod)
{
	int i;
	for(i=0;i<L->length;i++)
	{
		if(showMethod==SHOW_CHAR)
			printf("%c ",L->elem[i]);
		if(showMethod==SHOW_INT)
			printf("%d ",L->elem[i]);
	}
	printf("\n");
}

//Initial DualLink
DuLinkList InitLink()
{
	DuLinkList L;
	DualNode *p,*q;
	L = (DuLinkList)malloc(sizeof(DualNode));
	L->next = L->prior=NULL;
	p=L;
	
	int i;
	
	for(i=0;i<26;i++)
	{
		q = (DualNode*)malloc(sizeof(DualNode));
		q->data = 'A'+i;
		q->prior = p;
		q->next = p->next;
		p->next =q;
		p=q;
	}
	p->next = L->next;
	L->prior = p;
	return L;
}
//Encrypt and Decrypt
char Crypt(DuLinkList L,char str,int offset,int method)
{
	
	int i=0;
	char n;
//	printf("pipei=%c\n",str);
	while(L->data!=str)
	{
		L = L->next;
//		printf("%c:%c\n",str,L->data);
	}	
	n = L->data;

	
	if(method==ENCRYPT)
	{
//		printf("method=encrypt!\n");
		for(i=0;i<offset;i++)
		{
			L = L->next;
		}
		return L->data;
	}
	if(method==DECRYPT)
	{
		printf("n=%c\n",n);
		printf("offset=%d\n",offset);
//		printf("method=decrypt!\n");
		for(i=0;i<offset;i++)
		{
			L = L->prior;
		}
//		L = L->prior;
		L = L->prior;
		L = L->prior;

		return L->data;
	}
}



int main()
{
	int cmd,read_n;
	char buf[20];
	char m;
	List str,offset,cry_str;
	DuLinkList abc;
	int i,key[20];
	printf("Hello!Welcome to use my Program!\n");
	printf("This Program can be used to encrypt or decrypt an English string by Vigenere\n");
	printf("Tell me what you want to do?\n");
	printf("1:encrypt an string\n");

	printf("2:decrypt an string by key\n");
	printf("3:exit\n");
	scanf("%d",&cmd);
	switch(cmd)
	{
		case 1:
		{
			
			printf("Please enter your string without space!(<20)\n");
			read_n = read(0,buf,128);
			if(read_n ==-1)
			{
				printf("read error had occor!");
				exit(0);
			}
			str = InitList();
			for(i=1;i<read_n;i++)
				Insert_Sqlist(str,i,buf[i-1]);
			offset = InitList();
			srand(time(0));
			for(i=1;i<read_n;i++)
				Insert_Sqlist(offset,i,rand()%100+1);
			PrintSqlist(str,SHOW_CHAR);
//			printf("%c\n",GetElem(str,2));
			PrintSqlist(offset,SHOW_INT);
			
			abc = InitLink();
			abc = abc->next;
			
			cry_str = InitList();
//			Crypt(abc,GetElem(str,1),GetElem(offset,1),ENCRYPT);
//			printf("%c\n",Crypt(abc,GetElem(str,1),GetElem(offset,1),ENCRYPT));
//			printf("%c\n",Crypt(abc,GetElem(offset,2),ENCRYPT));
			for(i=1;i<read_n;i++)
			{
				Insert_Sqlist(cry_str,i,Crypt(abc,GetElem(str,i),GetElem(offset,i),ENCRYPT));
			}
			PrintSqlist(cry_str,SHOW_CHAR);
//			for(i=0;i<26;i++)
//			{
//				abc = abc->next; 
//				printf("%c->",abc->data);
//			}
			//printf("%d\n",read_n);
			//write(1,buf,read_n);
			//CreateChar_LinkList(buf);
			//printf("%c\n",buf[0]);	
			break;
		}
		case 2:
		{
			printf("Please enter your cry_string without space!(<20)\n");
			read_n = read(0,buf,128);
			if(read_n ==-1)
			{
				printf("read error had occor!");
				exit(0);
			}
			str = InitList();
			for(i=1;i<read_n;i++)
				Insert_Sqlist(str,i,buf[i-1]);
			offset = InitList();
			printf("Please enter your %d keys\n",read_n-1);
			for(i=1;i<read_n;i++)
				scanf("%d",&key[i-1]);
			
//			PrintSqlist(str,SHOW_CHAR);
//			printf("%c\n",GetElem(str,2));
//			PrintSqlist(offset,SHOW_INT);
			
			abc = InitLink();
			abc = abc->prior;
			for(i=1;i<read_n;i++)
				printf("%c ",Crypt(abc,GetElem(str,i),key[i-1],DECRYPT));
//			printf("Enter the str:key\n");
//			scanf("%c:%d",&m,&i);
//			printf("%c\n",Crypt(abc,'R',66,DECRYPT));
			break;
		}
		case 3:return 0;break;
	}
} 
