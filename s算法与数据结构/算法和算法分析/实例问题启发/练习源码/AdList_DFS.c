
/**
 * AdList_DFS.c
 * 邻接表实现 图的深度遍历
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

typedef enum{DG,DN,AG,AN}GraphKind;
typedef struct ArcNode
{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;
}ArcNode;


typedef struct VNode
{
	VertexType data;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];


typedef struct{
	AdjList vertices;
	int vexnum,arcnum;
	GraphKind kind;
}ALGraph;

void InsertNode(ALGraph *G,int i,int j)
{
	printf("\ni=%d,j=%d\n`",i,j);
	ArcNode *ptrArcNode = (ArcNode*)malloc(sizeof(ArcNode));
	
	ptrArcNode->adjvex = j;
	ptrArcNode->nextarc = G->vertices[i].firstarc;
	G->vertices[i].firstarc = ptrArcNode;
	printf("%c-%c\n",G->vertices[i].data,G->vertices[j].data);
	
	ptrArcNode = (ArcNode*)malloc(sizeof(ArcNode));
	ptrArcNode->adjvex = i;
	ptrArcNode->nextarc = G->vertices[j].firstarc;
	G->vertices[j].firstarc = ptrArcNode;
}

void CreateALGraph(ALGraph *G)
{
	int i,j,k;
	if(G==NULL) G =  (ALGraph*)malloc(sizeof(ALGraph));
	
	printf("Please input the vexnum and arcnum:\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	getchar();
	
	printf("Please input the Vertices:\n");
	for (i=0;i<G->vexnum;i++)
	{
		printf("Vertex %d:",i+1);
		scanf("%c",&G->vertices[i].data);
		G->vertices[i].firstarc=NULL;
		getchar();
	}
	
	for(k=0;k<G->arcnum;k++)
	{
		printf("Please input  (vi,vj) vertex:\n");
		scanf("%d%d",&i,&j);
		
		InsertNode(G,i,j);
	}	
}

void ShowALGraph(ALGraph *G)
{
	ArcNode *ptrArcNode;
	int i;
	for(i=0;i<G->vexnum;i++)
	{
		printf("The Vertex %d is %c :",i+1,G->vertices[i].data);
		ptrArcNode = G->vertices[i].firstarc;
		while(1)	
		{
			if(ptrArcNode==NULL)break;
			printf("->%c",G->vertices[ptrArcNode->adjvex]);
			if(ptrArcNode->nextarc==NULL)break;
			ptrArcNode = ptrArcNode->nextarc;
		}
		printf("\n");
	}
}
void DFS(ALGraph *G,bool visited[],int i)
{
	ArcNode *ptrArcNode;					//新建工作指针ptrArcNode
	visited[i]=true;						//标记访问
	printf("%c\t",G->vertices[i].data);		
	ptrArcNode = G->vertices[i].firstarc;
	while(ptrArcNode)						//递归遍历，退出条件是工作指针不为空（邻接表某个顶点最右端是Null）
	{
		if(!visited[ptrArcNode->adjvex])DFS(G,visited,ptrArcNode->adjvex);		//如果没被访问，继续以它为顶点，递归遍历
		ptrArcNode = ptrArcNode->nextarc;
	}
}
void DFSTraverse(ALGraph *G)
{
	int i;
	bool visited[MAX_VERTEX_NUM];					//顶点访问记录数组
	for(i=0;i<G->vexnum;i++)						//初始化
		visited[i]==false;
	for(i=0;i<G->vexnum;i++)						
	{
		if(!visited[i]) DFS(G,visited,i);
	}
	printf("\n");
}



int main()
{
	ALGraph G;
	CreateALGraph(&G);
	ShowALGraph(&G);
	DFSTraverse(&G);
	return 0;
}
