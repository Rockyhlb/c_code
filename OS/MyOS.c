// #include <stdio.h>
// #include <signal.h>
// #include <string.h>
// #include <unistd.h>

// //模拟进程动作
// void func1()
// {
// 	printf("111111111111111\n");
// }
// //模拟进程动作
// void func2()
// {
// 	printf("2222222222222222222\n");
// }
// //模拟进程动作
// void func3()
// {
// 	printf("333333333333333\n");
// }

// // 函数指针
// typedef void FUNC(void);
// // 指针数组
// FUNC *arr[3];//模拟进程数据结构

// //模拟调度器
// void scheduler(int x)
// {
// 	static int i = 0;
// 	arr[i]();
// 	i = (i+1)%3;
// 	alarm(5);
// }

// int main()
// {
// 	//1. 输出启动界面
// 	printf("**********xxx  OS  starting!!!!************\n");
	
// 	//2. 初始化内存系统（数据结构）
	
// 	//3. 初始化文件系统（数据结构）
	
// 	//4. 初始化进程调度系统（数据结构）
// 	/*模拟网进程数据结构中加入新进程  add_thread(&threadlist, func1)  */
// 	arr[0] = func1;	
// 	arr[1] = func2;	
// 	arr[2] = func3;	
	
// 	/* 模拟定时器，完成调度器的运作 */
// 	signal(SIGALRM, scheduler);
// 	alarm(5);

// 	//5. 初始化设备（硬件驱动）

// 	while(1)
// 	{
// 		//6. 输出控制台信息并提取控制台命令
// 		printf("\033[44;33mroot@xxxOS# \033[0m");
// 		fflush(stdout); //强制printf输出
// 		char buf[100] = {0};
// 		gets(buf);
// 		//7. 处理命令
// 		if(0 == strcmp(buf, "ps") )
// 		{
// 			printf("PID\tNAME\tNICE\tTIME\n");
// 			for(int i=0; i<3; i++)
// 			{
// 				printf("%d\txxxx\t10\t10:00\n", i);
// 			}
// 		}
// 		else
// 			printf("cmd error ! try help!\n");
// 	}
// }
