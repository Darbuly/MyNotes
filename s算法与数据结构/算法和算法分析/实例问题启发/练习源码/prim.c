


/**
 * prim.c   普里姆算法(邻接矩阵实现)
 * @author Darbuly 2018-2019
 * @copyright 2018-2019 Darbuly
 */







#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>//没用的！


#define VRType int
#define InfoType int 
#define VertexType char
#define MAX_VERTEX_NUM 20
#define MAX_VALUE 65535


typedef enum{DG,DN,AG,AN}GraphKind;

typedef struct ArcCell{
	VRType adj;
	InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct 
{
	VertexType vexs[MAX_VERTEX_NUM];//顶点文本数组
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
		scanf("%c",&graph->vexs[i]);//顶点文本数组的创建
		getchar();
	}
	
	for(i=0;i<graph->vexnum;i++)
		for(j=0;j<graph->vexnum;j++)
			graph->arc[i][j].adj=MAX_VALUE;//初始化矩阵的内容   全部为65535

	graph->arcnum = 0;
	
	for(i=0;i<graph->vexnum;i++)
	{
		printf("Please enter vertex nextto the %c ,and end by #\n",graph->vexs[i]);
		for(j=0;j<graph->vexnum;j++)
		{
			scanf("%c",&c);//你要输入的目标顶点  如  A
			if(c=='#')
			{
				getchar();
				break;
			}
			scanf("%d",&num);//路径长度
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
		


void MinSpanTree_Prim(MGraph G)
{
	int min,i,j,k;

	int adjvex[MAX_VERTEX_NUM];
	int lowcost[MAX_VERTEX_NUM];

	printf("\nMinSpanTree_Prim\n");
	lowcost[0]=0;//源头到目的顶点的最小成本记录器 //记录着当前研究对象的所有边，通过step3来更新，step1来去除最小边
	adjvex[0]=0;

	for(i=1;i<G.vexnum;i++)//从1到9
	{
		lowcost[i] = G.arc[0][i].adj;//普利姆算法  是需要知道从哪里开始   我这里默认为0开始，也就是V0
		adjvex[i] = 0;//应该是标志处理器
	}

	for(i=1;i<G.vexnum;i++)//从1到9
	{
		min = MAX_VALUE;
		j=1;
		k=0;
		//step1:找出当前研究对象lowcost最小权值的边
		while(j<G.vexnum)//1<9
		{
			if(lowcost[j]!=0 && lowcost[j]<min)//j从1~8   刚好0是VO   1~8是V1~V8，这里的if判断的是   把所有能和V0连接的顶点找出来
			{
				min = lowcost[j];//找出最小全小权值的边
				k=j;
			}
			j++;//j从1~9
		}
		//step2:找一条，标一条，归0
		printf("(%d,%d)",adjvex[k],k);//k就是记录着当前顶点的最小权值的边所连接的顶点的下标
		lowcost[k]=0;		//作用就是   该边已经用过了，也就是0,0是不需要再比较了，不然等会第二次遍历还会是它，死循环了
		
		//step3:整改研究对象
		for(j=1;j<G.vexnum;j++)//从1到9
		{
			if(lowcost[j]!=0 && G.arc[k][j].adj <lowcost[j])
			{
				lowcost[j] = G.arc[k][j].adj;//k=1,j=8
				adjvex[j]=k;//adjvex[8]=1
			}
		}
	}
	printf("\n");
}
				
int main()
{
	MGraph graph;
	printf("PRIM.C TEST\n");
	g_create(&graph);
	
	MinSpanTree_Prim(graph);
	return 0;
}













