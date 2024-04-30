#ifndef _MEMORY_
#define _MEMORY_

#define MEMORY_MAX_SIZE 256

typedef struct memory
{
    void *data[1024]; // 内存块数组
    int size;         // 当前消耗内存大小
    int is_used;      // 标记当前是否已经被用 0-未分配   1-已分配
} MEMORY;

void memory_init(MEMORY *memory);
void *my_malloc(MEMORY *memory, int size);
void my_free(MEMORY *memory, void *ptr);

#endif