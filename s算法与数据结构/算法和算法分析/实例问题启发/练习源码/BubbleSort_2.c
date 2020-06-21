
/**
 * BubbleSort.c 正宗的冒泡排序算法
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019 DBL
 */

#include <stdio.h>



void BubbleSort(int k[],int n)
{
	int i,j,temp,flag;
	
	flag = 1;
	for(i=0;i<n-1 && flag ;i++)
	{
		for(j=n-1;j>i;j--)
		{
			flag = 0;
			if(k[j-1]>k[j])
			{
				temp = k[j-1];
				k[j-1] = k[j];
				k[j] = temp;
				flag = 1;
			}
		}
	}
}


int main()
{
	int i,a[10] = {5,2,6,0,3,9,1,7,4,8};
	printf("BubbleSort.c Test\n");
	
	BubbleSort(a,10);
	printf("With BubbleSort:\n");
	for(i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n");
	return 0;
}

	
	
