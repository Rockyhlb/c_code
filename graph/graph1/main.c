#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"

int create(AMGraph *G)
{
	int venum = 0, arnum = 0;  //�ܶ�����ܱ���
	ArcType v1, v2;		//һ�����������Ķ���
	int i = 0, j = 0;

	printf("�������ͼ���ܶ�����ܱ�����");

	while (scanf("%d", &venum) && scanf("%d", &arnum))
	{
		G->vexnum = venum;
		G->arcnum = arnum;

		for (i = 0; i < G->vexnum; i++)
		{
			int data;
			printf("�������%d�����㣺",i+1);
			scanf("%d", &data);
			G->vexs[i] = data;
		}

		for (i = 0; i < G->vexnum; i++)
		{
			for (j = 0; j < G->vexnum; j++)
			{
				G->arcs[i][j] = InitInt;	//��ʼ��һ��vexnum��vexnum�еľ���
			}
		}

		printf("�ڽӾ����ʼ����ɣ�\n");
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
			printf("������ȷ����%d���ߵ��������㣺",k+1);
			scanf("%d",&v1);
			scanf("%d",&v2);

			i = locate(G, v1); j = locate(G, v2);	//ȷ��v1,v2��G�е�λ�ã�
													//������������±�
			G->arcs[i][j] = 1;  //����������ͼ�����������G->arcs[j][i]=G->arcs[i][j]�γɶԳƾ���
		}

		printf("�ڽӾ���������ɣ�\n");
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
		printf("�����������ȱ���ͼ������±꣺");
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
	visited[v] = true;  //���ʵ�v�����㣬���ö�Ӧ����ռ�Ϊ�գ�

	for (w = 0; w < G->vexnum; w++)  //���μ���ڽӾ���v���ڵ��У�
	{
		if ((G->arcs[v][w] != 0) && (!visited[w]))
		{
			DFS_AM(G, w);		//G->arcs[v][w]��= 0��ʾw��v���ٽӵ㣬
								//���wδ���ʣ���ݹ���ñ����㷨��
		}
	}
}


int main()
{
	AMGraph g;
	create(&g);
}