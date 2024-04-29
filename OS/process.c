#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <time.h>
#include <string.h>

#include "util.h"
#include "memory.h"
#include "process.h"

// 初始化进程管理模块
void process_init(PROCESS *processList)
{
	// 将 index 初始化为 0
	processList->index = 0;

    // 将 tasks 数组初始化为 NULL
	int i;
    for (i = 0; i < 10; ++i) {
        processList->tasks[i] = NULL;
    }
	processList->next = processList->prev = NULL;
}

//模拟进程动作
void func(struct JOB job) {
    printf("%s\n", job.command);
}

struct JOB create_init_job()
{
	// 创建进程
	struct JOB job;
	// 使用 strcpy() 函数复制字符串到 user_name 字段
	strcpy(job.user_name, "root");
	job.pid = 4421;
	job.priority = 2;

	// 获取当前时间
	struct tm cur_time = get_cur_time();
	int hour = cur_time.tm_hour;
	int minute = cur_time.tm_min;

	// 将时间拼接好后赋值给 job.start
	sprintf(job.start, "%02d:%02d", hour, minute);
	
	job.status = 0; // 进程状态初始化为就绪
	strcpy(job.command, "/root/a.sh");

	return job;
}

// 头插  add [-name] [-priority] [-status]
void process_insert(MEMORY *memory, PROCESS *list,struct JOB job)
{
	PROCESS *node = (PROCESS *)my_malloc(memory, sizeof(PROCESS));
	if (!node)
	{
		print_log_error("内存已满, 请先换出或结束进程!");
	}
	
	node->data = job;
	node->tasks[node->index++] = func;

	node->next = node->prev = NULL;
	node->next = list->next;
	node->prev = list;
	list->next = node;
	// node的下一个结点不为空时，让下一个结点的前驱指向自己
	if (node->next)
	{
		node->next->prev = node;
	}

	print_log_info("Insert process success.");
}

// 进程运行状态检测  ps aux
void process_show(PROCESS *list, int dflag)
{
	printf("USER\tPID\tNICE\tSTART\tSTATE\tCOMMAND\n");

	if (NEXT == dflag)
	{
		while (list->next)
		{
			// 带头双向链表，打印下一个结点的 data,打印赋值后的结果
			printf("%s\t%d\t%d\t%s\t%d\t%s\n", list->next->data.user_name, list->next->data.pid, list->next->data.priority,
				   list->next->data.start, list->next->data.status, list->next->data.command);
			list = list->next;
		}
		printf("\n");
	}
	else
	{
		PROCESS *head = list;
		while (list->next)
		{
			list = list->next;
		}

		while (list != head)
		{
			// 由于是从尾打印，因此最后一个结点并不是头，就需要打印当前结点的 data
			printf("%s\t%d\t%d\t%s\t%d\t%s\n", list->data.user_name, list->data.pid, list->data.priority, list->data.start,
				   list->data.status, list->data.command);
			list = list->prev;
		}
		printf("\n");
	}
}

// 根据PID移除进程  kill [-PID] 
void process_kill(MEMORY *memory, PROCESS *list,int pid)
{
	// 找到要移除的进程节点
    PROCESS *current = list->next; // 第一个节点是头节点，跳过
    while (current) {
        if (current->data.pid == pid) {
            // 找到匹配的PID，移除当前节点
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            my_free(memory, current); // 释放当前节点的内存
            print_log_info("Process killed successfully.");
            return;
        }
        current = current->next;
    }

    // 没有找到匹配的PID
    print_log_error("Failed to kill process: PID not found.");
}

// 修改进程优先级 nice [-PID] [-PRIORITY]
void process_nice(PROCESS *list,int pid,int priority)
{
	// 找到要调整优先级的进程节点
    PROCESS *current = list->next; // 第一个节点是头节点，跳过
    while (current != NULL) {
        if (current->data.pid == pid) {
            // 找到匹配的PID，更新其优先级
            current->data.priority = priority;
            print_log_info("Priority of process updated successfully.");
            return;
        }
        current = current->next;
    }
    // 没有找到匹配的PID
    print_log_error("Failed to update process priority: PID not found.");
}

// 修改进程优先级 nice [-PID] [-PRIORITY]
// void process_nice(PROCESS *list,int pid,int priorisy)
// {
// 	// 找到要调整优先级的进程节点
//     PROCESS *current = list->next; // 第一个节点是头节点，跳过
//     while (current != NULL) {
//         if (current->data.pid == pid) {
//             // 找到匹配的PID，更新其优先级
//             current->data.priority = priority;
//             print_log_info("Priority of process updated successfully.");
//             return;
//         }
//         current = current->next;
//     }
//     // 没有找到匹配的PID
//     print_log_error("Failed to update process priority: PID not found.");
// }

// 进程调度
void process_scheduler(PROCESS *processList, int numProcesses)
{
	// 实现进程调度算法
	printf("进程调度！！");
}

// 模拟调度器
void scheduler(PROCESS *proc_list,int x)
{
	static int i = 0;
    static int time_slice = 0;
    PROCESS *cur = proc_list->next;
    
	// 时间片轮转
    while (cur) {
        // 如果时间片用尽，则重置时间片计数器并切换到下一个时间片
        if (time_slice == 0) {
            i = (i + 1) % cur->index;
            time_slice = x; // 设置时间片大小
        }

        cur->tasks[i](cur->data); // 调用当前进程的任务函数
        time_slice--;

        cur = cur->next;
    }
    alarm(2); // 设置下一个定时器
}