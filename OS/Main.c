#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

#include <signal.h>
#include <unistd.h>

#include "memory.h"
#include "util.h"
#include "process.h"

#define PNUM 5
#define MAX 10

// 定义用户节点
struct user_node
{
	char user_name[50];			   // 用户名
	char password[50];			   // 密码
	struct file_node *current_dir; // 当前目录
};

// 全局变量: 用户列表
struct user_node *user_list[50];
int user_num = 0;
// 内存
MEMORY memory_list[MEMORY_MAX_SIZE];

// ---文件管理---
// 定义文件节点
struct file_node
{
	char name[50];					  // 文件/目录名称
	int is_dir;						  // 是否为目录: 1-是，0-否
	char content[10000];			  // 文件内容
	int read_only;					  // 是否为只读文件: 1-是，0-否
	int encrypted;					  // 是否为加密文件: 1-是，0-否
	char password[50];				  // 加密文件的密码
	struct file_node *parent;		  // 父节点
	struct file_node *child_list[50]; // 子节点列表
	int child_num;				  // 子节点数
};

// 进程列表
PROCESS process_list;
// 默认 pid_num 从0开始技术
int pid_num = 0;

// 函数声明
int deal(struct user_node *user,PROCESS *process);

int main_menu(struct user_node *p);

int create_dir(struct user_node *user, char *cmd);
void close_file(struct file_node *file);

void setup_timer(int time);

struct file_node *file_init();

// 系统初始化函数，添加默认管理员用户和根目录
void sys_initialize()
{
	// 打印启动日志
	print_log_info("Starting system initialization...");

	// 初始化内存块列表
	memory_init(memory_list);
	if (!memory_list)
	{
		print_log_error("System initialization failed!!");
	}

	// 初始化 root 用户...
	print_log_info("Initializing root...");
	struct user_node *admin_user = (struct user_node *)my_malloc(memory_list, sizeof(struct user_node));
	strcpy(admin_user->user_name, "00");
	strcpy(admin_user->password, "00");
	admin_user->current_dir = NULL;
	user_list[user_num++] = admin_user;

	// 加载模块
	print_log_info("Loading kernel modules...");

	//初始化进程管理系统
	print_log_info("Initializing proccess manege init...");
	struct JOB job1 = create_init_job();

	process_init(&process_list);
	process_insert(memory_list,&process_list,job1);
	process_insert(memory_list,&process_list,job1);
	process_insert(memory_list,&process_list,job1);
	print_log_info("Process manage initialization complete.");

	// 初始化文件系统
	struct file_node *root = file_init();
	if (!root)
	{
		print_log_error("System initialization failed!!");
	}
	admin_user->current_dir = root; // 管理员用户当前目录设为根目录
	// 启动完成
	print_log_info("System initialization complete.");
	print_combined_logo();
}

// 初始化文件系统
struct file_node *file_init()
{
	print_log_info("Initializing file system...");
	// 创建根目录  '/'
	struct file_node *root_dir = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));
	// 初始化root用户的家目录   '/root'
	struct file_node *root_home = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));
	// 初始化 '/etc'
	struct file_node *etc_dir = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));

	strcpy(root_dir->name, "/");
	strcpy(root_home->name, "root");
	strcpy(etc_dir->name, "etc");

	print_log_info("Starting initialization file system...");
	root_dir->is_dir = 1;				 // 是目录
	root_dir->read_only = 0;			 // 不是只读文件
	root_dir->encrypted = 0;			 // 不是加密文件
	root_dir->parent = NULL;			 // 没有父目录
	root_dir->child_num = 2;			 // 有一个子节点 (/root)
	root_dir->child_list[0] = root_home; // 根目录 挂载 /root节点
	root_dir->child_list[1] = etc_dir;	 // 根目录 挂载 /etc节点

	print_log_info("Starting initialization file system...");
	etc_dir->is_dir = 1;		// 是目录
	etc_dir->read_only = 0;		// 不是只读文件
	etc_dir->encrypted = 0;		// 不是加密文件
	etc_dir->parent = root_dir; // 父目录就是根目录
	etc_dir->child_num = 0;		// 没有子节点

	print_log_info("Starting initialization file system...");
	root_home->is_dir = 1;		  // 是目录
	root_home->read_only = 0;	  // 不是只读文件
	root_home->encrypted = 0;	  // 不是加密文件
	root_home->parent = root_dir; // 父目录就是根目录
	root_home->child_num = 0;	  // 没有子节点

	if (!root_home)
	{
		print_log_error("File system initialization failed!!");
		return NULL;
	}
	print_log_info("File system initialization complete.");
	return root_home;
}

