#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

void snake_init(SNAKE *head) {
    head->next = NULL;
}

void snake_on_map(SNAKE *snake,int map[10][10]) {
    while(snake->next) {
        map[snake->next->pos.x][snake->next->pos.y] = 3;
        snake = snake->next;
    }
}

void snake_clear_map(SNAKE *snake,int map[10][10]) {
    while(snake->next) {
        map[snake->next->pos.x][snake->next->pos.y] = 0;
        snake = snake->next;
    }
}

int snake_insert(SNAKE *head,int x,int y,int map[10][10]) {
    SNAKE *node = malloc(sizeof(SNAKE));
	node->pos.x = x;
	node->pos.y = y;
	node->next = NULL;

    // 检查移动方向是否碰到身体
    int res = check_pos(head,x,y);
    if (0 == res)
    {
        printf("BBQ,游戏结束！\n");
        exit(0);
    }

    if (x > 0 && x < 9 && y > 0 && y < 9)
    {
        node->next = head->next;
        head->next = node;
        
        if (2 == map[x][y])
        {
            map[x][y] = 3;
            int xpos = (rand() % 8) + 1;
            int ypos = (rand() % 8) + 1;
            // 检查随机数的位置，防止食物生成在🐍身处
            int flag = check_pos(head,xpos,ypos);
            while (0 == flag)
            {
                xpos = (rand() % 8) + 1;
                ypos = (rand() % 8) + 1;
                flag = check_pos(head,xpos,ypos);
            }
            
            map[xpos][ypos] = 2;
            // 1 - 吃到食物
            return 1;
        }
    }else {
        printf(": Game over~~\n");
        exit(0);
    }
    // 0 - 未吃到食物
    return 0;
}

int check_pos(SNAKE *head,int x,int y) {
    while (head->next)
    {
        if (x == head->next->pos.x && y == head->next->pos.y)
        {
            // 0 - 地址重复
            return 0;
        }
        head = head->next;
    }
    // 1 - 地址有效
    return 1;
} 

static void snake_delete_tail(SNAKE *snake)
{	
	while(snake->next)
	{
		if(snake->next->next == NULL)
		{	
			SNAKE *t = snake->next;
			snake->next = NULL;
			free(t);
			break;
		}
		snake = snake->next;
	}
}

void snake_up(SNAKE *head,int map[10][10]) {
    int res = snake_insert(head, head->next->pos.x-1, head->next->pos.y,map);
	if (0 == res)
    {
        snake_delete_tail(head);    
    }
}

void snake_down(SNAKE *head,int map[10][10]) {
    int res = snake_insert(head, head->next->pos.x+1, head->next->pos.y,map);
	if (0 == res)
    {
        snake_delete_tail(head);    
    }
}

void snake_left(SNAKE *head,int map[10][10]) {
    int res = snake_insert(head, head->next->pos.x, head->next->pos.y-1,map);
	if (0 == res)
    {
        snake_delete_tail(head);    
    }
}

void snake_right(SNAKE *head,int map[10][10]) {
    int res = snake_insert(head, head->next->pos.x, head->next->pos.y+1,map);
	if (0 == res)
    {
        snake_delete_tail(head);    
    }
}