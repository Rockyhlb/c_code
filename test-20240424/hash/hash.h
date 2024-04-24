#ifndef _HASH_
#define _HASH_

typedef struct node{
	int data;
	struct node *next;
}NODE;

// Hash表的长度
#define SIZE 10
// 链地址法 降低 Hash冲突
typedef struct hash{
	/**
	 * 指针数组：指针数组是一个数组，它的每个元素都是一个指针。在这里，arr 是一个包含 SIZE 个元素的数组，每个元素都是指向 NODE 结构体的指针。
	 * 数组指针：数组指针是一个指针，它指向一个数组。与指针数组不同，数组指针指向的是整个数组()，而不是数组中的单个元素。(数组访问/数组传递/多维数组)
	 * int arr[5] = {1, 2, 3, 4, 5};
	 * int (*ptr)[5] = &arr; // 数组指针，指向一个包含5个整数的数组
	*/
	NODE *arr[SIZE];  // 指针数组，数组的每个元素都是指向 NODE 结构体的指针
}HASH;

void init_hash(HASH *hash);
void insert_hash(HASH *hash, int data);
void show_hash(HASH *hash);

#endif