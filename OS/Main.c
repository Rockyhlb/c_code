#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>
#define PNUM 5
#define _CRT_SECURE_NO_WARNINGS 1
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
	int child_num;					  // 子节点数
};

// ---处理机调度---
struct process
{
	int pid;
	int burst_time;
	int arrival_time;
	int priority;
};

// ---设备管理---
// 定义设备类型枚举
typedef enum
{
	DEVICE_TYPE_COMPUTER,
	DEVICE_TYPE_PRINTER,
	DEVICE_TYPE_SCANNER
} DeviceType;

// 定义设备状态枚举
typedef enum
{
	DEVICE_STATUS_FREE,
	DEVICE_STATUS_BUSY
} DeviceStatus;

// 定义设备结构体  -- 链表
typedef struct Device
{
	char *name;			 // 设备名称
	DeviceType type;	 // 设备类型
	DeviceStatus status; // 设备状态
	struct Device *next; // 指向下一个设备的指针
} Device;

// 定义全局变量，存储设备列表头指针
Device *device_head = NULL;

// ---进程管理---
struct process_type
{					  // 进程状态定义
	int pid;		  // 进程
	int priority;	  // 进程优先级
	int size;		  // 进程大小
	int status;		  // 标志进程状态，0为不在内存，1为在内存，3为挂起
	char content[10]; // 进程内容
};

// 设置内存大小
struct process_type memory[20];
int process_num = 0, guaqi = 0, pid, flag = 0;

int deal_main();
int main_menu(struct user_node *p);

int create_dir(struct user_node *user, char *cmd);
int file_menu_detail(struct user_node *p);
void close_file(struct file_node *file);

// 系统初始化函数，添加默认管理员用户和根目录
void sys_initialize()
{
	// 初始化 root 用户...
	struct user_node *admin_user = (struct user_node *)malloc(sizeof(struct user_node));
	strcpy(admin_user->user_name, "00");
	strcpy(admin_user->password, "00");
	admin_user->current_dir = NULL;
	user_list[user_num++] = admin_user;

	// 初始化文件系统...
	struct file_node *root_dir = (struct file_node *)malloc(sizeof(struct file_node));	// 创建根目录
	struct file_node *root_home = (struct file_node *)malloc(sizeof(struct file_node)); // 初始化root用户的家目录
	strcpy(root_dir->name, "/");
	strcpy(root_home->name, "root");
	root_dir->is_dir = 1;				 // 是目录
	root_dir->read_only = 0;			 // 不是只读文件
	root_dir->encrypted = 0;			 // 不是加密文件
	root_dir->parent = NULL;			 // 没有父目录
	root_dir->child_num = 1;			 // 有一个子节点 (/root)
	root_dir->child_list[0] = root_home; // 根目录 挂载 /root节点

	root_home->is_dir = 1;				 // 是目录
	root_home->read_only = 0;			 // 不是只读文件
	root_home->encrypted = 0;			 // 不是加密文件
	root_home->parent = root_dir;		 // 父目录就是根目录
	root_home->child_num = 0;			 // 没有子节点
	admin_user->current_dir = root_home; // 管理员用户当前目录设为根目录
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
		printf("用户名为空或过长，请重新注册\n");
		return;
	}
	int i = 0;
	for (i = 0; i < user_num; i++)
	{
		if (strcmp(user_name, user_list[i]->user_name) == 0)
		{
			printf("此用户名已被使用，请重新注册\n");
			return;
		}
	}
	// 用户注册成功，创建用户节点
	struct user_node *new_user = (struct user_node *)malloc(sizeof(struct user_node));
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
	struct file_node *root_dir = (struct file_node *)malloc(sizeof(struct file_node));	// 初始化根目录
	struct file_node *root_home = (struct file_node *)malloc(sizeof(struct file_node)); // 初始化root用户的家目录
	struct file_node *usr_dir = (struct file_node *)malloc(sizeof(struct file_node));	// 初始化用户目录
	struct file_node *usr_home = (struct file_node *)malloc(sizeof(struct file_node));	// 初始化用户家目录

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
			return i; // 返回用户在用户列表中的下标
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
		printf("用户 %s 登录成功\n", user_name);
		// main_menu();
		return user_list[user_index];
	}
	else
	{
		printf("用户名或密码错误，请重新登录\n");
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
			printf("已经是顶层目录，无法继续返回\n");
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
			// printf("当前目录更改为 %s\n\n", user->current_dir->name);
		}
		else
		{
			printf("不存在目录 %s，请重新输入\n", dir_name);
		}
		file_menu_detail(user);
	}
}

