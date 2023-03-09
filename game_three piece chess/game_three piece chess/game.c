#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void init_table(char board[ROW][COL],int row,int col)
{
	//i,j控制行列
	int i = 0, j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

//        |  |  
//
//		--|--|--
//
//		  |  |
//
//		--|--|--
//
//		  |  |

void print_table(char board[ROW][COL], int row, int col)
{
	int i = 0, j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf("%c ", board[i][j]);
			if (j < col - 1)
			{
				//因为三子棋打印出来的分隔符应该是二行二列
				//因此此处打印列分隔符应该小于列数-1
				printf("|");
			}
		}
		printf("\n");

		//分隔行也应该少于行数-1
		if (i < row - 1)
		{
			//将分隔行扩大成--|--|--的形式
			for (int k = 0; k < col; k++)
			{

				printf("--");
				if (k < col - 1)
				{
					printf("|");
				}
			}
			printf("\n");
		}
	}
}

void play_user(char board[ROW][COL], int row, int col)
{
	//此处我们规定电脑下棋用“*”，玩家下棋用“#”
	//下棋落子的前提是：该处没有被电脑或玩家下过
	//玩游戏坐标是从1开始，但我们的数组下标是0开始，因此要-1
	//此处判断输入代码块应该还能再优化！！！！！
	int x = 0, y = 0;

	while (1)
	{
		printf("玩家落子(#)：玩家请输入坐标位置：");
		scanf("%d %d", &x, &y);
		if (x > row || y > col || x <= 0 || y <= 0)
		{
			printf("落子错误，请在%d行%d列内落子。。。\n", row, col);
		}
		else
		{
			if ((board[x - 1][y - 1] == ' '))
			{
				board[x - 1][y - 1] = '#';
				break;
			}
			else
			{
				printf("该处已被占用，请重新输入合法位置。。。\n");

			}
		}
	}
}

void com_input(char board[ROW][COL],int row,int col)
{
	printf("电脑落子(*)：\n");
	while (1)
	{
		int x = rand() % row ;
		int y = rand() % col ;
		if (board[x][y] == ' ')
		{
			board[x][y] = '*';
			break;
		}
	}
}

//玩家赢，返回‘#’
//电脑赢，返回‘*’
//平局，返回‘S’
//游戏继续，返回‘C’
char judge(char board[ROW][COL],int row,int col)
{
	int i = 0, j = 0;
	//一方在一条直线上的符号相同则该方胜利
	//判断行相同的情况
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
		{
			return board[i][1];
		}
	}
	//判断列相同的情况
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
		{
			return board[1][j];
		}
	}
	//判断对角线相同的情况
	if (board[0][0] == board[1][1] && board[1][1] ==board[2][2] && board[0][0] != ' ')
	{
		return board[1][1];
	}
	
	//		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//		!!!!!!!!!!!!!!!!!!此处吃了点苦头哟!!!!!!!!!!!!!!!!
	//		if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	//		{
	//			return board[1][1];
	//		}
	if (board[1][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		return board[1][2];
	}
	//判断当棋盘已满时，没有出现一方胜利的情况
	if (full(board,ROW,COL))  //full函数返回1则return S
	{
		return 'S';
	}
	//游戏继续
	else
	{
		return 'C';
	}
}

int full(char board[ROW][COL],int row,int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0;j < col;j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}