/**
 * QuickSort.c 快速排序算法 优化选取基准点
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2019-2020 DBL
 * 
 */

#include <stdio.h>

void swap(int k[],int low,int high)
{
	int temp;
	
	temp = k[low];
	k[low] = k[high];
	k[high] = temp;
}

int Partition(int k[],int low,int high)
{
	int point;
	//优化选取基准点
	int m = low + (high-low)/2;
	if(k[low]>k[high])
	{
		swap(k,low,high);
	}
	if(k[m]>k[high])
	{
		swap(k,m,high);
	}
	if(k[m]>k[low])
	{
		swap(k,m,low);
	}

	point = k[low];
	
	while(low<high)
	{
		while(low<high && k[high]>=point)
		{
			high--;
		}
		swap(k,low,high);
		while(low<high && k[low]<=point)
		{
			low++;
		}
		swap(k,low,high);
	}
	return low;
}

void QSort(int k[],int low,int high)
{
	int point;
	
	if(low<high)
	{
		point = Partition(k,low,high);
		QSort(k,low,point-1);
		QSort(k,point+1,high);
	}
}
	
	

void QuickSort(int k[],int n)
{
	QSort(k,0,n-1);
}

int main()
{
	int i,a[10] = {5,2,6,0,3,9,1,7,4,8};
	
	QuickSort(a,10);

	printf("Sort by QuickSort\n");
	for(i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n\n");

	return 0;
}