// pwd
void print_pwd(struct file_node *p);
// 生成家目录
void create_home_directory(struct user_node *user);

// 注册函数: 用户名同名或过长均不被接受
void register_user()
{
	char user_name[50];
	char password[50];
	printf("请输入用户名: ");
	scanf("%s", user_name);
	printf("请输入密码: ");
	scanf("%s", password);
	// 检查用户名是否合法
	if (user_name == NULL || strlen(user_name) == 0 || strlen(user_name) > 50)
	{
		print_log_error("username is null or too long, please sign up again!\n");
		return;
	}
	int i = 0;
	for (i = 0; i < user_num; i++)
	{
		if (strcmp(user_name, user_list[i]->user_name) == 0)
		{
			print_log_error("此用户名已被使用，请重新注册!\n");
			return;
		}
	}
	// 用户注册成功，创建用户节点
	struct user_node *new_user = (struct user_node *)my_malloc(memory_list, sizeof(struct user_node));
	strcpy(new_user->user_name, user_name);
	strcpy(new_user->password, password);
	user_list[user_num++] = new_user;
	// 默认在账户注册以后自动生成 家目录
	create_home_directory(new_user);
	printf("用户 %s 注册成功！\n", user_name);
}

// 创建用户家目录的函数
void create_home_directory(struct user_node *user)
{
	struct file_node *root_dir = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));	// 初始化根目录
	struct file_node *root_home = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node)); // 初始化root用户的家目录
	struct file_node *usr_dir = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));	// 初始化用户目录
	struct file_node *usr_home = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));	// 初始化用户家目录

	strcpy(root_dir->name, "/");
	root_dir->is_dir = 1;				 // 是目录
	root_dir->read_only = 0;			 // 不是只读文件
	root_dir->encrypted = 0;			 // 不是加密文件
	root_dir->parent = NULL;			 // 没有父目录
	root_dir->child_num = 2;			 // 有二个子节点 (/root、/usr)
	root_dir->child_list[0] = root_home; // 根目录 挂载 /root节点
	root_dir->child_list[1] = usr_home;	 // 挂载 /usr

	strcpy(root_home->name, "root");
	root_home->is_dir = 1;		  // 是目录
	root_home->read_only = 0;	  // 不是只读文件
	root_home->encrypted = 0;	  // 不是加密文件
	root_home->parent = root_dir; // 父目录就是根目录
	root_home->child_num = 0;	  // 没有子节点

	strcpy(usr_dir->name, "usr");
	usr_dir->is_dir = 1;			   // 是目录
	usr_dir->read_only = 0;			   // 不是只读文件
	usr_dir->encrypted = 0;			   // 不是加密文件
	usr_dir->parent = root_dir;		   // 父目录 是 根目录
	usr_dir->child_num = 1;			   // 有一个子节点 (/usr)
	usr_dir->child_list[0] = usr_home; // 根目录 挂载 /root节点

	strcpy(usr_home->name, user->user_name);
	usr_home->is_dir = 1;		// 是目录
	usr_home->read_only = 0;	// 不是只读文件
	usr_home->encrypted = 0;	// 不是加密文件
	usr_home->parent = usr_dir; // 父目录就是用户目录
	usr_home->child_num = 0;	// 没有子节点

	// 将家目录设置为用户的当前目录
	user->current_dir = usr_home;
}

