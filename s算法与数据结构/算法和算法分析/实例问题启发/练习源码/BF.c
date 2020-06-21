





#include <stdio.h>
#include <string.h>
int BF(char s1[],char s2[])
{
	int i,j,flag=0,len1,len2;
	len1 = strlen(s1);
	len2 = strlen(s2);
	for(i=0;i<len1;i++)		//工作指针i 指示  S1
	{
		if(s2[0]==s1[i])   	//当s2的第一个字符匹配成功   则触发全匹配工作
		{
			j=1;			//初始化s2的工作指针j
			while(s2[j]==s1[i+j])		//只要一直匹配成功  我就++      如果匹配失败，就跳回上一个if 判断第一成功匹配触发
			{
				if(j==len2-1)		//循环结束的触发条件就是    一直匹配 直到S2的工作指针能走完 说明全匹配成功！！  	
				{
					flag=1;			//通过flag来标记成功，计1，跳出循环
					break;
				}
				j++;				//只要一直匹配成功  我就++
			}
		}
	}
	return flag;
}


int main()
{
	char s1[]={"I am dcrbuly."};
	char s2[]={"darbuly"};

	printf("%d\n",BF(s1,s2));
	return 0;
}


























