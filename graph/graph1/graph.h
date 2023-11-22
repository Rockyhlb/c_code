#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitInt 0
#define MVNum 100

#define ERROR -1

typedef int ArcType;

bool visited[MVNum] = { false };//建立一个标记数组，赋初值为“false”
								//注：c语言中建立bool型数组首先要导入stdbool.h头文件！
typedef struct
{
	ArcType vexs[MVNum];    //顶点表
	int arcs[MVNum][MVNum];		//邻接矩阵
	int vexnum, arcnum;		//图的当前顶点数和边数
}AMGraph;

int locate(AMGraph *G, ArcType e);	//定位
int create(AMGraph *G);			//创建图

void DFS_AM(AMGraph *G, ArcType v);	//DFS深度遍历