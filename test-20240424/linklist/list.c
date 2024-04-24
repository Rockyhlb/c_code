#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void init_list(LIST *list)
{
	list->next = NULL;
}

void insert_list(LIST *list, int data, int offset)
{
	// 申请一个结点
	LIST *node = malloc(sizeof(LIST));
	node->data = data;
	node->next = NULL;

	// HEAD 标识头插
	if(HEAD == offset)
	{
		// 带头单向链表
		node->next = list->next;
		list->next = node;	
	}
}

void delete_list(LIST *list, int data)
{
	while(list->next)
	{
		if(data == list->next->data)
		{
			LIST *node = list->next;
			list->next = list->next->next;
			
			free(node);
			return;
		}
		list = list->next;
	}
}

void show_list(LIST *list)
{
	while(list->next)
	{
		// 由于是带头链表，因此每次遍历打印的都是 下一个结点 的 data,避免将不带数据的头一起打印
		printf("%d ", list->next->data);
		list = list->next;
	}
	printf("\n");
}