// 显示当前目录
void show_current_dir(struct user_node *user)
{
	printf("当前目录为 %s\n\n", user->current_dir->name);
	file_menu_detail(user);
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
		printf("目录名称为空，请重新输入~\n");
		return -1;
	}
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, dir_name) == 0)
		{
			printf("目录名称已存在，请重新输入~\n");
			return -1;
		}
	}
	struct file_node *new_dir = (struct file_node *)malloc(sizeof(struct file_node));
	strcpy(new_dir->name, dir_name);
	new_dir->is_dir = 1;
	new_dir->read_only = 0;
	new_dir->encrypted = 0;
	new_dir->parent = user->current_dir;
	new_dir->child_num = 0;
	user->current_dir->child_list[user->current_dir->child_num++] = new_dir;
	printf("目录 %s 创建成功\n\n", dir_name);
	file_menu_detail(user);
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
		printf("目录名称为空，请重新输入!");
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
			printf("目录非空，无法删除\n");
			return;
		}
		// 从父目录中删除
		user->current_dir->child_list[index] = user->current_dir->child_list[--user->current_dir->child_num];
		free(dir_to_delete);
		printf("目录 %s 删除成功\n\n", dir_name);
		file_menu_detail(user);
	}
	else
	{
		printf("不存在目录 %s，请重新输入\n", dir_name);
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
		printf("文件名称为空，请重新输入\n");
		return;
	}
	int i = 0;
	for (i = 0; i < user->current_dir->child_num; i++)
	{
		if (strcmp(user->current_dir->child_list[i]->name, file_name) == 0)
		{
			printf("文件名称已存在，请重新输入\n");
			return;
		}
	}
	struct file_node *new_file = (struct file_node *)malloc(sizeof(struct file_node));
	strcpy(new_file->name, file_name);
	new_file->is_dir = 0;
	new_file->read_only = 0;
	new_file->encrypted = 0;
	new_file->parent = user->current_dir;
	new_file->child_num = 0;
	user->current_dir->child_list[user->current_dir->child_num++] = new_file;
	printf("文件 %s 创建成功\n\n", file_name);
	file_menu_detail(user);
}

// 删除文件
void delete_file(struct user_node *user, char *cmd)
{
	// rm /root/tmp.txt
	char *subStr = cmd + 3; // 从第4个字符开始（索引为3）
	char *file_name = subStr;

	if (strlen(file_name) == 0)
	{
		printf("文件名称为空，请重新输入\n");
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
		free(file_to_delete);
		printf("文件 %s 删除成功\n\n", file_name);
	}
	else
	{
		printf("不存在文件 %s, 请重新输入\n\n", file_name);
	}
	file_menu_detail(user);
}

// 打开文件
struct file_node *open_file(struct user_node *user, char *cmd)
{
	// open /root/tmp.txt
	char *subStr = cmd + 5; // 从第6个字符开始（索引为5）
	char *file_name = subStr;

	if (strlen(file_name) == 0)
	{
		printf("文件名称为空，请重新输入\n");
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
		printf("文件只读，不可修改\n");
		return;
	}
	printf("请输入新的文件内容（不超过 10000 个字符）: \n");
	scanf(" %[^\n]", file->content); // 读取输入直到换行符为止，避免遇到空格问题
	printf("文件 %s 的内容已更新\n\n", file->name);
}

