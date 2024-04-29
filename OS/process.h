#ifndef _PROCESS_
#define _PROCESS

// NEXT 和 PREV 控制是顺序遍历 还是 逆序遍历
#define NEXT 0
#define PREV 1

// ---进程管理---
struct JOB
{					  
	char user_name[20];   // 创建进程的用户	
	int pid;		  // 进程PID
	int priority;	  // 进程优先级
    char start[10];   // 进程创建时间
	int status;		  // 进程状态，0为不在内存，1为在内存，3为挂起，   就绪，运行，阻塞
	char command[25]; // 进程内容(可以为当前用户路径)
};

// 进程调度
// 函数指针
typedef void FUNC(struct JOB);

// 双向链表管理进程
typedef struct process {
    struct JOB data;
	// 任务执行列表 -- 指针数组 -- 存储进程执行任务
	FUNC *tasks[10];
	// 控制任务列表下标
	int index;
	// 前驱
	struct process *prev;
	// 后继
	struct process *next;
}PROCESS;

void process_init(PROCESS *processList);
struct JOB create_init_job();

// task
void func(struct JOB job);

// 头插  add [-name] [-priority] [-status]
void process_insert(MEMORY *memory, PROCESS *list,struct JOB job);

// 根据PID移除进程  kill [-PID] 
void process_kill(MEMORY *memory, PROCESS *list,int pid);

// 进程运行状态检测  ps aux
void process_show(PROCESS *processList, int dflag);

// 修改进程优先级 nice [-PID] [-PRIORITY]
void process_nice(PROCESS *list,int pid,int priorisy);

void process_scheduler(PROCESS *processList, int numProcesses);

//模拟调度器
void scheduler(PROCESS *process_list,int x);


#endif