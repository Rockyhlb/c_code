#include "list.h"
#include <stdio.h>

int main()
{
	LIST list;
	list_init(&list);

	list_insert(&list, 1);
	list_insert(&list, 2);
	list_insert(&list, 3);
	list_insert(&list, 4);
	list_insert(&list, 5);

	// 顺序
	printf("NEXT: ");
	list_show(&list, NEXT);
	// 逆序
	printf("PREV: ");
	list_show(&list, PREV);
}
