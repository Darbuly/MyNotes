/**
 * BubbleSort.c 不正宗的冒泡排序算法
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019 Darbuly
 */


#include <stdio.h>



void BubbleSort(int k[],int n)
{
	int i,j,temp;
	
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(k[i]>k[j])
			{
				temp = k[j];
				k[j] = k[i];
				k[i] = temp;
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

	
	