// 密码验证
int verify_password(char *user_name, char *password)
{
	int i = 0;
	for (i = 0; i < user_num; i++)
	{
		if (strcmp(user_name, user_list[i]->user_name) == 0 && strcmp(password, user_list[i]->password) == 0)
		{
			// 返回用户在用户列表中的下标
			return i; 
		}
	}
	return -1; // 密码错误或用户名不存在
}

// 登录函数
struct user_node *login()
{
	char user_name[50];
	char password[50];
login:
	printf("请输入用户名: ");
	scanf("%s", user_name);
	printf("请输入密码: ");
	scanf("%s", password);
	int user_index = verify_password(user_name, password);
	if (user_index >= 0)
	{
		return user_list[user_index];
	}
	else
	{
		printf("\033[31mAccese Denied: Username or Password is Faied!\033[0m\n\n");
		goto login;
		return NULL;
	}
}

//---文件管理---
// 获取文件/目录在其父目录中的位置
int get_child_index(struct file_node *parent, struct file_node *child)
{
	int i = 0;
	for (i = 0; i < parent->child_num; i++)
	{
		if (parent->child_list[i] == child)
		{
			return i;
		}
	}
	return -1; // 子节点不存在于父节点中
}

// 更改目录
void change_dir(struct user_node *user, char *cmd)
{
	// cd /root/tmp   从第四个字符开始获取目录
	char *subStr = cmd + 3; // 从第4个字符开始（索引为3）

	char *dir_name = subStr;

	if (strcmp(dir_name, "..") == 0)
	{
		// 到上层目录
		if (user->current_dir->parent != NULL)
		{
			user->current_dir = user->current_dir->parent;
		}
		else
		{
			print_log_info("已经是顶层目录，无法继续返回!\n");
		}
	}
	else
	{
		// 到下层目录
		int index = -1, i = 0;
		for (i = 0; i < user->current_dir->child_num; i++)
		{
			if (strcmp(user->current_dir->child_list[i]->name, dir_name) == 0 && user->current_dir->child_list[i]->is_dir)
			{
				index = i;
			}
		}
		if (index >= 0)
		{
			user->current_dir = user->current_dir->child_list[index];
		}
		else
		{
			printf("不存在目录 %s, 请重新输入\n", dir_name);
		}
	}
}

// 显示当前目录
void show_current_dir(struct user_node *user)
{
	printf("当前目录为 %s\n\n", user->current_dir->name);
}

// 创建目录
int create_dir(struct user_node *user, char *cmd)
{
	// mkdir /root/tmp
	char *subStr = cmd + 6; // 从第7个字符开始（索引为6）
	char *dir_name = subStr;

	int i = 0;
	if (strlen(dir_name) == 0)
	{
		print_log_error("目录名称为空，请重新输入~\n");
		return -1;
	}
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, dir_name) == 0)
		{
			print_log_error("目录名称已存在，请重新输入~\n");
			return -1;
		}
	}
	struct file_node *new_dir = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));
	strcpy(new_dir->name, dir_name);
	new_dir->is_dir = 1;
	new_dir->read_only = 0;
	new_dir->encrypted = 0;
	new_dir->parent = user->current_dir;
	new_dir->child_num = 0;
	user->current_dir->child_list[user->current_dir->child_num++] = new_dir;
	printf("目录 %s 创建成功\n\n", dir_name);
	return 0;
}

// 删除目录
void delete_dir(struct user_node *user, char *cmd)
{
	// rmdir /root/tmp
	char *subStr = cmd + 6; // 从第7个字符开始（索引为6）
	char *dir_name = subStr;

	if (strlen(dir_name) == 0)
	{
		print_log_error("目录名称为空，请重新输入!\n");
		return;
	}
	int index = -1, i = 0;
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, dir_name) == 0 && user->current_dir->child_list[i]->is_dir)
		{
			index = i;
			break;
		}
	}
	if (index >= 0)
	{
		struct file_node *dir_to_delete = user->current_dir->child_list[index];
		if (dir_to_delete->child_num > 0)
		{
			// 目录非空不允许删除
			print_log_error("目录非空，无法删除!\n");
			return;
		}
		// 从父目录中删除
		user->current_dir->child_list[index] = user->current_dir->child_list[--user->current_dir->child_num];
		my_free(memory_list, (void *)dir_to_delete);
		printf("目录 %s 删除成功~\n\n", dir_name);
	}
	else
	{
		printf("不存在目录 %s, 请重新输入!\n", dir_name);
	}
}

