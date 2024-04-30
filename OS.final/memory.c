#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "util.h"

// 初始化内存块
void memory_init(MEMORY *memory)
{
    print_log_info("Initializing memory...");
    int i,j;
    for (i = 0; i < MEMORY_MAX_SIZE; i++)
    {
        memory[i].size = 0;
        memory[i].is_used = 0;
        for (j = 0; j < 1024; j++)
        {
            memory[i].data[j] = NULL;
        }
        print_log_info("Starting initialization memory...");
    }
    print_log_info("Memory initialization complete...");
}

// 释放内存块
void my_free(MEMORY *memory, void *ptr)
{
    // 遍历内存块列表
    int i;
    for (i = 0; i < MEMORY_MAX_SIZE; i++)
    {
        // 遍历每个内存块中的数据项
        int j;
        for (j = 0; j < memory[i].size; j++)
        {
            // 检查当前数据项是否指向要释放的指针
            if (memory[i].data[j] == ptr)
            {
                // 从后向前移动数据以填补空洞
                int k;
                for (k = j; k < memory[i].size - 1; k++)
                {
                    memory[i].data[k] = memory[i].data[k + 1];
                }
                // 将最后一个元素设置为NULL，因为我们已经移除了一个元素
                memory[i].data[memory[i].size - 1] = NULL;
                // 减少内存块的大小
                memory[i].size--;

                // 检查内存块是否已经完全空闲
                if (memory[i].size == 0)
                {
                    memory[i].is_used = 0;
                }

                return; // 找到匹配项并处理后退出函数
            }
        }
    }
}

// 模拟内存分配
void *my_malloc(MEMORY *memory, int size)
{
    int i;
    for (i = 0; i < MEMORY_MAX_SIZE; i++)
    {
        if (!memory[i].is_used && memory[i].size <= size)
        {
            memory[i].is_used = 1;
            memory[i].size++;
            return memory[i].data;
        }
    }
    // 如果没有找到合适的内存块，返回NULL
    return NULL;
}