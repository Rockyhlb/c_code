#include "list.h"
#include <stdio.h>

int main()
{
	LIST list;
	init_list(&list);

	// 头插后 list = 5, 4, 3, 2, 1
	insert_list(&list, 1, HEAD);
	insert_list(&list, 2, HEAD);
	insert_list(&list, 3, HEAD);
	insert_list(&list, 4, HEAD);
	insert_list(&list, 5, HEAD);

	printf("Before delete: \n");
	show_list(&list);

	printf("After delete 3: \n");
	delete_list(&list, 3);

	show_list(&list);
}

