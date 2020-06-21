/**
 * InsertSort.c  直接插入排序算法
 *
 * @author Darbuly 2019-2020
 * @copyright 
 */


#include <stdio.h>



void InsertSort(int k[],int n)
{
	int i,j,temp;
	
	for(i=1;i<n;i++)
	{
		if(k[i]<k[i-1])
		{
			temp = k[i];
		
		
			for(j=i-1;k[j]>temp;j--)
			{
				k[j+1] = k[j];
			}
		
			k[j+1] = temp;
		}
	}
}


int main()
{
	int i,a[10] = {5,2,6,0,3,9,1,7,4,8};
	printf("InsertSort.c Test\n");
	InsertSort(a,10);
	
	printf("Sorted BY InsertSort:\n");
	for(i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n\n");
	return 0;
}

	