// 设置文件保护码
void set_file_password(struct file_node *file)
{
	if (file->read_only)
	{
		printf("文件只读，无需设置密码\n");
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
		free(user_list[i]->current_dir);
		free(user_list[i]);
	}
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

int file_menu_detail(struct user_node *p)
{
	char cmd[100] = {0};
	do
	{
		printf("\033[95m[root@biteOS %s]# \033[0m", p->current_dir->name); // 输出紫色文本
		fflush(stdout);													   // 强制printf输出

		scanf(" %[^\n]", cmd); // 读取输入直到换行符为止，避免遇到空格问题

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

		// 根据空格切割命令，获取命令属于什么系列
		char *ser_cmd = strtok(cmd, " ");

		// TODO bug: 当第一次进入循环时，会连续打印两次信息
		if (!ser_cmd)
		{
			continue;
		}

		if (strcmp(ser_cmd, "cd") == 0)
		{
			change_dir(p, cmd);
		}
		else if (strcmp(ser_cmd, "mkdir") == 0)
		{
			create_dir(p, cmd);
		}
		else if (strcmp(ser_cmd, "rmdir") == 0)
		{
			delete_dir(p, cmd);
		}
		else if (strcmp(ser_cmd, "touch") == 0)
		{
			create_file(p, cmd);
		}
		else if (strcmp(ser_cmd, "rm") == 0)
		{
			delete_file(p, cmd);
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
					printf("file:%s$ ", opened_file->name);
					scanf("%s", sub_cmd);
					if (strcmp(sub_cmd, "close") == 0)
					{
						close_file(opened_file);
						// main_menu(p);
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
					else if (strcmp(sub_cmd, "exit") == 0)
					{
						close_file(opened_file);
						printf("退出文件管理成功！\n");
						main_menu(p);
						break;
					}
					else
					{
						printf("无效命令 %s, 请重新输入\n", sub_cmd);
					}
				} while (1);
			}
		}
		else if (strcmp(cmd, "ls") == 0)
		{
			for (int i = 0; i < p->current_dir->child_num; i++)
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
		else if (strcmp(cmd, "clear") == 0)
		{
			system("clear");
		}
		else if (strcmp(cmd, "exit") == 0)
		{
			main_menu(p);
		}
		else
		{
			printf("bash: %s: Invalid command...\n", cmd);
		}
		strcpy(cmd, "");
	} while (1);
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
void fcfs(struct process p[], int n)
{
	int waiting_time = 0, turnaround_time = 0;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (i == 0)
		{
			waiting_time = p[i].arrival_time;
		}
		else
		{
			waiting_time += p[i - 1].burst_time;
		}

		turnaround_time = waiting_time + p[i].burst_time;

		printf("\nProcess %d\n", p[i].pid);
		printf("Waiting time: %d\n", waiting_time);
		printf("Turnaround time: %d\n", turnaround_time);
	}
}

void sjf(struct process p[], int n)
{
	struct process temp;
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (p[j].burst_time < p[i].burst_time)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}

	fcfs(p, n);
}

void srtf(struct process p[], int n)
{
	int remaining_time[MAX], time = 0, smallest, complete = 0, t;
	float wait_time = 0, turnaround_time = 0;
	int i = 0;
	for (i = 0; i < n; i++)
		remaining_time[i] = p[i].burst_time;

	while (complete != n)
	{
		smallest = MAX;
		for (i = 0; i < n; i++)
		{
			if (p[i].arrival_time <= time && remaining_time[i] < remaining_time[smallest] && remaining_time[i] > 0)
			{
				smallest = i;
			}
		}

		remaining_time[smallest]--;

		if (remaining_time[smallest] == 0)
		{
			complete++;
			t = time + 1;
			wait_time += t - p[smallest].burst_time - p[smallest].arrival_time;
			turnaround_time += t - p[smallest].arrival_time;
		}

		time++;
	}

	printf("\nAverage waiting time: %.2f", wait_time / n);
	printf("\nAverage turnaround time: %.2f", turnaround_time / n);
}

void priority(struct process p[], int n)
{
	struct process temp;
	int i = 0, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (p[j].priority < p[i].priority)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}

	fcfs(p, n);
}

