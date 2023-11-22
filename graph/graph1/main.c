#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

int create(AMGraph *G)
{
	int venum = 0, arnum = 0;  //总顶点和总边数
	ArcType v1, v2;		//一条边所依附的顶点
	int i = 0, j = 0;

	printf("请输入该图的总顶点和总边数：");

	while (scanf("%d", &venum) && scanf("%d", &arnum))
	{
		G->vexnum = venum;
		G->arcnum = arnum;

		for (i = 0; i < G->vexnum; i++)
		{
			int data;
			printf("请输入第%d个顶点：",i+1);
			scanf("%d", &data);
			G->vexs[i] = data;
		}

		for (i = 0; i < G->vexnum; i++)
		{
			for (j = 0; j < G->vexnum; j++)
			{
				G->arcs[i][j] = InitInt;	//初始化一个vexnum行vexnum列的矩阵
			}
		}

		printf("邻接矩阵初始化完成：\n");
		for (i = 0; i < G->vexnum; i++)
		{
			for (j = 0; j < G->vexnum; j++)
			{
				printf("%d\t",G->arcs[i][j]);
			}
			printf("\n");
		}

		for (int k = 0; k < G->arcnum; k++)
		{
			printf("请输入确定第%d条边的两个顶点：",k+1);
			scanf("%d",&v1);
			scanf("%d",&v2);

			i = locate(G, v1); j = locate(G, v2);	//确定v1,v2在G中的位置，
													//即顶点数组的下标
			G->arcs[i][j] = 1;  //若建立无向图，后面需加入G->arcs[j][i]=G->arcs[i][j]形成对称矩阵
		}

		printf("邻接矩阵生成完成：\n");
		for (i = 0; i < G->vexnum; i++)
		{
			for (j = 0; j < G->vexnum; j++)
			{
				printf("%d\t", G->arcs[i][j]);
			}
			printf("\n");
		}

		for (i = 0; i < G->vexnum; i++)
		{
			visited[i] = false;
		}

		ArcType start = 0;
		printf("请输入进行深度遍历图的起点下标：");
		while (scanf("%d",&start))
		{
			DFS_AM(G, start);
		}
	}
	return 0;
}

int locate(AMGraph *G, ArcType e)
{
	for (int i = 0; i < G->vexnum; i++)
	{
		if (G->vexs[i] == e)
		{
			return i;
		}
	}
	return ERROR;
}

void DFS_AM(AMGraph *G, ArcType v)
{
	int  w = 0;
	printf("%d->",v+1);
	visited[v] = true;  //访问第v个顶点，并置对应数组空间为空！

	for (w = 0; w < G->vexnum; w++)  //依次检查邻接矩阵v所在的行！
	{
		if ((G->arcs[v][w] != 0) && (!visited[w]))
		{
			DFS_AM(G, w);		//G->arcs[v][w]！= 0表示w是v的临接点，
								//如果w未访问，则递归调用遍历算法！
		}
	}
}


int main()
{
	AMGraph g;
	create(&g);
}