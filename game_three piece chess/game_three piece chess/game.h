#pragma once

#include <stdio.h>
#include <stdlib.h>		//提供rand和srand函数随机生成数
#include <time.h>		//time();提供时间戳来设置随机数的起点

#define ROW 3  //行
#define COL 3  //列

void game();   //运行此游戏的总框架
void init_table(char board[ROW][COL], int row, int col); //初始化棋盘
void print_table(char board[ROW][COL], int row, int col);//打印棋盘

void play_user(char board[ROW][COL], int row, int col);		 //玩家开始下棋
void com_input(char board[ROW][COL], int row, int col);	 //电脑随机下棋 

char judge(char board[ROW][COL],int row,int col);			//判断输赢
int full(char board[ROW][COL],int row,int col);				//判断棋盘是否为空


