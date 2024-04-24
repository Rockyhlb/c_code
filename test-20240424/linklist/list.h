// 条件编译的开始部分，通过 #ifndef 指令判断宏 _LIST_ 是否已经被定义。
// 如果 _LIST_ 未被定义，那么执行后续的代码，否则跳过后续代码直接到 #endif 结束处。
#ifndef _LIST_
#define _LIST_

typedef struct node{
	int data;
	struct node *next;
}LIST;

void init_list(LIST *list);

#define HEAD 0
void insert_list(LIST *list, int data, int offset);
void delete_list(LIST *list, int data);
void show_list(LIST *list);

#endif

