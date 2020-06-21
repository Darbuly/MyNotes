



/**
 * AdList_DFS.c
 * 邻接矩阵实现 图的深度遍历
 * @author Darbuly 2018-2019
 * @copyright 2018-2019 Darbuly
 */




#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



#define VRType int
#define InfoType int
#define VertexType char
#define MAX_VERTEX_NUM 20
#define MAX_VALUE 0

typedef enum{DG,DN,AG,AN}GraphKind;

typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arc;
	int vernum,arcnum;
	GraphKind kind;
}MGraph;

void g_create(MGraph *graph)
{
	int num;
	int i,j,k;
	char c;
	
	printf("Please enter the num of vertex:\n");
	scanf("%d",&graph->vernum);
	getchar();
	printf("Please enter vertex infomations:\n");
	for(i=0;i<graph->vernum;i++)
	{
		scanf("%c",&graph->vexs[i]);
		getchar();
	}

	for(i=0;i<graph->vernum;i++)
		for(j=0;j<graph->vernum;j++)
			graph->arc[i][j].adj = MAX_VALUE;

	graph->arcnum = 0;

	for(i=0;i<graph->vernum;i++)
	{
		printf("Please enter vertex nextto the %c ,and end by #\n",graph->vexs[i]);
		for(j=0;j<graph->vernum;j++)
		{
			scanf("%c",&c);
			if(c=='#')
			{
				getchar();
				break;
			}
			//scanf("%d",&num);
			for(k=0;k<graph->vernum;k++)
			{
				if(graph->vexs[k]!=c)
					continue;
				//graph->arc[i][k].adj=num;
				graph->arc[i][k].adj=1;
				graph->arcnum++;
			}
			getchar();
		}
	}
	graph->arcnum /=2;
	
	printf("\n");
	for(i=0;i<graph->vernum;i++)
	{
		for(j=0;j<graph->vernum;j++)
		{
			printf("%d ",graph->arc[i][j].adj);
		}
		printf("\n");
	}
}
static void dfs_graph(MGraph *graph,bool visited[],const int i);

void g_depth_first_search(MGraph *graph)
{
	bool visited[graph->vernum];
	int i;
	for(i=0;i<graph->vernum;i++)
		visited[i]=false;
	visited[0]=true;
	dfs_graph(graph,visited,0);
	printf("\n");
}		
static void dfs_graph(MGraph *graph,bool visited[],const int i)
{
	int j;
	printf("%c\t",graph->vexs[i]);
	for(j=0;j<graph->vernum;j++)
	{
		if(graph->arc[i][j].adj != MAX_VALUE && !visited[j])
		{
			visited[j]=true;
			dfs_graph(graph,visited,j);
		}
	}
}

int main()
{	MGraph graph;
	g_create(&graph);
	g_depth_first_search(&graph);
	return 0;
}











