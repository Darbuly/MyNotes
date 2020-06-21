 



/**
 * Student.c 顺序查找算法
 *
 * @author Darbuly 970073804@qq.con
 * @copyright 2018-2019  DBL
 * 
 */










#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NUM 20


typedef struct 
{
	int id,score;
	char *name;
}Student[MAX_NUM];

typedef struct
{
	Student stu;
}Class;

void putsStu(Class *class,int n,int id,int score,char *name)
{
	if(!class) class = (Class*)malloc(sizeof(Class));
	class->stu[n].id = id;
	class->stu[n].score = score;
	class->stu[n].name = name; 
		
}

void showStu(Class class,int n)
{
	printf("\n===============Class==============\n");
	printf("id=%d\t,score=%d\t,name=",class.stu[n].id,class.stu[n].score);
	puts(class.stu[n].name);
	printf("\n");
}
void Find(Class class,int id)
{
	int i=0;
	while(class.stu[i].id)
	{
		if(class.stu[i].id==id)
		{
			showStu(class,i);
		}
		i++;
	}
}

int main()
{
	Class class;
	int i=0;
	int id[] = {1024,1026,1028,1030,0};
	int score[] = {100,60,100,60};
	char *name[] = {"small fishc","dance sun","black night","stray"};
	printf("Student.c Test\n");
	while(id[i])
	{
		//puts(name[i++]);
		putsStu(&class,i,id[i],score[i],name[i]);
		i++;
	}
		
	i = 0;
	while(id[i])
	{
		showStu(class,i);
		i++;
	}	
	
	
	//puts(name[0]);
	Find(class,1024);
	return 0;
}
	
