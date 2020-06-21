/**
 * ShellSort.c 希尔排序
 *
 * @author Darbuly 970073804@qq.com
 * @copyright DBL 2019-2020
 */


#include <stdio.h>

void ShellSort(int k[],int n)
{
	int i,j,temp;
	int gap = n;
	
	do
	{
		gap = gap/3+1;
		
		for(i=gap;i<n;i++)
		{
			if(k[i]<k[i-gap])
			{
				temp = k[i];
			
			
				//for(j=i-gap;k[j]>temp;j-=gap)
				//{
				//	k[j+gap] = k[j];
				//}//小甲鱼的这个算法会出现内存溢出问题，用以下代替
				j=i-gap;	
				do{
					
					k[j+gap] = k[j];
					j-=gap;
				}while(k[j]>temp&&j>=0);
			
				k[j+gap] = temp;
			}
		}
	}while(gap>1);
}


int main()
{
	int i,a[10] = {5,2,6,0,3,9,1,7,4,8};
	printf("ShellSort.c Test\n");
	ShellSort(a,10);
	
	printf("Sorted BY ShellSort:\n");

	for(i=0;i<10;i++)
	{
		printf("%d",a[i]);
	}



	printf("\n\n");
	return 0;
}

	

