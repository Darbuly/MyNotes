
/**
 * floyd.c 弗洛伊德算法    
 * @author Darbuly  2018-2019
 * @copyright Darbuly  
 */






#include <stdio.h>
#include <stdlib.h>


#define VRType int
#define VertexType char
#define InfoType int
#define MAX_VERTEX_NUM 20
#define MAX_VALUE 65535



typedef enum{DG,DN,AG,AN}GraphKind;
typedef int Pathmatirx[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}AreCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

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
	
	printf("Please enter the vexnum of vertex:\n");
	scanf("%d",&graph->vexnum);
	getchar();
	printf("Please enter vertex infomations:\n");
	for(i=0;i<graph->vexnum;i++)
	{
		scanf("%c",&graph->vexs[i]);
		getchar();
	}
	
	for(i=0;i<graph->vexnum;i++)
		for(j=0;j<graph->vexnum;j++)
			graph->arc[i][j].adj = MAX_VALUE;


	graph->arcnum = 0;
	
	for(i=0;i<graph->vexnum;i++)
	{
		printf("Please enter vertex nextto the %c ,and end by #\n",graph->vexs[i]);
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
		

void ShortestPath_Floyd(MGraph G,Pathmatirx *P,ShortPathTable *D)
{
	int v,w,k;
	
	for(v=0;v<G.vexnum;v++)
	{
		for(w=0;w<G.vexnum;w++)
		{
			(*D)[v][w] = G.arc[v][w].adj;
			(*P)[v][w] = w;
		}
	}
	
	for(k=0;k<G.vexnum;k++)
	{
		for(v=0;v<G.vexnum;v++)
		{
			for(w=0;w<G.vexnum;w++)
			{
				if( (*D)[v][w] > (*D)[v][k] + (*D)[k][w])
				{
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];
				}
			}
		}
	}
	
	for(k=0;k<G.vexnum;k++)
	{
		for(v=0;v<G.vexnum;v++)
		{
			printf("%d\t",(*D)[k][v]);
		}
		printf("\n");
	}
	printf("\n");

	for(k=0;k<G.vexnum;k++)
	{
		for(v=0;v<G.vexnum;v++)
		{
			printf("%d\t",(*P)[k][v]);
		}
		printf("\n");
	}
}	

int main()
{
	MGraph graph;
	Pathmatirx P;
	ShortPathTable D;
	g_create(&graph);
	ShortestPath_Floyd(graph,&P,&D);
	printf("FLOYD.C TEST\n");
	return 0;
}





























