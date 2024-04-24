#ifndef _LIST_
#define _LIST_

typedef struct node{
	int data;
	// 前驱
	struct node *prev;
	// 后继
	struct node *next;
}LIST;

void list_init(LIST *list);
void list_insert(LIST *list, int data);

// NEXT 和 PREV 控制是顺序遍历 还是 逆序遍历
#define NEXT 0
#define PREV 1
void list_show(LIST *list, int dflag);

#endif

