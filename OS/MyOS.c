#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "device.h"
#include "memory.h"
#include "process.h"
#include "util.h"

#include <string.h>

int main() {
    //1. 输出启动界面
	printf("*******************************************\n");
	printf("***************** My OS ^_^ ***************\n");
	printf("*******************************************\n");
	
	//2. 初始化内存系统（数据结构）
    // 内存分配
    MEMORY memoryList;
    allocate_memory(&memoryList, 1024);

	//3. 初始化文件系统（数据结构)
    // 初始化文件系统
    FILEHASH fileHash;
    init_file_system(&fileHash);
	
	//4. 初始化进程调度系统（数据结构)
	PROCESS processList;
	process_init(&processList);

	process_insert(&processList);
	process_insert(&processList);
	process_insert(&processList);

    // 进程调度
    // process_scheduler(&processesList, numProcesses);

	//5. 初始化设备（硬件驱动）
    // 初始化设备
    int numDevices = 3;
    DEVICE devices[numDevices];
    initDevices(devices, numDevices);
    // 设备请求
    requestDevice(devices, numDevices);

	char username[USERNAME_MAX_LENGTH];
	char password[PASSWORD_MAX_LENGTH];
	char cur_path[CUR_MAX_PATH];
	cur_path[0] = '/';

	while (1) 
	{
		printf("Enter your username: ");
		fgets(username, USERNAME_MAX_LENGTH, stdin);
		// 去除输入字符串末尾的换行符
		if (username[strlen(username) - 1] == '\n') {
			username[strlen(username) - 1] = '\0';
		}

		printf("Enter your password: ");
		hide_password(password);
		printf("\n");

		// 登陆校验
		if (0 == verify_user(&fileHash,username,password)) {
			// 验证成功
			strcat(cur_path,username);
			break;
		}
		printf("\033[31mAccese Denied: Username or Password is Faied!\033[0m\n\n");
	}

	while(1) {
		//6. 输出控制台信息并提取控制台命令
		char last_path[20]; // 声明一个字符数组来存储最后一个路径
		// 调用函数来获取最后一个路径
		find_last_path(cur_path, last_path);

		printf("\033[95m[root@biteOS %s]# \033[0m",last_path);   // 输出紫色文本

		fflush(stdout); //强制printf输出
		char buf[100] = {0};
		// gets 函数存在缓冲区溢出的风险，可以改用 fgets 函数
		gets(buf);

		//7. 处理命令
		if(0 == strcmp(buf, "ps")) {
			printf("USER\tPID\tNICE\tSTART\tSTATE\n");
			process_show(&processList,NEXT);
		} else if (0 == strcmp(buf,"clear")) {
			system("clear");
		} else if (0 == strcmp(buf,"pwd")) {
			printf("%s\n",cur_path);
		} else if (0 == strcmp(buf,"cd")) {
			continue;
		} else if (0 == strcmp(buf,"cd ..")) {
			// 检查当前路径是否已经是根目录
			if (strcmp(cur_path, "/") == 0) {
				printf("Already at root directory.\n");
			} else {
				// 借用前面获取的 last_path 从 cur_path 中移除
			    file_cd_front(cur_path,last_path);
			}
			// 避免当 /root 时将根目录也给清除了
			if (strlen(cur_path) == 0) {
				// 如果最后一个路径为空，则表示当前已经是根目录，直接将当前路径设置为根目录 "/"
				strcpy(cur_path,"/");
			}
		} else if (0 == strcmp(buf,"ls")) {
			file_show_cur(&fileHash,cur_path);
		} else if (0 == strcmp(buf,"ll")) {
			file_show_cur_detail(&fileHash,cur_path);
		} else if (0 == strcmp(buf,"exit")) {
            // 退出登录
			printf("退出成功~~\n");
			cur_path[0] = '\0';
            break;
		} else {
			printf("bash: %s: Invalid command...\n",buf);
		}
	}
    return 0;
}