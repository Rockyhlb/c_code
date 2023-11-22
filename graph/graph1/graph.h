#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitInt 0
#define MVNum 100

#define ERROR -1

typedef int ArcType;

bool visited[MVNum] = { false };//����һ��������飬����ֵΪ��false��
								//ע��c�����н���bool����������Ҫ����stdbool.hͷ�ļ���
typedef struct
{
	ArcType vexs[MVNum];    //�����
	int arcs[MVNum][MVNum];		//�ڽӾ���
	int vexnum, arcnum;		//ͼ�ĵ�ǰ�������ͱ���
}AMGraph;

int locate(AMGraph *G, ArcType e);	//��λ
int create(AMGraph *G);			//����ͼ

void DFS_AM(AMGraph *G, ArcType v);	//DFS��ȱ���