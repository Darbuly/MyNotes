






/**
 * kruskal.c  克鲁斯卡尔算法
 *
 * @auther Darbuly  2018-2019
 * @copyright 2018-2019 Darbuly
 * 
 */














#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_VERTEX_NUM 20

typedef struct 
{
	int begin;
	int end;
	int weight;
}Edge[MAX_VERTEX_NUM];

typedef struct 
{
	Edge edge;
	int vexnum,arcnum;
}Graph;

void CreateGraph(Graph* G)
{
	int i;
	
	printf("Please enter vexnum and arcnum:\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	getchar();
	
	printf("Please enter the begin,end,weight by asc order:\n");
	
	for(i=0;i<G->arcnum;i++)
	{
		scanf("%d %d %d",&G->edge[i].begin,&G->edge[i].end,&G->edge[i].weight);
		getchar();
	}
	
	for(i=0;i<G->arcnum;i++)
	{
		printf("%d---->%d:%d\n",G->edge[i].begin,G->edge[i].end,G->edge[i].weight);
		
	}
}


int Find(int *parent,int f)  //根据当前  数组    一个顶点的下标   
{
	while(parent[f]>0)
	{
		f = parent[f];
	}
	return f;
}

int MiniSpanTree_Kruskal(Graph G)
{
	int i,n,m;
	int parent[MAX_VERTEX_NUM];		//作用：1.避免形成环    2.通过它可以表示某些边   3.通过它可以表示一颗树

	for(i=0;i<G.vexnum;i++)		//初始化   数组
	{
		parent[i]=0;
	}
	
	for(i=0;i<G.arcnum;i++)
	{
		n=Find(parent,G.edge[i].begin);  //n是边的开始
		m=Find(parent,G.edge[i].end);	//n是边的结束
		
		if(n!=m)
		{
			parent[n]=m;
			printf("(%d, %d) %d",G.edge[i].begin,G.edge[i].end,G.edge[i].weight);
		}
	}
}		








int main()
{
	Graph G;
	CreateGraph(&G);
	MiniSpanTree_Kruskal(G);
	printf("Kruskal.c test\n");
	return 0;
}