// 创建文件
void create_file(struct user_node *user, char *cmd)
{
	// touch /root/tmp.txt
	char *subStr = cmd + 6; // 从第7个字符开始（索引为6）
	char *file_name = subStr;

	if (strlen(file_name) == 0)
	{
		print_log_error("文件名称为空，请重新输入!\n");
		return;
	}
	int i = 0;
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, file_name) == 0)
		{
			print_log_error("文件名称已存在，请重新输入!\n");
			return;
		}
	}
	struct file_node *new_file = (struct file_node *)my_malloc(memory_list, sizeof(struct file_node));
	strcpy(new_file->name, file_name);
	new_file->is_dir = 0;
	new_file->read_only = 0;
	new_file->encrypted = 0;
	new_file->parent = user->current_dir;
	new_file->child_num = 0;
	user->current_dir->child_list[user->current_dir->child_num++] = new_file;
	printf("文件 %s 创建成功~~\n\n", file_name);
}

// 删除文件
void delete_file(struct user_node *user, char *cmd)
{
	// rm /root/tmp.txt
	char *subStr = cmd + 3; // 从第4个字符开始（索引为3）
	char *file_name = subStr;

	if (strlen(file_name) == 0)
	{
		print_log_error("文件名称为空，请重新输入!!\n");
		return;
	}
	int index = -1;
	int i = 0;
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, file_name) == 0 && !user->current_dir->child_list[i]->is_dir)
		{
			index = i;
			break;
		}
	}
	if (index >= 0)
	{
		struct file_node *file_to_delete = user->current_dir->child_list[index];
		// 从父目录中删除
		user->current_dir->child_list[index] = user->current_dir->child_list[--user->current_dir->child_num];
		my_free(memory_list, file_to_delete);
		printf("文件 %s 删除成功~~\n\n", file_name);
	}
	else
	{
		printf("不存在文件 %s, 请重新输入!\n\n", file_name);
	}
}

// 打开文件
struct file_node *open_file(struct user_node *user, char *cmd)
{
	// open /root/tmp.txt
	char *subStr = cmd + 5; // 从第6个字符开始（索引为5）
	char *file_name = subStr;

	if (strlen(file_name) == 0)
	{
		print_log_error("文件名称为空，请重新输入!\n");
		return NULL;
	}
	int index = -1, i = 0;
	// 遍历当前路径下的所有文件( user->current_dir )
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (0 == strcmp(user->current_dir->child_list[i]->name, file_name) && !user->current_dir->child_list[i]->is_dir)
		{
			index = i;
			break;
		}
	}
	// 找到文件，返回打开的文件
	if (index >= 0)
	{
		struct file_node *file_to_open = user->current_dir->child_list[index];
		printf("文件 %s 打开成功：\n", file_name);
		return file_to_open;
	}
	else
	{
		printf("不存在文件 %s, 请重新输入\n", file_name);
		return NULL;
	}
}

// 关闭文件
void close_file(struct file_node *file)
{
	printf("文件 %s 关闭成功\n", file->name);
}

// 读文件
void read_file(struct file_node *file)
{
	printf("文件 %s 的内容为: \n", file->name);
	printf("%s \n", file->content);
}

// 写文件
void write_file(struct file_node *file)
{
	if (file->read_only)
	{
		printf("文件只读，不可写入\n");
		return;
	}

	printf("请输入文件内容（不超过 10000 个字符）:\n");
	scanf(" %[^\n]", file->content); // 读取输入直到换行符为止，避免遇到空格问题
	// 写入成功消息
	printf("文件 %s 写入成功\n", file->name);
}

// 更改文件内容
void update_file_content(struct file_node *file)
{
	if (file->read_only)
	{
		print_log_error("文件只读，不可修改\n");
		return;
	}
	printf("请输入新的文件内容（不超过 10000 个字符）: \n");
	scanf(" %[^\n]", file->content); // 读取输入直到换行符为止，避免遇到空格问题
	printf("文件 %s 的内容已更新~~\n\n", file->name);
}

