#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

struct process {
	int pid;  // 进程ID
	int arrival_time;  // 到达时间
	int burst_time;  // 运行时间
	int remaining_time;  // 剩余运行时间
	int turnaround_time;  // 周转时间
};

int main() {
	int n = 0, time_quantum = 0;
	printf("请输入进程数量和时间片大小：");
	scanf("%d %d", &n, &time_quantum);

	struct process *p = (struct process *) malloc(n * sizeof(struct process));
	int *waiting_time = (int *)malloc(n * sizeof(int));
	int *completion_time = (int *)malloc(n * sizeof(int));

	int total_waiting_time = 0, total_turnaround_time = 0;
	for (int i = 0; i < n; i++) {
		printf("请输入第%d个进程的到达时间和运行时间：", i + 1);
		scanf("%d%d", &p[i].arrival_time, &p[i].burst_time);
		p[i].pid = i + 1;
		p[i].remaining_time = p[i].burst_time;
		waiting_time[i] = 0;
		completion_time[i] = -1;
	}

	int current_time = 0, completed_processes = 0;
	while (completed_processes < n) {
		for (int i = 0; i < n; i++) {
			if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
				if (p[i].remaining_time <= time_quantum) {
					current_time += p[i].remaining_time;
					p[i].remaining_time = 0;
					completion_time[i] = current_time;
					completed_processes++;
				}
				else {
					current_time += time_quantum;
					p[i].remaining_time -= time_quantum;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		p[i].turnaround_time = completion_time[i] - p[i].arrival_time;
		total_waiting_time += p[i].turnaround_time - p[i].burst_time;
		total_turnaround_time += p[i].turnaround_time;
	}

	printf("进程ID\t到达时间\t运行时间\t完成时间\t周转时间\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, completion_time[i], p[i].turnaround_time);
	}
	printf("平均等待时间：%.2f\n", (float)total_waiting_time / n);
	printf("平均周转时间：%.2f\n", (float)total_turnaround_time / n);

	return 0;
}