int deal()
{
	int i, n, ch;
	printf("请输入进程个数: ");
	scanf("%d", &n);
	struct process p[MAX];
	for (i = 0; i < n; i++)
	{
		printf("\n请输入进程 %d的详细信息\n", i + 1);
		printf("PID: ");
		scanf("%d", &p[i].pid);
		printf("Burst time: ");
		scanf("%d", &p[i].burst_time);
		printf("Arrival time: ");
		scanf("%d", &p[i].arrival_time);
		printf("优先级: ");
		scanf("%d", &p[i].priority);
	}

	while (1)
	{
		printf("\nChoose a scheduling algorithm:\n");
		printf("1. FCFS\n");
		printf("2. SJF\n");
		printf("3. SRTF\n");
		printf("4. Priority\n");
		printf("5. Exit\n");
		printf("\nEnter your choice: ");
		scanf("%d", &ch);

		switch (ch)
		{
		case 1:
			fcfs(p, n);
			break;
		case 2:
			sjf(p, n);
			break;
		case 3:
			srtf(p, n);
			break;
		case 4:
			priority(p, n);
			break;
		case 5:
			deal_main();
		default:
			printf("Invalid choice\n");
		}
	}
}
int deal_main()
{
	struct user_node *current_user;
	int n, ch, j;
	printf("-----------------------------处理机调度--------------------------");
	printf("\n*                          1. 创建进程                         *");
	printf("\n*                          2. 返回上一级                       *");
	printf("\n*                          3. 退出系统                         *");
	printf("\n------------------------------------------------------------------");
deal:
	printf("\n请输入需要进行的操作: ");
	scanf("%d", &j);
	switch (j)
	{
	case 1:
		deal();
		break;
	case 2:
		main_menu(current_user);
		break;
	case 3:
		exit(1);
		break;
	default:
		printf("Invalid choice\n");
		goto deal;
		break;
	}

	return 0;
}

// ---设备管理---
// 添加设备
void add_device()
{
	// 从键盘输入设备信息
	char name[50];
	DeviceType type;
	int status_input;
	DeviceStatus status;

	printf("请输入设备名称:");
	scanf("%s", name);
equpment1:
	printf("\n请输入设备类型 (0 : 电脑, 1 : 打印设备, 2 : 扫描设备):");
	scanf("%d", &type);

	printf("\n请输入设备状态 (0 : 空闲, 1 : 繁忙):");
equpment2:
	scanf("%d", &status_input);
	if (status_input == 0)
	{
		status = DEVICE_STATUS_FREE;
	}
	else if (status_input == 1)
	{
		status = DEVICE_STATUS_BUSY;
	}
	else
	{
		printf("输入错误，请重新输入:");
		goto equpment2;
	}

	// 分配内存并初始化设备信息
	Device *new_device = (Device *)malloc(sizeof(Device));
	if (new_device != NULL)
	{
		new_device->name = strdup(name);
		new_device->type = type;
		new_device->status = status;
		new_device->next = NULL;

		// 将新设备插入到设备列表末尾
		if (device_head == NULL)
		{
			device_head = new_device;
		}
		else
		{
			Device *curr = device_head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = new_device;
		}

		printf("设备添加成功: %s\n", name);
	}
	else
	{
		printf("添加设备: 内存不足\n");
	}
}

// 查找设备
Device *find_device(char *name)
{
	if (device_head != NULL)
	{
		Device *curr = device_head;
		while (curr != NULL)
		{
			if (strcmp(curr->name, name) == 0)
			{
				return curr;
			}
			curr = curr->next;
		}
	}
	return NULL;
}

// 修改设备状态
void modify_device_status()
{
	char name[50];
	int status_input;
	DeviceStatus status;

	printf("请输入设备名称:");
	scanf("%s", name);

	Device *device = find_device(name);
	if (device != NULL)
	{
		printf("\n请输入设备状态(0 : 空闲, 1 繁忙):");
		scanf("%d", &status_input);
		if (status_input == 0)
		{
			status = DEVICE_STATUS_FREE;
		}
		else
		{
			status = DEVICE_STATUS_BUSY;
		}
		device->status = status;
		printf("\n设备状态修改成功！: %s\n", name);
	}
	else
	{
		printf("没有发现设备！\n");
	}
}

