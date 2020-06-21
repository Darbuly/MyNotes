/**
 * index_KMP.c   KMP算法研究
 *
 *
 *
 * 
 */




#include <stdio.h>


typedef char* string;

int get_next(string T,int *next)
{
	int i=1;
	int j=0;
	next[1]=0;		//先预备当1就失败时，我也要i++ j++，为了j加之后为1  就j=next[1]=0
	
	while(i<T[0])	//
	{
		if(0==j||T[i]==T[j])		//我要如何计算相同前缀的长度？就得需要用两个工作指针对同一个串通过位置不同分出两个对象，一个是主串 就是当前工作指针i来表示
									//一个是模式串  用j来表示，当分开的这两个T[i]！=T[j]，同样既可以直接用已经写好的next[i]因为i才是表示当前失配的
		{
			i++;
			j++;				//j代表模式串相同前缀的长度-1
			next[i]=j;			//所有已经成功匹配的，我边计算长度 边给它布防下一个失败应该能跳到的next所以这个i是先i++之后才写的，为啥用i？因为我边工作边写到哪，就得用当前工作指针来表示
		}
		else
		{
			j=next[i];			//匹配失败就是直接跳下一个位，本质是通过一个在当前的指针，一个在前面的指针 来分离两个串   两个串如果出现相同  就代表着前后缀相同，刚好指针记录了长度，我的目的就是要  当前失配就转到[相同前缀的长度-1]
		}
	}
}


/**
 * [Index_KMP description]
 * @Author   Darbuly:970073804@qq.com
 * @DateTime 2019-12-30T19:27:56+0800
 * @param    S                        匹配串
 * @param    T                        模式串
 * @param    pos                      开始匹配位置
 * @return                            [description]
 */
int Index_KMP(string S, string T,int pos)
{
	int i = pos;
	int j = 1;
	int next[255];
	get_next(T,next);
	while(i<=S[0]&&j<=T[0])		//如何遍历两个串？答：通过数组第一个留空记录长度，while循环是否两个都到底，可以省去getlength的麻烦
	{
		if(0==j||S[i]==T[j])	//什么情况要两个指针要同步继续下一个元素匹配（什么时候要i++和j++）？1.就是两个串的元素正确匹配时  2.就是当j=0时，意味着模式串第一个就不匹配，而next【1】=0,
								//j=0之后加1，代表下一模式串从1开始匹配（0是长度），i在不匹配之后+1代表开始下一个元素匹配模式串的第一个字符  
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];			//如2号位匹配失败 且next[2]=1  j=1  下一次比较 主串[当前] 与  模式[1]号位
		}
	}

	if(j>T[0])					//如何判断KMP成功？就是当模式串都已经到底了的时候，如何判断KMP失败？就是匹配串都走完了  你的模式串还是没走完  返回0
	{
		return i-T[0];			//如果KMP成功 如何返回正确匹配的开始位置？就是已经跟着模式串一块递增的匹配串工作指针i通过减去模式串的长度就可以回退到正确匹配的开始位置了
	}
	else
	{
		return 0;
	}

}

int main()
{
	char s[255] = " ababaaaba";
	char t[255] = " aaa";
	int next[255];
	
	s[0]=9;
	t[0]=3;

	printf("%d\n",Index_KMP(s,t,1));
	return 0;
}












































