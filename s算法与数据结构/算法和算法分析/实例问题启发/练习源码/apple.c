

/**
 * apple.c  插入查找算法
 * 
 */


#include <stdio.h>



int insert_search(int str[],int low,int high,int key)
{
	int mid;
	if(low>high)return -1;
	//mid = (low+high)/2;
	//mid = low + (key-str[low])/(str[high]-str[low])*(high-low);
	mid = low + (key-str[low])*(high-low)/(str[high]+str[low]);
	printf("\nmid=%d",mid);
	if(str[mid]==key)return mid;
	if(str[mid]>key)return insert_search(str,low,mid-1,key);
	if(str[mid]<key)return insert_search(str,mid+1,high,key);
}

int main()
{
	int k,str[11] = {1,1,2,3,5,8,13,21,34,55,89};
	int addr;

	printf("Please enter a key you want to search:\n");
	scanf("%d",&k);
	addr = insert_search(str,0,10,k);
	printf("The addr is :%d\n",addr);
	return 0;
}
	













