/**
 * reload.cpp 函数的重载课后作业
 *
 * @author Darbuly 970073804@qq.com
 * @copytight 2019-2020 DBL
 */
#include <iostream>

int calc(int num);
int calc(int a,int b);
int calc(int a,int b,int c);


int main()
{
	int n[3],cnt=0,res,i=0;	
	std::cout<<"input:";
	do{
		std::cin>>n[i++];
		cnt++;
	}while(std::cin.get()!='\n'||cnt>3);
	
	switch(cnt)
	{
		case 1:
			res = calc(n[0]);
			break;
		case 2:
			res = calc(n[0],n[1]);
			break;
		case 3:
			res = calc(n[0],n[1],n[2]);
			break;
	}
	std::cout<<"\n"<<"res is :"<<res<<std::endl;
	return 0;
}


int calc(int num)
{
	return num*num;
}

int calc(int a,int b)
{
	return a*b;
}

int calc(int a,int b,int c)
{
	return a+b+c;
}
