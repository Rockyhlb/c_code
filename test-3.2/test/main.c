#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //提供strlen等函数
#include <Windows.h>  //提供Sleep函数产生缓慢打印的效果
#include <time.h>  //提供time函数

//int main()
//{
//	int i = 0, k = 0;
//	for (i = 0,k = 0; k = 0;i++,k++)	
//	{
//		printf("%d", k);
//	}
//	return 0;
//}

//int main()
//{
//	int i = 1;
//	do
//	{
//		if (5 == i)
//		{
//			break;
//		}
//		printf("%d ", i);
//		i++;
//	} while (i < 10);
//	return 0;
//}


//int main()
//{
//	//计算n的阶乘
//	//int n = 0;
//	//输入
//	//scanf("%d", &n);
//	//计算
//	int res = 1;
//	int sum = 0;
//	for (int i = 1;i <= 10;i++)
//	{
//		res = 1;
//		for (int j = 1; j <= i; j++)
//		{
//			res *= j;
//		}
//		sum += res;
//	}
//	
//	printf("%d\n",sum);
//	return 0;
//}


//int main()
//{
//	//利用二分查找有序数组！！！
//	//定义有序数组
//	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
//	//标记目标元素是否被找到
//	int flag = 0;
//	int left = 0, right = 0, mid = 0;
//	//求数组长度
//	int len = sizeof(a) / sizeof(a[0]);
//	//需要被查找的数
//	int k = 7;
//	left = 0;
//	right = len - 1;
//	
//	while (left <= right)
//	{
//		mid = (left + right) / 2;
//		if (a[mid] < k)
//		{
//			left = mid + 1;
//		}
//		else if(a[mid] > k)
//		{
//			right = mid - 1;
//		}
//		else
//		{
//			printf("find!,下标是：%d",mid);
//			flag = 1;
//			break;
//		}
//	}
//	if (flag == 0)
//	{
//		printf("No find!");
//	}
//	return 0;
//}


////演示多个字符从两端向中间汇聚  happy every day!
//int main()
//{
//	char arr1[] = "happy every day!";
//	char arr2[] = "****************";
//	//定位下标
//	int left = 0, right = strlen(arr1)-1;
//
//	while (left <= right)
//	{
//		arr2[left] = arr1[left];
//		arr2[right] = arr1[right];
//		printf("%s\n", arr2);
//		Sleep(1000);  //停顿
//		system("cls");//清理窗口
//		left++;
//		right--;
//	}
//	return 0;
//}


////假设密码是123456，三次机会进行密码验证
//int main()
//{
//	char passwd[20] = { 0 };
//	int flag = 0;
//	for (int i = 0; i < 3; i++)
//	{
//		printf("请输入密码:>");
//		scanf("%s", passwd);
//		//判断
//		if (strcmp(passwd,"123456") == 0)
//		{
//			flag = 1;
//			printf("密码正确！\n");
//			break;
//		}
//		else
//		{
//			printf("密码错误！\n");
//		}
//	}
//	if (flag == 0)
//	{
//		printf("三次密码均输入错误,退出程序！\n");
//	}
//	return 0;
//}


////猜数字游戏
//int main()
//{
//	int input = 0;
//	do
//	{
//		menu();
//		printf("请选择:>");
//		scanf("%d", &input);
//		switch (input)
//		{
//		case 1:
//		{
//			game();
//			break;
//		}
//		case 0:
//		{
//			break;
//		}
//		default:
//			printf("选择错误");
//			break;
//		}
//	} while (input);
//	return 0;
//}
//
// int menu()
//{
//	printf("***************************\n");
//	printf("******    1.play    *******\n");
//	printf("******    0.exit    *******\n");
//	printf("***************************\n");
//}
//
//int game()
//{
//	//设置随机数的生成器
//	srand((unsigned)time(NULL));
//	//rand函数返回一个0~32767的随机数
//	int flag = rand()%100 + 1; //取模将随机数控制成0~100的数
//	//读取所猜的数
//	printf("请输入你所猜的数：>");
//	int num = 0;
//	while (scanf("%d",&num) != EOF)
//	{
//		printf("%d\n", flag);  //查看生成的随机数
//		if (flag < num)
//		{
//			printf("数字猜大了，真可惜\n");
//		}
//		else if (flag > num)
//		{
//			printf("数字猜小了，真可惜\n");
//		}
//		else
//		{
//			printf("恭喜你，猜对了！\n");
//			break;
//		}
//	}
//}