#define _CRT_SECURE_NO_WARNINGS 

#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#define False 0
#define Ture 1
#define Process_num 5

typedef struct {
	int r1;
	int r2;
	int r3;
}Resource;

//最大需求矩阵
Resource Max[Process_num] = { {6,4,3},{3,2,4},{9,0,2},{2,2,2},{3,4,3} };
//已分配资源数矩阵
Resource Allocation[Process_num] = { {1,1,0},{2,0,1},{4,0,2},{2,1,1},{0,1,2} };
//需求矩阵
Resource Need[Process_num] = { {5,3,3},{1,2,3},{5,0,1},{0,1,1},{3,3,1} };
//可用资源向量
Resource Available = { 3,3,2 };
int safe[Process_num];

//试探分配
void ProbeAlloc(int process, Resource* res)
{
	Available.r1 -= res->r1;
	Available.r2 -= res->r2;
	Available.r3 -= res->r3;

	Allocation[process].r1 += res->r1;
	Allocation[process].r2 += res->r2;
	Allocation[process].r3 += res->r3;

	Need[process].r1 -= res->r1;
	Need[process].r2 -= res->r2;
	Need[process].r3 -= res->r3;
}
//若试探分配后进入不安全状态，将分配回滚
void RollBack(int process, Resource* res)
{
	Available.r1 -= res->r1;
	Available.r2 -= res->r2;
	Available.r3 -= res->r3;

	Allocation[process].r1 += res->r1;
	Allocation[process].r2 += res->r2;
	Allocation[process].r3 += res->r3;

	Need[process].r1 += res->r1;
	Need[process].r2 += res->r2;
	Need[process].r3 += res->r3;
}
//安全性检查
int SafeCkeck()
{
	Resource Work = Available;
	int Finish[Process_num] = { False,False,False,False,False };
	int i, j = 0;
	for (i = 0; i < Process_num; i++)
	{
		//是否已检查过
		if (Finish[i] == False)
		{
			//是否有足够的资源分配给该进程
			if (Need[i].r1 <= Work.r1 && Need[i].r2 <= Work.r2 && Need[i].r3 <= Work.r3)
			{
				//有则使其执行完成，并将已分配给该进程的资源全部回收
				Work.r1 += Allocation[i].r1;
				Work.r2 += Allocation[i].r2;
				Work.r3 += Allocation[i].r3;
				Finish[i] = Ture;
				safe[j++] = i;
				i = -1;
			}
		}
	}
	//是否所有进程的Finish向量都为true则处于安全状态1，否则为不安全
	for (i = 0; i < Process_num; i++)
	{
		if (Finish[i] == False)
		{
			return Ture;
		}
	}
}
//资源分配请求
int Request(int process, Resource* res)
{
	//request向量需小于Need矩阵中对应的向量
	if (res->r1 <= Need[process].r1 && res->r2 <= Need[process].r2 && res->r3 <= Need[process].r3)
	{
		//request向量需小于Available向量
		if (res->r1 <= Available.r1 && res->r2 <= Available.r2 && res->r3 <= Available.r3)
		{
			//试探分配
			ProbeAlloc(process, res);
			//如果安全检查成立，则请求成功，否则将分配回滚并返回失败
			if (SafeCkeck())
			{
				return Ture;
			}
			else
			{
				printf("安全性检查失败。原因：系统将进入不安全状态，有可能引起死锁。\n");
				printf("正在回滚……\n");
				RollBack(process, res);
			}
		}
		else
		{
			printf("安全性检查失败。原因：请求向量大于可利用资源向量。\n");
		}
	}
	else
	{
		printf("安全性检查失败。原因：请求向量大于需求向量");
	}
	return False;
}

//输出资源分配表
void PrintTable()
{
	printf("\t\t\t*********资源分配表*********\n");
	printf("Process     Max     |    Allocation  |     Need      |  Available\n");
	printf("       r1   r2   r3 |  r1   r2   r3  |  r1   r2   r3 |  r1   r2   r3\n");
	printf(" P0    %d    %d    %d  |  %d    %d    %d   |   %d    %d    %d |  %d    %d    %d\n", 
		Max[0].r1, Max[0].r2, Max[0].r3, Allocation[0].r1, Allocation[0].r2, Allocation[0].r3, 
		Need[0].r1, Need[0].r2, Need[0].r3, Available.r1, Available.r2, Available.r3);
	printf(" P1    %d    %d    %d  |  %d    %d    %d   |   %d    %d    %d |\n",
		Max[1].r1, Max[1].r2, Max[1].r3, Allocation[1].r1, Allocation[1].r2, 
		Allocation[1].r3, Need[1].r1, Need[1].r2, Need[1].r3);
	printf(" P2    %d    %d    %d  |  %d    %d    %d   |   %d    %d    %d |\n", 
		Max[2].r1, Max[2].r2, Max[2].r3, Allocation[2].r1, Allocation[2].r2, 
		Allocation[2].r3, Need[2].r1, Need[2].r2, Need[2].r3);
	printf(" P3    %d    %d    %d  |  %d    %d    %d   |   %d    %d    %d |\n", 
		Max[3].r1, Max[3].r2, Max[3].r3, Allocation[3].r1, Allocation[3].r2, 
		Allocation[3].r3, Need[3].r1, Need[3].r2, Need[3].r3);
	printf(" P4    %d    %d    %d  |  %d    %d    %d   |   %d    %d    %d |\n", 
		Max[4].r1, Max[4].r2, Max[4].r3, Allocation[4].r1, Allocation[4].r2, 
		Allocation[4].r3, Need[4].r1, Need[4].r2, Need[4].r3);
	printf("\n");
}

int main()
{
	int ch;
	printf("先检查初始状态是否安全。\n");
	if (SafeCkeck())
	{
		printf("系统处于安全状态。\n");
		printf("安全序列是{P%d,P%d,P%d,P%d,P%d}.\n", safe[0], safe[1], safe[2], safe[3], safe[4]);
	}
	else
	{
		printf("系统处于不安全状态。程序将退出……\n");
		printf("执行完毕。\n");
		return 0;
	}
	do
	{
		int process;
		Resource res;
		PrintTable();
		printf("请依次输入请求分配的进程和对三类资源的请求数量：");
		scanf("%d %d %d %d", &process, &res.r1, &res.r2, &res.r3);
		if (Request(process, &res))
		{
			printf("分配成功。\n");
			printf("安全序列是{P%d,P%d,P%d,P%d,P%d}.\n", safe[0], safe[1], safe[2], safe[3], safe[4]);
		}
		else
		{
			printf("分配失败。\n");
		}
		printf("是否继续分配？（Y/N）");
		ch = getchar();
		ch = getchar();
	} while (ch == 'Y' || ch == 'N');
	return 0;
}
