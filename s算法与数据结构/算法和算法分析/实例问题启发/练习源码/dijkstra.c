





/**
 * dijkstra.c   迪杰斯特拉算法
 *
 * @author Darbuly 970073804@qq.com
 * @copyright 2018-2019
 */



#include <stdio.h>
#include <stdlib.h>

#define VRType int
#define InfoType int
#define VertexType char
#define MAX_VERTEX_NUM 20
#define MAX_VALUE 65535


typedef enum{DG,DN,AG,AN}GraphKind; 

typedef int Patharc[MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];
typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct 
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arc;
	int vexnum,arcnum;
	GraphKind kind;
}MGraph;

void g_create(MGraph *graph)
{
	int num;
	int i,j,k;
	char c;
	
	printf("Please enter the number of vertex:\n");
	scanf("%d",&graph->vexnum);
	getchar();
	printf("Please enter the vertex infomations:\n");
	for(i=0;i<graph->vexnum;i++)
	{
		scanf("%c",&graph->vexs[i]);
		getchar();
	}
	
	for(i=0;i<graph->vexnum;i++)
		for(j=0;j<graph->vexnum;j++)
			graph->arc[i][j].adj=MAX_VALUE;

	graph->arcnum=0;

	for(i=0;i<graph->vexnum;i++)
	{
		printf("Please enter vertex nextto the %c , and end by #\n",graph->vexs[i]);
		for(j=0;j<graph->vexnum;j++)
		{
			scanf("%c",&c);
			if('#'==c)
			{
				getchar();
				break;
			}
			scanf("%d",&num);
			for(k=0;k<graph->vexnum;k++)
			{
				if(graph->vexs[k]!=c)
					continue;
				graph->arc[i][k].adj = num;
				graph->arcnum++;
			}
			getchar();
		}
	}

	graph->arcnum /=2;

	printf("\n");
	
	for(i=0;i<graph->vexnum;i++)
	{
		for(j=0;j<graph->vexnum;j++)
		{
			printf("%5d\t",graph->arc[i][j].adj);
		}
		printf("\n");
	}
}



void ShortestPath_Dijkstra(MGraph G,int V0,Patharc *P,ShortPathTable *D)
{
	int v,w,k,min;
	int final[MAX_VERTEX_NUM];
	
	for(v=0;v<G.vexnum;v++)
	{
		final[v]=0;
		(*D)[v] = G.arc[V0][v].adj;
		(*P)[v] = 0;
	}

	(*D)[V0] = 0;
	final[V0] = 1;

	for(v=1;v<G.vexnum;v++)
	{
		min = MAX_VALUE;
		for(w=0;w<G.vexnum;w++)
		{
			if(!final[w] && (*D)[w]<min)
			{
				k = w;
				min = (*D)[w];
			}	
		}	

		final[k] = 1;
		
		for(w=0;w<G.vexnum;w++)
		{	
			if(!final[w] && min+G.arc[k][w].adj< (*D)[w])
			{
				(*D)[w] = min + G.arc[k][w].adj;
				(*P)[w] = k;
			}
		}
	}
	
	printf("\n");
	for(v=0;v<G.vexnum;v++)
	{
		printf("%d\t",(*P)[v]);
	}
}


	






int main()
{
	MGraph graph;
	Patharc P;
	ShortPathTable D; 
	g_create(&graph);
	ShortestPath_Dijkstra(graph,0,&P,&D);
	printf("Dijkstra.c Test\n");
	return 0;
}















