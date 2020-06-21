

/**
 * BinarySearch.c 折半查找法(递归实现)
 *
 * @author DBL 970073804@QQ.COM
 * @copyright 2018-2019 DBL
 *
 * 
 */


#include <stdio.h>



int binary_search(int str[],int low,int hight,int key)
{
	int mid;
	if(low>hight)return -1;
	mid = (low+hight)/2;
	if(str[mid]==key)return mid;
	if(str[mid]>key)return binary_search(str,low,mid-1,key);
	if(str[mid]<key)return binary_search(str,mid+1,hight,key);
}

int main()
{
	int k,str[11] = {1,1,2,3,5,8,13,21,34,55,89};
	int addr;

	printf("Please enter a key you want to search:\n");
	scanf("%d",&k);
	addr = binary_search(str,0,10,k);
	printf("The addr is :%d\n",addr);
	return 0;
}
	













