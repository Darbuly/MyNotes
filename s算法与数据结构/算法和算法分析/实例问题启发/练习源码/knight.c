

/**
 * knight.c   深度优先遍历 - 骑士周游问题|马踏棋算法
 *
 * @author Darbuly
 * @copy 2018-2019 DBL
 * 
 */

#include <stdio.h>
#include <time.h>




#define X 8
#define Y 8



int chess[X][Y];


int nextxy(int *x,int *y,int count)			//以x y为基点  count为方向    看看方向通不通，同时会通过指针记录改变
{
	switch(count)
	{
		case 0:
			if(*x+2<=X-1 && *y-1>=0 && chess[*x+2][*y-1]==0)
			{
				*x+=2;
				*y-=1;
				return 1;
			}
			break;
		case 1:
			if(*x+2<=X-1 && *y+1<=Y-1 && chess[*x+2][*y+1]==0)
			{
				*x+=2;
				*y+=1;
				return 1;
			}
			break;
		case 2:	
			if(*x+1<=X-1 && *y-2>=0 && chess[*x+1][*y-2]==0)
			{
				*x+=1;
				*y-=2;
				return 1;
			}
			break;
		case 3:
			if(*x+1<=X-1 && *y+2<=Y-1 && chess[*x+1][*y+2]==0)
			{
				*x+=1;
				*y+=2;
				return 1;
			}
			break;
		case 4:
			if(*x-2>=0 && *y-1>=0 && chess[*x-2][*y-1]==0)
			{
				*x-=2;
				*y-=1;
				return 1;
			}
			break;
		case 5: 
			if(*x-2>=0 && *y+1<=Y-1 && chess[*x-2][*y+1]==0)
			{
				*x-=2;
				*y+=1;
				return 1;
			}
			break;			
		case 6:
			if(*x-1>=0 && *y-2>=0 && chess[*x-1][*y-2]==0)
			{
				*x-=1;
				*y-=2;
				return 1;
			}
			break;
		case 7:
			if(*x-1>=0 && *y+2<=Y-1 && chess[*x-1][*y+2]==0)
			{
				*x-=1;
				*y+=2;
				return 1;
			}
			break;
		default:
			break;
	}
	return 0;
}

void print()
{
	int i,j;
	for(i=0;i<X;i++)
	{
		for(j=0;j<Y;j++)
		{
			printf("%2d\t",chess[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int TravelChessBoard(int x,int y,int tag)		//tag记录了已经进行了多少步
{						
	int x1=x,y1=y,flag=0,count=0;
	chess[x][y]=tag;							//tag=0刚好是记录0步		
	
	if(X*Y == tag)								//如果步数满了  那么就是完成了
	{
		print();								//打印棋盘
		return 1;
	}	
	flag = nextxy(&x1,&y1,count);					
	while(0==flag && count<7)					//先找到一个通的为止
	{
		count++;
		flag=nextxy(&x1,&y1,count);
	}
	
	while(flag)									//一旦有通的了
	{
		if(TravelChessBoard(x1,y1,tag+1))			//，就走进下一层，如果里面的所有的层能走通64步，那么就返回1
		{
			return 1;
		}
		x1=x;										//走不通，就换个方向  也就是count++
		y1=y;
		count++;

		flag = nextxy(&x1,&y1,count);				//换完方向  看看以当前的x1y1为基点吗，这个方向通不通
		while(0==flag && count <7)					//同样，直到找到一个方向是通的才罢休
		{
			count++;
			flag = nextxy(&x1,&y1,count);
		}
	}
	
	if(0==flag)										//如果当前层全部方向都遍历过了还是走不通，那就放弃吧，写0吧
	{
		chess[x][y]=0;
	}
	return 0;
}


int main()
{
	int i,j;
	clock_t start,stop;								//计时函数记录所用时间
	//开始计时
	start = clock();		
	
	for(i=0;i<X;i++)								//初始化棋盘矩阵
	{
		for(j=0;j<Y;j++)
		{
			chess[i][j]=0;
		}
	}

	if(!TravelChessBoard(2,0,1))					//不一定每个点都能走通
													//选好点意味着时间少
	{
		printf("sorry!Coun'ld founded!\n");
	}
	//结束计时
	stop = clock();
	
	printf("\nThis time had run for :%fsec\n\n",(double)(stop-start)/CLOCKS_PER_SEC);
	
	return 0;
}	

	














