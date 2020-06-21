
#include "stdio.h"

int count= 0;
int notDanger(int row,int j,int (*chess)[8])
{
	int i,k,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0;	//通过遍历攻击范围的格子，如果发现不为1，那么久标志着危险，所以要五个
	//判断列方向
	for(i=0;i<8;i++)
	{
		if( *(*(chess+i)+j) !=0)
		{
			flag1 = 1;
			break;
		}
	}
	//判断左上方
	for(i=row,k=j;i>=0 && k>=0;i--,k--)
	{
		if( *(*(chess+i)+k)!= 0)
		{
			flag2 = 1;
			break;
		}
	}
	//判断右下方
	for(i=row,k=j;i<8 && k<8;i++,k++)
	{
		if(*(*(chess+i)+k) !=0)
		{
			flag3 = 1;
			break;
		}
	}
	//判断右上方
	for(i=row,k=j;i>=0 && k< 8;i--,k++)
	{
		if( *(*(chess+i)+k) != 0)
		{
			flag4 = 1;
			break;
		}	
	}
	//判断左下方
	for(i=row,k=j;i<8 && k>= 0;i++,k--)
	{
		if( *(*(chess+i)+k) != 0)
		{
			flag5 = 1;
			break;
		}
	}
	if(flag1 || flag2 || flag3 || flag4 || flag5)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}	
//参数low表示起始行
//参数n表示列数
//参数(*chess)[8]表示指向棋盘每一行的指针
EightQueen(int row,int n, int (*chess)[8])//用指针表示二维数组
//二维数组a[M][N]中，a[i]表示的就是元素a[i][0]的地址
//a[i]+j == &a[i][j]
//&a[i][0]+j == &a[i][j]
//一维数组中 a[i] 和 *(a+i)等价
//*(a+i)+j == &a[i][j]
//*(*(a+i)+j) = a[i][j]
{
	int chess2[8][8],i,j;
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			chess2[i][j]=chess[i][j];
		}
	}
		
	if(8 == row)//递归的结束条件  就是当 递归到第8行时结束
	{
		printf("第 %d 种\n",count+1);	//直接将最后一种迭代输出
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				//printf("%d ",chess2[i][j]);
				printf("%d ",*(*(chess2+i)+j));
			}
			printf("\n");
		}
		printf("\n");
		count++;	//	习惯上没输出一次 就计次器就++（所以你看到main中不需要+1）
	}
 	else{			//否则，则进入递归
		for(j=0;j<8;j++)
		{
			if( notDanger( row,j,chess))   //设计一个函数专门看是否有危险
			{
				for(i=0;i<8;i++)		//如果不危险，就就讲该列全部写0
				{
					*(*(chess2+row)+i) = 0;
				}
				*(*(chess2+row)+j) = 1;    	//占位置
				EightQueen( row +1,n,chess2);//
				//chess2是数组，本身代表着数组的首地址   用int (*chess)[8]接受它的行地址   实参是int *()[8]
			}
	
		}
		
	}
		
}


int main()
{
	int chess[8][8],i,j;

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			chess[i][j]=0;
		}
	}

	EightQueen(0,8,chess);
	
	printf("总共有 %d 种解决方法！\n\n",count);
	
	return 0;
}
