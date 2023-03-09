#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

menu()
{
	printf("#################################\n");
	printf("##########  1.开始游戏  #########\n");
	printf("##########  0.退出游戏  #########\n");
	printf("#################################\n");
}

int main()
{

	int choice = 0;
	//先打印菜单，用户再输入选项，因此用do循环；
	do
	{
		menu();
		printf("是否开始游戏->:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("开始游戏：\n");
			game();
			break;
		case 0:
			printf("退出游戏！\n");
			break;
		default:
			printf("非法输入！！！请重新输入:>>");
		}
	} while (choice);

	return 0;
}

void  game()
{
	char board[ROW][COL] = { 0 };
	//初始化棋盘
	init_table(board, ROW, COL);
	//打印棋盘
	print_table(board, ROW, COL);
	//随机数起点设置
	srand((unsigned int)time(NULL));

	//开始下棋
	char flag = ' ';	//设置标记接收judge函数的返回值
	while (1)
	{
		//玩家下棋
		play_user(board, ROW, COL);
		print_table(board, ROW, COL);
		
		flag = judge(board, ROW, COL);

		if (flag == '*' || flag ==  '#' || flag == 'S')
		{
			break;
		}
		//电脑随机下棋
		com_input(board, ROW, COL);
		print_table(board, ROW, COL);

		flag = judge(board, ROW, COL);
		//判断棋盘是否还有空位
		if (flag == '*' || flag == '#' || flag == 'S')
		{
			break;
		}
	}

	if ( '*' == flag)
	{
		printf("很遗憾，你输了哟~~\n");
	}
	else if ( '#' == flag)
	{
		printf("恭喜你，你赢啦！\n");
	}
	else if('S' == flag)
	{
		printf("平局也是一种胜利哟~~\n");
	}
}