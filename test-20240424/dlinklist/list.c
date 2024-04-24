#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_init(LIST *list)
{
	list->next = list->prev = NULL;
}

// 头插
void list_insert(LIST *list, int data) 
{
	LIST *node = malloc(sizeof(LIST));
	node->data = data;
	node->next = node->prev = NULL;

	node->next = list->next;
	node->prev = list;
	list->next = node;
	// node的下一个结点不为空时，让下一个结点的前驱指向自己
	if(node->next) {
		node->next->prev = node; 
	}
}

void list_show(LIST *list, int dflag) 
{
	if(NEXT == dflag) {
		while(list->next) {
			// 带头双向链表，打印下一个结点的 data
			printf("%d ", list->next->data);
			list = list->next;
		}
		printf("\n");
	} else {
		LIST *head = list;
		while(list->next) {
			list = list->next;
		}

		while(list != head) {
			// 由于是从尾打印，因此最后一个结点并不是头，就需要打印当前结点的 data
			printf("%d ", list->data);
			list = list->prev;
		}
		printf("\n");
	}
}