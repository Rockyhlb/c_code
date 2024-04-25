#include <stdio.h>
#include <stdlib.h>
#include "process.h"

// #include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void process_init(PROCESS *processList) {
	processList->next = processList->prev = NULL;
}

static JOB create_job() {
	// 创建进程
	JOB job;
	// 使用 strcpy() 函数复制字符串到 user_name 字段
    strcpy(job.user_name, "root");
	job.pid = 4421;
	job.priority = 3;

	// 获取当前时间
	time_t current_time;
    struct tm *local_time;

    current_time = time(NULL);
    local_time = localtime(&current_time);

    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

    // 计算总的分钟数
    long total_minutes = hour * 60 + minute;
    // 将总的分钟数赋值给 job.start
    job.start = total_minutes;
    job.state = 0; // 进程状态初始化为就绪
	
	return job;
}

// 头插
void process_insert(PROCESS *list) 
{
	JOB job = create_job();

	PROCESS *node = malloc(sizeof(PROCESS));
    node->data = job;
	
    node->next = node->prev = NULL;
	node->next = list->next;
	node->prev = list;
	list->next = node;
	// node的下一个结点不为空时，让下一个结点的前驱指向自己
	if(node->next) {
		node->next->prev = node;
	}
}

// NEXT 和 PREV 控制是顺序遍历 还是 逆序遍历
#define NEXT 0
#define PREV 1
void process_show(PROCESS *list, int dflag) {
    if(NEXT == dflag) {
		while(list->next) {
			// 带头双向链表，打印下一个结点的 data,打印赋值后的结果
			// 进程创建时间默认是存储分钟
			int hour = list->next->data.start / 60;
			int minute = list->next->data.start % 60;
    		// 将小时和分钟格式化为字符串
    		char time_str[10]; // 用于存储格式化后的时间字符串
    		sprintf(time_str, "%02d:%02d", hour, minute);
			printf("%s\t%d\t%d\t%s\t%d\n",list->next->data.user_name,list->next->data.pid,list->next->data.priority,time_str,list->next->data.state);
			list = list->next;
		}
		printf("\n");
	} else {
		PROCESS *head = list;
		while(list->next) {
			list = list->next;
		}

		while(list != head) {
			// 由于是从尾打印，因此最后一个结点并不是头，就需要打印当前结点的 data
			// 进程创建时间默认是存储分钟
			int hour = list->next->data.start / 60;
			int minute = list->next->data.start % 60;
    		// 将小时和分钟格式化为字符串
    		char time_str[10]; // 用于存储格式化后的时间字符串
    		sprintf(time_str, "%02d:%02d", hour, minute);
            printf("%s\t%d\t%d\t%s\t%d\n",list->next->data.user_name,list->next->data.pid,list->next->data.priority,time_str,list->next->data.state);
			list = list->prev;
		}
		printf("\n");
	}
}

// 进程调度
void process_scheduler(PROCESS *processList, int numProcesses) {
    // 实现进程调度算法
    printf("进程调度！！");
}