// 设置文件保护码
void set_file_password(struct file_node *file)
{
	if (file->read_only)
	{
		print_log_info("文件只读，无需设置密码!\n");
		return;
	}
	printf("请输入文件保护码（不能包含特殊字符）: ");
	scanf("%s", file->password);
	file->encrypted = 1;
	printf("文件 %s 的保护码已设置\n\n", file->name);
}

// 退出系统
void exit_system()
{
	int i = 0;
	for (i = 0; i < user_num; i++)
	{
		my_free(memory_list, user_list[i]->current_dir);
		my_free(memory_list, user_list[i]);
	}
	my_free(memory_list, &process_list);
	print_logo_tail();
	exit(0);
}

int file_menu()
{
	printf("---------------------文件管理界面——命令浏览--------------------------\n");
	printf("*                     > cd: 进入指定目录                            *\n");
	printf("*                     > rm: 删除文件                                *\n");
	printf("*                     > ls : 查看当前目录                            *\n");
	printf("*                     > pwd: 查看当前绝对路径                        *\n");
	printf("*                     > mkdir: 创建目录                             *\n");
	printf("*                     > rmdir: 删除目录                             *\n");
	printf("*                     > touch: 创建文件	                            *\n");
	printf("*                     > open : 打开文件                             *\n");
	printf("*                     > close: 关闭文件                             *\n");
	printf("*                     > cat: 读取文件内容                            *\n");
	printf("*                     > write : 写入文件内容                         *\n");
	printf("*                     > update: 更新文件内容                         *\n");
	printf("*                     > password: 设置文件保护码                     *\n");
	printf("*                     > clear: 清除屏幕                              *\n");
	printf("*                     > exit : 退出                                  *\n");
	printf("---------------------------------------------------------------------\n");
}

void print_pwd(struct file_node *p)
{
	if (!p->parent)
	{
		return;
	}
	print_pwd(p->parent);
	printf("/%s", p->name);
}

// ---处理机调度---
// void fcfs(struct process p[], int n)
// {
// 	int waiting_time = 0, turnaround_time = 0;
// 	int i = 0;
// 	for (i = 0; i < n; i++)
// 	{
// 		if (i == 0)
// 		{
// 			waiting_time = p[i].arrival_time;
// 		}
// 		else
// 		{
// 			waiting_time += p[i - 1].burst_time;
// 		}

// 		turnaround_time = waiting_time + p[i].burst_time;

// 		printf("\nProcess %d\n", p[i].pid);
// 		printf("Waiting time: %d\n", waiting_time);
// 		printf("Turnaround time: %d\n", turnaround_time);
// 	}
// }

// void priority(struct process p[], int n)
// {
// 	struct process temp;
// 	int i = 0, j = 0;
// 	for (i = 0; i < n; i++)
// 	{
// 		for (j = i + 1; j < n; j++)
// 		{
// 			if (p[j].priority < p[i].priority)
// 			{
// 				temp = p[i];
// 				p[i] = p[j];
// 				p[j] = temp;
// 			}
// 		}
// 	}
// 	fcfs(p, n);
// }

// 定义一个信号处理函数，该函数将调用 scheduler 函数
static void alarm_handler(int signum) {
	scheduler(&process_list, 3);
    print_log_info("Scheduled tasks executed.");
}

// 设置定时器
void setup_timer(int time) {
    signal(SIGALRM, alarm_handler);
    alarm(time);
}

int deal(struct user_node *user,PROCESS *process)
{
    // 通过定时器，模拟完成调度器的时间片轮转调度 */
	setup_timer(3);

	// 定时器的实现一定要配合循环一起使用！！
	while (1)
	{
		char cmd[100] = {0};
		printf("\033[95m[%s@biteOS %s]# \033[0m", user->user_name, user->current_dir->name); // 输出紫色文本
		fflush(stdout);																   // 强制printf输出

		scanf(" %[^\n]", cmd); // 读取输入直到换行符为止，避免遇到空格问题

		if (0 == strcmp(cmd,"pause"))
		{
			break;
		}
	}
}

