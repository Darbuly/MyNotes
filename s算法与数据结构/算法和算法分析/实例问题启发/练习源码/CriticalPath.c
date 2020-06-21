
/**
 *
 * CriticalPath.c   关键路径算法
 *
 * @author Darbuly 970073804@QQ.com  2018-2019
 * @copyright 2018-2019
 * 
 *
 * 
 */



#include <stdio.h>
#include <stdlib.h>


#define VRType int
#define InfoType int
#define VertexType char
#define MAX_VERTEX_NUM 20

#define OK 1
#define ERROR 0

typedef int Status;

typedef enum {DG,DN,AG,AN}GraphKind;

typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	int weight;
	InfoType *info;
}ArcNode;

typedef struct VNode{
	VertexType data;
	int in;
	ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;
	GraphKind kind;
}ALGraph;

int *etv,*ltv;
int *stack2;
int top2;

void InsertNode(ALGraph *G,int i,int j,int weight)
{
	printf("\ni=%d,j=%d\n",i,j);
	ArcNode *ptrArcNode = (ArcNode *)malloc(sizeof(ArcNode));
	
	ptrArcNode->adjvex = j;
	ptrArcNode->nextarc = G->vertices[i].firstarc;
	ptrArcNode->weight = weight;
	G->vertices[i].firstarc = ptrArcNode;
	G->vertices[j].in++;
	printf("%c-%c,weight:%d \n",G->vertices[i].data,G->vertices[j].data,ptrArcNode->weight);

}

void CreateALGraph(ALGraph *G)
{
	int i,j,k,weight;
	if(NULL==G) G = (ALGraph*)malloc(sizeof(ALGraph));
	
	printf("Please input the vexnum and arcnum:\n");
	scanf("%d%d",&G->vexnum,&G->arcnum);
	getchar();
	
	printf("Please input the Vertices:\n");
	for(i=0;i<G->vexnum;i++)
	{
		printf("Vertex %d:",i+1);
		scanf("%c",&G->vertices[i].data);
		G->vertices[i].in = 0;
		G->vertices[i].firstarc = NULL;
		getchar();
	}
	
	for(k=0;k<G->arcnum;k++)
	{
		printf("Please input (vi,vj,weight) vertex:\n");
		scanf("%d%d%d",&i,&j,&weight);
		
		InsertNode(G,i,j,weight);
	}
}
	
void ShowALGraph(ALGraph *G)
{
	ArcNode *ptrArcNode;
	int i;

	printf("\nShowALGraph\n");
	for(i=0;i<G->vexnum;i++)
	{
		printf("The Vertex %d is %c, in %d:",i+1,G->vertices[i].data,G->vertices[i].in);
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


Status ToplogicalSort(ALGraph G)
{
	ArcNode *e;
	int i,k,gettop;
	int top = 0;
	int count = 0;
	int *stack;

	stack = (int*)malloc(G.vexnum*sizeof(int));
	
	printf("\nToplogicalSort\n");	
	for(i=0;i<G.vexnum;i++)
	{
		if(0==G.vertices[i].in)
		{
		//	printf("\ntop=%d\n",i);
			stack[++top] = i;
		}
	}


	top2 = 0;
	etv = (int*)malloc(G.vexnum*sizeof(int));
	for(i=0;i<G.vexnum;i++)
	{
		etv[i] = 0;
	}	
	stack2 = (int*)malloc(G.vexnum*sizeof(int));
	
	while(0!=top)
	{
		gettop = stack[top--];
		stack2[++top2] = gettop;
		count++;
	
		for(e=G.vertices[gettop].firstarc;e;e=e->nextarc)
		{
			k = e->adjvex;
			
			if(!(--G.vertices[k].in))
			{
				stack[++top]=k;
			}
		
		//	printf("\n%d\n",etv[gettop]+e->weight);
			if( (etv[gettop] + e->weight)>etv[k])
			{
				etv[k] = etv[gettop] + e->weight;
			}
		}
	}

	if(count < G.vexnum)
	{
		return ERROR;
	}
	else
	{
		printf("\netv :\n");
		
		for(i=0;i<G.vexnum;i++)
		{
			printf("%d\t",etv[i]);
		}
		printf("\n");
		return OK;
	}
}
	

void CriticalPath(ALGraph G)
{
	ArcNode *e;
	int i,gettop,k,j;
	int ete,lte;

	ToplogicalSort(G);
	
	ltv = (int*)malloc(G.vexnum*sizeof(int));

	for(i=0;i<G.vexnum;i++)
	{
		ltv[i] = etv[G.vexnum-1];
	}
	
	while(0 != top2)
	{
		gettop = stack2[top2--];
		for(e=G.vertices[gettop].firstarc;e;e=e->nextarc)
		{
			k = e->adjvex;
			if( (ltv[k] - e->weight) < ltv[gettop])
			{
				ltv[gettop] = ltv[k] - e->weight;
			}
		}
	}
	
	printf("\nltv======:\n");
	for(i=0;i<G.vexnum;i++)
	{
		printf("%d\t",ltv[i]);
	}
	printf("\n");

	for(j=0;j<G.vexnum;j++)
	{
		for(e=G.vertices[j].firstarc;e;e= e->nextarc)
		{
			k = e->adjvex;
			ete = etv[j];
			lte = ltv[k] - e->weight;
			
			if(ete == lte)
			{
				printf("<v%c, v%c> length: %d , \n",G.vertices[j].data,G.vertices[k].data,e->weight);
			}
		}
	}

	
}
	
	

int main()
{
	printf("CriticalPath.c Test\n");
	ALGraph G;
	CreateALGraph(&G);
	ShowALGraph(&G);
//	ToplogicalSort(G);
	CriticalPath(G);
	
	return 0;
}

