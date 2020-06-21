/**
 * SelectSort.c 选择排序算法
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019
 * 
 */


#include <stdio.h>


void SelectSort(int k[],int n)
{
	int i,j,temp,min;
	
	for(i=0;i<n-1;i++)
	{
		min = i;
		for(j=i+1;j<n;j++)
		{
			if(k[j]<k[min])
			{
				min = j;
			}
		}
		
		if(min!=i)
		{
			temp = k[min];
			k[min] = k[i];
			k[i] = temp;
		}
	}
}

int main()
{
	int i,a[10] = {5,2,6,0,3,9,1,7,4,8};
	printf("SelectSort.c Test\n");
	
	SelectSort(a,10);
	
	printf("Sorted by SelectSort:\n:");
	for(i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n\n");
	return 0;
}
	