// // 进程换出
// void huanchu()
// {
// 	if (!process_num)
// 	{
// 		printf("当前没有运行进程！\n");
// 		return;
// 	}
// 	printf("\n请输入换出进程的ID值");
// 	scanf("%d", &pid);
// 	int i = 0;
// 	for (i = 0; i < 20; i++)
// 	{
// 		// 定位，找到要换出的进程，根据其状态进行相应处理
// 		if (pid == process_list[i]->pid)
// 		{
// 			if (process_list[i]->status == 1)
// 			{
// 				process_list[i]->status = 2;
// 				guaqi++;
// 				printf("\n已经成功换出进程\n");
// 			}
// 			else if (process_list[i]->status == 0)
// 				printf("\n要换出的进程不存在\n");
// 			else
// 				printf("\n要换出的进程已被挂起\n");
// 			flag = 1;
// 			break;
// 		}
// 	}
// 	// 找不到，则说明进程不存在
// 	if (flag == 0)
// 		printf("\n要换出的进程不存在\n");
// }

// 结束（杀死）进程
// void kill()
// {

// 	for (i = 0; i < 20; i++)
// 	{
// 		// 定位，找到所要杀死的进程，根据其状态做出相应处理
// 		if (pid == process_list[i]->pid)
// 		{
// 			process_list[i]->status = 0;
// 			process_num--;
// 			printf("\n已经成功杀死进程\n");
// 		}
// 		else if (process_list[i]->status == 0)
// 			printf("\n要杀死的进程不存在\n");
// 		else
// 			printf("\n要杀死的进程已被挂起\n");
// 		flag = 1;
// 		break;
// 	}
// 	// 找不到，则说明进程不存在
// 	if (!flag)
// 		printf("\n 要杀死的进程不存在\n");
// }

// // 唤醒进程
// void huanxing()
// {
// 	if (!process_num)
// 	{
// 		printf("当前没有运行进程\n");
// 		return;
// 	}
// 	if (!guaqi)
// 	{
// 		printf("\n当前没有挂起进程\n");
// 		return;
// 	}
// 	printf("\n输入进程pid:\n");
// 	scanf("%d", &pid);
// 	int i = 0;
// 	for (i = 0; i < 20; i++)
// 	{
// 		// 定位，找到所要杀死的进程，根据其状态做相应处理
// 		if (pid == process_list[i]->pid)
// 		{
// 			flag = false;
// 			if (process_list[i]->status == 2)
// 			{
// 				process_list[i]->status = 1;
// 				guaqi--;
// 				printf("\n已经成功唤醒进程\n");
// 			}
// 			else if (process_list[i]->status == 0)
// 				printf("\n要唤醒的进程不存在\n");
// 			else
// 				printf("\n要唤醒的进程已被挂起\n");
// 			break;
// 		}
// 	}
// 	// 找不到，则说明进程不存在
// 	if (flag)
// 		printf("\n要唤醒的进程不存在\n");
// }

void process_menu()
{
	printf("\n---------------------------进程管理----------------------------------\n");
	printf("*                1.创建新的进程 add [-name] [-priority] [-status]     *\n");
	printf("*                2.查看运行进程 ps aux                                *\n");
	printf("*                3.换出某个进程 pause [-PID]                          *\n");
	printf("*                4.杀死运行进程 kill [-PID]                           *\n");
	printf("*                5.唤醒某个进程 continue [-PID]                       *\n");
	printf("*                6.运行进程 exec                                      *\n");
	printf("*                7.修改进程优先级 nice [-PID] [-PRIORITY]             *\n");
	printf("*                0.退出系统 exit                                     *\n");
	printf("----------------------------------------------------------------------\n");
}

// 功能菜单
int F_menu()
{
	printf("---------------------------- 功能菜单---------------------------------\n");
	printf("*                          1. 文件管理                               *\n");
	printf("*                          2. 进程管理                               *\n");
	printf("*                          3. 处理机调度                             *\n");
	printf("*                          输入任意键退出！                           *\n");
	printf("----------------------------------------------------------------------\n");
}

