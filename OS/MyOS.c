#include <stdio.h>
#include <stdlib.h>

#include "file/file.c"
#include "device/device.c"
#include "memory/memory.c"
#include "process/process.c"
#include "utils/util.c"

int main() {
    //1. 输出启动界面
	printf("*******************************************\n");
	printf("***************** My OS ^_^ ***************\n");
	printf("*******************************************\n");
	
	//2. 初始化内存系统（数据结构）
    // 内存分配
    MEMORY memoryList;
    allocateMemory(&memoryList, 1024);
	
	//3. 初始化文件系统（数据结构）
    // 初始化文件系统
    File fileList;
    initFileSystem(&fileList);
	
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
	char cur_path[100];
	cur_path[0] = '/';

	while (1) 
	{
		printf("Enter your username: ");
		fgets(username, USERNAME_MAX_LENGTH, stdin);
		// 去除输入字符串末尾的换行符
		username[strcspn(username, "\n")] = '\0';

		printf("Enter your password: ");
		hide_password(password);
		printf("\n");

		// 去除输入字符串末尾的换行符
		// password[strcspn(password, "\n")] = '\0';

		if (0 == strcmp(username,"root") && 0 == strcmp(password,"0000")) {
			// 登陆成功后进入根目录
			strcat(cur_path,username);
			break;
		}
		printf("\033[31mAccese Denied: Username or Password is Faied!\033[0m\n\n");
	}

	while(1) {
		//6. 输出控制台信息并提取控制台命令
		char *last_path = find_last_path(cur_path);
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
		} else if (0 == strcmp(buf,"exit")) {
            // 退出登录
			printf("退出成功~~\n");
            break; 
		} else {
			printf("Invalid command! try help!\n");
		}
	}
    return 0;
}
