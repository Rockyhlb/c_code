#define _CRT_SECURE_NO_WARNINGS 1

#include "tickets.h"

//菜单函数
void menu() 
{
	printf("\n\t---------------------------------欢迎来到火车信息管理系统---------------------------------\n");
	printf("\n\t*********************************\n");
	printf("\t\t1.录入列车信息\n\t\t2.查询列车情况\n\t\t3.修改列车信息\n\t\t4.保存已录入的信息\n\t\t5.读取已有的列车信息\n\t\t6.删除列车信息\n\t\t0.退出系统");
	printf("\n\t*********************************\n\t");
	printf("输入您所要执行的功能(0-8)：");
}

int main() 
{
	link l;
	int Choice;
	l = (Node *)malloc(sizeof(Node));
	l->next = NULL;
	do
	{
		system("color F4");
		menu();
		scanf("%d", &Choice);
		system("cls");
		switch (Choice)
		{
		case 1:
			insert_Info(l); 
			break;
		case 2:
			search(l); 
			break;
		case 3:
			updateInfo(l); 
			break;
		case 4:
			save(l);
			break;
		case 5:
			load(l);
			break;
		case 6:
			deleteInfo(l); 
			break;
		case 0:
			exit(0);
			break;
		default:
			continue;
		}
	} while (1);
	return 0;
}