#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

// 定义作业结构体
typedef struct {
	int Pid;           // 作业 ID
	int arrival_time; // 到达时间
	int service_time; // 服务时间
	int finish_time;  // 完成时间
	int turnaround_time; // 周转时间
	float response_ratio; // 响应比
} Job;

int main() {
	int n;
	printf("请输入作业数：");
	scanf("%d", &n);

	// 动态分配作业数组空间
	Job *jobs = (Job*)malloc(n * sizeof(Job));

	// 输入每个作业的信息
	for (int i = 0; i < n; i++) {
		printf("请输入第 %d 个作业的到达时间和服务时间：", i + 1);
		scanf("%d %d", &jobs[i].arrival_time, &jobs[i].service_time);
		jobs[i].Pid = i + 1;
	}

	// 初始化第一个作业的完成时间和响应比
	jobs[0].finish_time = jobs[0].arrival_time + jobs[0].service_time;
	jobs[0].turnaround_time = jobs[0].finish_time - jobs[0].arrival_time;
	jobs[0].response_ratio = (float)jobs[0].turnaround_time / jobs[0].service_time;

	// 计算每个作业的完成时间、周转时间和响应比
	for (int i = 1; i < n; i++) {
		int prev_finish_time = jobs[i - 1].finish_time;
		int min_service_time = jobs[i].service_time;
		int min_index = i;

		// 找到剩余作业中服务时间最短的作业
		for (int j = i; j < n; j++) {
			if (jobs[j].arrival_time <= prev_finish_time && jobs[j].service_time < min_service_time) {
				min_service_time = jobs[j].service_time;
				min_index = j;
			}
		}

		// 完成时间等于上一个作业的完成时间加上服务时间
		jobs[min_index].finish_time = prev_finish_time + jobs[min_index].service_time;
		// 周转时间等于完成时间减去到达时间
		jobs[min_index].turnaround_time = jobs[min_index].finish_time - jobs[min_index].arrival_time;
		// 响应比等于（周转时间+服务时间）/ 服务时间
		jobs[min_index].response_ratio = (float)jobs[min_index].turnaround_time / jobs[min_index].service_time;

		// 交换作业顺序，将当前作业放在已完成的作业后面
		Job temp = jobs[min_index];
		for (int k = min_index; k > i; k--) {
			jobs[k] = jobs[k - 1];
		}
		jobs[i] = temp;
	}

	// 输出每个作业的信息
	printf("作业  到达时间  服务时间  完成时间  周转时间  响应比\n");
	for (int i = 0; i < n; i++) {
		printf("%3d%10d%10d%10d%10d%10.2f\n", jobs[i].Pid, jobs[i].arrival_time, jobs[i].service_time, jobs[i].finish_time, jobs[i].turnaround_time, jobs[i].response_ratio);
	}

	// 释放作业数组空间
	free(jobs);
	return 0;
}