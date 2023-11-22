#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef int Elemtype;

typedef struct queue
{
	Elemtype *arr;
	int front;
	int rear;
}queue;

void menu()
{
	printf("***********�кų���***********\n");
	printf("********   1.�Ŷ�    *********\n");
	printf("********   2.�Ͳ�    *********\n");
	printf("********   3.��ѯ�Ŷ�����  ***\n");
}

int main()
{
	queue q;
	int data;
	initQueue(&q);
	int choice = 0;

	do
	{
		menu();
		printf("\n���������ѡ��\n");
		scanf("%d", &choice);

		if (choice == 0)
		{
			break;
		}

		switch (choice)
		{
		case 1:
			enterQueue(&q);
			break;

		case 2:
			data = deleteQueue(&q);
			printf("��%d�ŵ����ھͲ�\n\n", data);
			break;

		case 3:
			printQueue(q);
			break;
		}
	} while (choice);

	return 0;
}

void initQueue(queue *q)
{
	q->arr = (Elemtype*)malloc(sizeof(Elemtype) * MAXSIZE);
	if (!q->arr)
	{
		exit(-1);
	}
	q->front = q->rear = 0;
}

void enterQueue(queue *q)
{
	if ((q->rear + 1) % MAXSIZE == 0)
	{
		return;
	}
	else
	{
		q->arr[q->rear] = q->rear+1;
		printf("����ȡ�ͺ��ǣ�%d \n\n",q->rear+1);
		q->rear = ((q->rear) + 1) % MAXSIZE;
	}
	
}

int deleteQueue(queue *q)
{
	if (q->front == q->rear)
	{
		exit(-1);
	}

	int data = q->arr[q->front];
	q->front = ((q->front) + 1) % MAXSIZE;
	return data;
}

void printQueue(queue q)
{
	if (q.front == q.rear)
	{
		printf("--��ǰ����ǰ��û�����ŶӾͲ�--\n\n");
		return;
	}
	else
	{
		printf("--��ǰ����ǰ����%d���ŶӾͲ�--\n\n ",q.rear - q.front);
	}
}