// 删除设备
void delete_device()
{
	char name[50];

	printf("请输入设备名称:");
	scanf("%s", name);

	if (device_head != NULL)
	{
		Device *prev = NULL;
		Device *curr = device_head;
		while (curr != NULL)
		{
			if (strcmp(curr->name, name) == 0)
			{
				if (prev == NULL)
				{
					device_head = curr->next;
				}
				else
				{
					prev->next = curr->next;
				}
				free(curr->name);
				free(curr);
				printf("设备删除成功: %s\n", name);
				return;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	printf("没有发现设备\n");
}

// 打印设备列表
void print_device_list()
{
	if (device_head != NULL)
	{
		printf("Device list:\n");
		Device *curr = device_head;
		while (curr != NULL)
		{
			printf("设备名称: %s    |      设备类型: %d       | 设备状态: %d\n", curr->name, curr->type, curr->status);
			printf("\n");
			curr = curr->next;
		}
	}
	else
	{
		printf("设备列表为空，请先添加设备！\n");
	}
}

int equipment_main()
{
	struct user_node *current_user;
	int e_choice;
	printf("-----------------------------设备管理--------------------------------\n"
		   "*                           1. 添加设备                             *\n"
		   "*                           2. 修改设备状态                         *\n"
		   "*                           3. 删除设备                             *\n"
		   "*                           4. 查询设备                             *\n"
		   "*                           5. 返回上一级功能                       *\n"
		   "*                           0. 退出系统！                           *\n"
		   "---------------------------------------------------------------------\n"
		   "请输入你要进行的操作: ");
	do
	{
	top3:
		//		top4:
		scanf("%d", &e_choice);
		switch (e_choice)
		{
		case 0:
			exit(1);
			break;
		case 1:
			add_device();
			break;
		case 2:
			modify_device_status();
			break;
		case 3:
			delete_device();
			break;
		case 4:
			print_device_list();
			break;
		case 5:
			main_menu(current_user);
			break;
		default:
			printf("没有该选项，请从新输入:");
			goto top3;
			break;
		}
		printf("\n请输入你要进行的操作: ");
		goto top3;

	} while (e_choice != 0);

	return 0;
}

// ---进程管理---
void create()
{
	if (process_num >= 20)
		printf("\n内存已满, 请先换出或结束进程\n");
	// 内存容量大小设置为20
	else
	{
		int i;
		int j;
		printf("请输入要创建进程的个数: ");
		scanf("%d", &j);
		for (i = 0; i < j; i++)
		{
			// 默认一次创建5个进程
			// 定位，找到可以还未创建的进程
			if (memory[i].status == 1)
				// 如果找到的进程在内存则结束 ，初始设置都不在内存中（main函数中设置状态为0）
				break;
		going1:
			printf("\n创建第%d个进程: \n", i + 1);
			printf("\n请输入新进程pid:");
			scanf("%d", &(memory[i].pid));
			for (j = 0; j < i; j++)
				if (memory[i].pid == memory[j].pid)
				{
					printf("\n该进程已存在\n");
					goto going1;
				}
			printf("\n请输入新进程优先级:");
			scanf("%d", &(memory[i].priority));
			printf("\n请输入新进程大小:");
			scanf("%d", &(memory[i].size));
			printf("\n请输入新进程内容:");
			scanf("%s", &(memory[i].content));
			// 创建进程，使标记位为1
			memory[i].status = 1;
			printf("\n进程已成功创建!\n");
			process_num++;
		}
	}
	printf("\n");
}

// 进程运行状态检测
void run()
{
	printf("运行进程信息如下: ");
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		if (memory[i].status == 1)
		{
			// 如果进程正在运行，则输出此运行进程的各个属性值
			printf("\n  pid=%d ", memory[i].pid);
			printf(" priority=%d  ", memory[i].priority);
			printf(" size=%d  ", memory[i].size);
			printf(" zhuanbgtai=%d  ", memory[i].status);
			printf(" content=%s  ", memory[i].content);
			flag = 1;
		}
	}
	if (!flag)
		printf("\n当前没有运行进程!\n");
}

// 进程换出
void huanchu()
{
	if (!process_num)
	{
		printf("当前没有运行进程！\n");
		return;
	}
	printf("\n请输入换出进程的ID值");
	scanf("%d", &pid);
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		// 定位，找到要换出的进程，根据其状态进行相应处理
		if (pid == memory[i].pid)
		{
			if (memory[i].status == 1)
			{
				memory[i].status = 2;
				guaqi++;
				printf("\n已经成功换出进程\n");
			}
			else if (memory[i].status == 0)
				printf("\n要换出的进程不存在\n");
			else
				printf("\n要换出的进程已被挂起\n");
			flag = 1;
			break;
		}
	}
	// 找不到，则说明进程不存在
	if (flag == 0)
		printf("\n要换出的进程不存在\n");
}

// 结束（杀死）进程
void kill()
{
	if (!process_num)
	{
		printf("当前没有运行进程！\n");
		return;
	}
	printf("\n输入杀死进程的ID值");
	scanf("%d", &pid);
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		// 定位，找到所要杀死的进程，根据其状态做出相应处理
		if (pid == memory[i].pid)
		{
			memory[i].status = 0;
			process_num--;
			printf("\n已经成功杀死进程\n");
		}
		else if (memory[i].status == 0)
			printf("\n要杀死的进程不存在\n");
		else
			printf("\n要杀死的进程已被挂起\n");
		flag = 1;
		break;
	}
	// 找不到，则说明进程不存在
	if (!flag)
		printf("\n 要杀死的进程不存在\n");
}

