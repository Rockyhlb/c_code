#ifndef _MEMORY_
#define _MEMORY_

// 内存结构体
typedef struct memory {
    int mid;
    int size;
    int status; // 内存状态：已分配、未分配等
} MEMORY;

void allocate_memory(MEMORY *memory, int size);

#endif