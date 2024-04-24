#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

void init_hash(HASH *hash)
{
	for(int i = 0; i < 10; i++)
		hash->arr[i] = NULL;
}

void insert_hash(HASH *hash, int data)
{
	NODE *node = malloc(sizeof(NODE));
	node->data = data;
	node->next = NULL;
	// 链地址法 降低 Hash冲突
	node->next = hash->arr[data%SIZE];
	// 不带头单向链表头插
	hash->arr[data%SIZE] = node;
}

void show_hash(HASH *hash)
{
	for(int i = 0; i < 10; i++)
	{
		NODE *head = hash->arr[i];
		while(head)
		{
			printf("%d->", head->data);
			head = head->next;
		}
		printf("\n");
	}
}