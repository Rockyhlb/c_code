#pragma once

#include <stdio.h>
#include <stdlib.h>		//�ṩrand��srand�������������
#include <time.h>		//time();�ṩʱ�������������������

#define ROW 3  //��
#define COL 3  //��

void game();   //���д���Ϸ���ܿ��
void init_table(char board[ROW][COL], int row, int col); //��ʼ������
void print_table(char board[ROW][COL], int row, int col);//��ӡ����

void play_user(char board[ROW][COL], int row, int col);		 //��ҿ�ʼ����
void com_input(char board[ROW][COL], int row, int col);	 //����������� 

char judge(char board[ROW][COL],int row,int col);			//�ж���Ӯ
int full(char board[ROW][COL],int row,int col);				//�ж������Ƿ�Ϊ��


