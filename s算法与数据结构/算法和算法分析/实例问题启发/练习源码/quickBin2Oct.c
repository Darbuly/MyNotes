
#include <stdio.h>



int main()
{
	char ch;
	int a=0;
	while(ch = getchar(),ch!='\n')//利用的是越到二进制数中低位，越少一次乘2   2^n+2^n-1
	a = a*2+(ch-'0');
	printf("%d\n",a);
	return 0;
}

