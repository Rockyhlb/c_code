#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define N 10

//  响应比R定义如下: R=( W+T)/T =1＋W / T -- 其中,T为该作业需要的执行时间,W为作业在后备状态队列中的等待时间

typedef struct table
{
	char name[10];				// 作业名
	int in_well;				// 进入输入井时间
	int run_time;				// 运行时间

	int begin_run;			// 开始运行时间 == 上一个作业运行结束时间
	int end_run;			// 结束时间 == 开始运行时间 + 运行时间
	int turnover_time;		// 周转时间 == 结束时间 - 开始运行时间

	int response;
}job_tab;

void init(job_tab job[], int n)
{
	printf("请输入%d个作业信息：\n", n);
	printf("in_well run_time name\n");

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %s", &job[i].in_well, &job[i].run_time, &job[i].name);
		job[i].begin_run = 0.0;
		job[i].end_run = 0.0;
		job[i].turnover_time = 0.0;
	}
}

void print_table(job_tab job[], int n)
{
	int i = 0;
	printf("name\t in_well\t run_time\t begin_time\t end_time\t turnover_time\n");

	for (i = 0; i < n; i++)
	{
		printf("%4s\t%4d\t%4d\t%4d\t%4d\t%4d\n", job[i].name,job[i].run_time, job[i].begin_run, job[i].end_run, job[i].turnover_time);
	}
}

void swap(job_tab job[],int n)
{
	int i = 0;

	
}

float response_ratio(job_tab job[],int n)
{
	int i = 0,j= 0,temp;
	float average_time = 0.0,ratio1,ratio2;

	job[0].begin_run = job[0].in_well;
	job[0].end_run = job[0].begin_run + job[0].run_time;
	job[0].turnover_time = job[0].end_run - job[0].begin_run;
	average_time = job[0].turnover_time;

	for (i = 1; i < n; i++)
	{
		j = i + 1, temp = i;

		if (job[i].in_well <= job[i - 1].end_run)
		{
			ratio1 = (float)(job[i].end_run - job[i].in_well) / job[i].run_time;
		}
	}
}

int main()
{
	int n = 0;
	job_tab tables[N];
	printf("请输入作业总数:>>");
	scanf("%d", &n);
	init(tables, n);
	print_table(tables,n);

	//开始进行作业的调度
	swap(tables,n);
	return 0;
}
