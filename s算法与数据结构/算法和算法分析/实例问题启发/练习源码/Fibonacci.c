



/**
 * Fibonacco.c 斐波那契查找
 *
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019
 *
 * 
 */









#include <stdio.h>


#define FIB_MAXSIZE 100

void ProduceFib(int *fib,int size)
{
	int i;
	
	fib[0] = 1;
	fib[1] = 1;

	for(i=2;i<size;i++)
	{
		fib[i] = fib[i-1] + fib[i-2];
	}
}
	
int FibonacciSearch(int data[],int length,int key)
{
	int low,high,mid,k,i,fib[FIB_MAXSIZE];
	
	low = 0;
	high = length-1;
	
	ProduceFib(fib,FIB_MAXSIZE);
	 
	k = 0;

	while(high>fib[k]-1)
	{
		k++;
	}
	
	for(i=length;i<=fib[k]-1;i++)
	{
		data[i] = data[high];
	}
	
	while(low<=high)
	{
		mid = low + fib[k-1] -1;
	
		if(data[mid]==key)
		{
			if(mid <=length-1)
			{
				return mid;
			}
			else
			{
				return length -1;
			}
		}

		if(data[mid]>key)
		{
			high = mid -1;
			k = k-1;
		}

		if(data[mid]<key)
		{
			low = mid +1;
			k = k -2;
		}
	}
	return -1;
}



int main()
{
	int data[] = {1,3,5,7,9,11,13,15,17,19,21};
	
	int index,key;
	printf("FibonacciSearch.c test\n");

	printf("Please enter what you want find :\n");
	scanf("%d",&key);
	index = FibonacciSearch(data,11,key);
	printf("%d\n",index);
	
	return 0;
}
