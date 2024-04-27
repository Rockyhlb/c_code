#ifndef _PROCESS_
#define _PROCESS_

// 进程结构体
typedef struct job {
    // USER  PID  priority  START  STAT
    char user_name[20];
    int pid;
    int priority;
    long start;
    int state; // 进程状态：就绪、运行、阻塞等
}JOB;

typedef struct process{
	JOB data;
	// 前驱
	struct process *prev;
	// 后继
	struct process *next;
}PROCESS;

void process_init(PROCESS *processList);
void process_insert(PROCESS *processList);

// NEXT 和 PREV 控制是顺序遍历 还是 逆序遍历
#define NEXT 0
#define PREV 1
void process_show(PROCESS *processList, int dflag);

void process_scheduler(PROCESS *processList, int numProcesses);

#endif