// 唤醒进程
void huanxing()
{
	if (!process_num)
	{
		printf("当前没有运行进程\n");
		return;
	}
	if (!guaqi)
	{
		printf("\n当前没有挂起进程\n");
		return;
	}
	printf("\n输入进程pid:\n");
	scanf("%d", &pid);
	int i = 0;
	for (i = 0; i < 20; i++)
	{
		// 定位，找到所要杀死的进程，根据其状态做相应处理
		if (pid == memory[i].pid)
		{
			flag = false;
			if (memory[i].status == 2)
			{
				memory[i].status = 1;
				guaqi--;
				printf("\n已经成功唤醒进程\n");
			}
			else if (memory[i].status == 0)
				printf("\n要唤醒的进程不存在\n");
			else
				printf("\n要唤醒的进程已被挂起\n");
			break;
		}
	}
	// 找不到，则说明进程不存在
	if (flag)
		printf("\n要唤醒的进程不存在\n");
}
int course_main()
{
	struct user_node *current_user;
	int n = 1;
	int num;
	// 一开始所有进程都不在内存中
	int i = 0;
	for (i = 0; i < 20; i++)
		memory[i].status = 0;
	while (n)
	{
		printf("\n---------------------------进程管理---------------------------------\n");
		printf("*                         1.创建新的进程                             *\n");
		printf("*                         2.查看运行进程                             *\n");
		printf("*                         3.换出某个进程                             *\n");
		printf("*                         4.杀死运行进程                             *\n");
		printf("*                         5.唤醒某个进程                             *\n");
		printf("*                         6.返回上一功能                             *\n");
		printf("*                         0.退出系统                                 *\n");
		printf("----------------------------------------------------------------------\n");
	top4:
		printf("\n请选择(1~6):");
		scanf("%d", &num);
		switch (num)
		{
		case 0:
			printf("已退出系统");
			exit(0);
		case 1:
			create();
			break;
		case 2:
			run();
			break;
		case 3:
			huanchu();
			break;
		case 4:
			kill();
			break;
		case 5:
			huanxing();
			break;
		case 6:
			main_menu(current_user);
			break;
		default:
			printf("请检查输入数值是否在系统功能中1~6");
			goto top4;
			n = 0;
		}
		flag = 0; // 恢复标记
	}
	return 0;
}

// 功能菜单
int F_menu()
{
	printf("---------------------------- 功能菜单---------------------------------\n");
	printf("*                          1. 文件管理                               *\n");
	printf("*                          2. 设备管理                               *\n");
	printf("*                          3. 进程管理                               *\n");
	printf("*                          4. 处理机调度                             *\n");
	printf("*                          输入任意键退出！                           *\n");
	printf("----------------------------------------------------------------------\n");
}

int main_menu(struct user_node *p)
{
	int f_choice;
	F_menu();
top2:
	printf("\n请输入使用的功能: ");
	scanf("%d", &f_choice);
	switch (f_choice)
	{
	case 1:
		file_menu();
		file_menu_detail(p);
		break;
	case 2:
		equipment_main();
		break;
	case 3:
		course_main();
		break;
	case 4:
		deal_main();
		break;
	default:
		exit(1);
		break;
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
	// all_function();
	int choice1;
top1:
	L_menu();
	printf("请输入要进行的操作: ");
	scanf("%d", &choice1);
	switch (choice1)
	{
	case 0:
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
		printf("Invalid choice\n");
	}
	return 0;
}