int main_menu(struct user_node *p)
{
	char cmd[100] = {0};
	while(1)
	{
		printf("\033[95m[%s@biteOS %s]# \033[0m", p->user_name, p->current_dir->name); // 输出紫色文本
		fflush(stdout);																   // 强制printf输出

		scanf(" %[^\n]", cmd); // 读取输入直到换行符为止，避免遇到空格问题

		// 匹配 help
		if (0 == strcmp(cmd, "help file")) {
			file_menu(p);
			continue;
		}
		if (strcmp(cmd, "help process") == 0) {
			process_menu(p);
			continue;
		}

		// 匹配常用 cd
		if (0 == strcmp(cmd, "cd"))
		{
			// 回到家目录
			while (p->current_dir->name != p->user_name)
			{
				p->current_dir = p->current_dir->parent;
			}
			continue;
		}
		if (0 == strcmp(cmd, "cd ."))
		{
			continue;
		}
		if (0 == strcmp(cmd, "cd /"))
		{
			while (p->current_dir->parent)
			{
				p->current_dir = p->current_dir->parent;
			}
			continue;
		}

		// 匹配常用 ps
		if (0 == strcmp(cmd,"ps aux"))
		{
			process_show(&process_list,NEXT);
			continue;
		}

		if (0 == strcmp(cmd,"exec"))
		{
			deal(p,&process_list);
		}

		// 常用命令
		if (strcmp(cmd, "clear") == 0)
		{
			system("clear");
			continue;
		}

		// 匹配退出系统
		if (0 == strcmp(cmd,"exit")) {
			print_log_info("已退出系统~~");
			exit_system();
		}

		// 根据空格切割命令，获取命令属于什么系列
		char *ser_cmd = strtok(cmd, " ");
		if (!ser_cmd)
		{
			continue;
		}

		// FILE_MANAGE
		if (strcmp(ser_cmd, "cd") == 0)
		{
			change_dir(p, cmd);
			continue;
		}
		else if (strcmp(ser_cmd, "mkdir") == 0)
		{
			create_dir(p, cmd);
			continue;
		}
		else if (strcmp(ser_cmd, "rmdir") == 0)
		{
			delete_dir(p, cmd);
			continue;
		}
		else if (strcmp(ser_cmd, "touch") == 0)
		{
			create_file(p, cmd);
			continue;
		}
		else if (strcmp(ser_cmd, "rm") == 0)
		{
			delete_file(p, cmd);
			continue;
		}
		else if (strcmp(ser_cmd, "open") == 0)
		{
			struct file_node *opened_file = open_file(p, cmd);
			if (opened_file)
			{
				// 打开成功
				char sub_cmd[50];
				do
				{
					printf("\nfile:%s$ ", opened_file->name);
					scanf("%s", sub_cmd);
					if (strcmp(sub_cmd, "close") == 0)
					{
						close_file(opened_file);
						break;
					}
					else if (strcmp(sub_cmd, "cat") == 0)
					{
						read_file(opened_file);
					}
					else if (strcmp(sub_cmd, "write") == 0)
					{
						write_file(opened_file);
					}
					else if (strcmp(sub_cmd, "update") == 0)
					{
						update_file_content(opened_file);
					}
					else if (strcmp(sub_cmd, "password") == 0)
					{
						set_file_password(opened_file);
					}
					else
					{
						printf("无效命令 %s, 请重新输入~~\n", sub_cmd);
					}
				} while (1);
			} else {
				print_log_error("File not found~~");
			}
		}
		else if (strcmp(cmd, "ls") == 0)
		{
			int i;
			for (i = 0; i < p->current_dir->child_num; i++)
			{
				printf("%s ", p->current_dir->child_list[i]->name);
			}
			printf("\n");
		}
		else if (strcmp(cmd, "pwd") == 0)
		{
			if (!p->current_dir->parent)
			{
				// 当已经是根目录时，直接打印
				printf("/");
			}
			// p->current_dir); 指向的是当前最底层路径，可以通过递归到根目录再打印结点
			print_pwd(p->current_dir);
			printf("\n");
		}
		// PROCESS_MANAGE
		else if(0 == strcmp(ser_cmd,"add")) {
			struct JOB new_job;
			new_job.pid = pid_num++;

			strcpy(new_job.user_name,p->user_name);

			char *args = cmd + 4;  // 控制下标到输入参数处
			// 获取命令的其他参数
			char *token = strtok(args, " ");
			if (!token)
			{
				printf("bash: %s: Invalid command...\n", cmd);
			}
			// 控制访问下标
			int index = 0;
			while (token != NULL) {
				switch (index) {
					case 0: // 命令
						strcpy(new_job.command, token);
						break;
					case 1: // 优先级
						new_job.priority = atoi(token);   // atoi(): 将字符串转换为整数 并 赋值
						break;
					case 2: // 状态
						new_job.status = atoi(token);
						break;
					default:
						break;
				}
				token = strtok(NULL, " ");
				index++;
			}
			// 当 index 不等于3时，说明输入参数缺失
			if (index != 3)
			{
				printf("bash: %s: Invalid command...\n", cmd);
				strcpy(cmd,"");
				continue;
			}
			// 获取当前时间
			struct tm cur_time = get_cur_time();
			int hour = cur_time.tm_hour;
			int minute = cur_time.tm_min;

			// 将时间拼接好后赋值给 job.start
			sprintf(new_job.start, "%02d:%02d", hour, minute);

			process_insert(memory_list,&process_list,new_job);
		} 
		else if (0 == strcmp(ser_cmd,"kill"))
		{
			// kill 2311
			char *args = cmd + 5;
			process_kill(memory_list,&process_list,atoi(args));
		}
		else if (0 == strcmp(ser_cmd,"pause"))
		{
			// pause 2311
			char *args = cmd + 6;
			process_kill(memory_list,&process_list,atoi(args));
		}
		else if (0 == strcmp(ser_cmd,"continue"))
		{
			// continue 2311
			char *args = cmd + 9;
			process_kill(memory_list,&process_list,atoi(args));
		}
		else if (0 == strcmp(ser_cmd,"nice"))
		{
			// nice 2311 1
			char *args = cmd + 5;
			// 获取命令的其他参数
			char *token = strtok(args, " ");
			if (!token)
			{
				printf("bash: %s: Invalid command...\n", cmd);
			}
			int pid = -1;
			int new_priority = -1;
			// 控制访问下标
			int index = 0;
			while (token != NULL) {
				switch (index) {
					case 0: // PID
						pid = atoi(token);
						break;
					case 1: // NEW PRIORITY
						new_priority = atoi(token);
						break;
					default:
						break;
				}
				token = strtok(NULL, " ");
				index++;
			}
			// 当 index 不等于2时，说明输入参数缺失
			if (index != 2)
			{
				printf("bash: %s: Too few args...\n", cmd);
				continue;
			}
			process_nice(&process_list,pid,new_priority);
		}else {
			printf("bash: %s: Invalid command...\n", cmd);
			continue;
		}
		strcpy(cmd,"");
	}
}

// 主功能界面
// 登录菜单
int L_menu()
{
	printf("------------------------- 请选择操作: --------------------------------\n");
	printf("*                        1. 注册新用户                               *\n");
	printf("*                        2. 用户登录                                 *\n");
	printf("*                        0. 退出系统                                 *\n");
	printf("----------------------------------------------------------------------\n");
}

// ——————主函数
int main()
{
	struct user_node *current_user;
	sys_initialize();
	int m_choice;
top1:
	L_menu();
	printf("请输入要进行的操作: ");
	scanf("%d", &m_choice);

	switch (m_choice)
	{
	case 0:
		exit_system();
		break;
	case 1:
		register_user();
		goto top1;
		break;
	case 2:
		current_user = login();
		main_menu(current_user);
		break;
	default:
		print_log_error("Invalid choice!\n");
	}
	return 0;
}