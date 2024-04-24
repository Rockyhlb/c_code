#ifndef _SNAKE_
#define _SNAKE_

typedef struct snake {
	struct {
		int x;
		int y;
	}pos;
	struct snake *next;
}SNAKE;

void snake_init(SNAKE *head);
int snake_insert(SNAKE *head,int x,int y,int map[10][10]);

void snake_on_map(SNAKE *snake,int map[10][10]);
void snake_clear_map(SNAKE *snake,int map[10][10]);
int check_pos(SNAKE *head,int x,int y);

void snake_up(SNAKE *head,int map[10][10]);
void snake_down(SNAKE *head,int map[10][10]);
void snake_left(SNAKE *head,int map[10][10]);
void snake_right(SNAKE *head,int map[10][10]);

#endif